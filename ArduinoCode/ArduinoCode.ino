// =============================================================================
// ArduinoCode.ino
// Toyota A340 Transmission Controller — Full PRND21 Edition
//
// Controls a Toyota A340 automatic transmission via paddle shifters.
// Reads all 6 positions from the factory inhibitor switch (P/R/N/D/2/L)
// and manages gear selection, solenoid actuation, and display feedback.
//
// === HARDWARE: Arduino Mega 2560 ===
//
// --- DISPLAY: WaveShare 1.5" RGB OLED (SSD1351, 128x128) ---
//   Display DIN  → Mega pin 51  (hardware MOSI — fixed, not reassignable)
//   Display CLK  → Mega pin 52  (hardware SCK  — fixed, not reassignable)
//   Display CS   → Mega pin 44  (user-assigned digital pin, active LOW)
//   Display DC   → Mega pin 45  (user-assigned digital pin, HIGH=data LOW=command)
//   Display RES  → Mega pin 46  (user-assigned digital pin, LOW=reset)
//   Display VCC  → 3.3V ONLY    (do NOT use 5V — will damage the OLED)
//   Display GND  → GND
//   Library: Adafruit_SSD1351 (install via Arduino Library Manager)
//
// --- INPUTS: Paddle switches (active LOW — wired to GND, INPUT_PULLUP) ---
//   Pin 2  → Shift Up paddle
//   Pin 3  → Shift Down paddle
//
// --- INPUTS: Inhibitor switch (active HIGH via voltage dividers, INPUT) ---
//   The A340 factory inhibitor switch outputs 12V per position.
//   Use a voltage divider per input: 10kΩ (signal→pin) + 4.7kΩ (pin→GND)
//   This converts 12V → ~3.8V (safe for Arduino 5V logic).
//
//   Pin 4  → Park    (factory wire: Green/White)
//   Pin 5  → Reverse (factory wire: Red/Black)
//   Pin 6  → Neutral (factory wire: Red)
//   Pin 7  → Drive   (factory wire: Black/Orange)
//   Pin 8  → 2nd     (factory wire: Orange)
//   Pin 9  → Low     (factory wire: Yellow/Blue)
//
// --- OUTPUTS: Solenoids (via relay board or MOSFET driver — NOT direct) ---
//   A340 solenoids run on 12V and draw up to 2A each.
//   Never connect solenoids directly to Arduino pins.
//   Pin 11 → Solenoid S1  (Shift solenoid A)
//   Pin 12 → Solenoid S2  (Shift solenoid B)
//   Pin 13 → Solenoid SLU (Torque converter lockup — digital on/off, not PWM)
//   Add flyback diodes (1N4007) across each solenoid to prevent voltage spikes.
//
// === VERIFIED A340 SOLENOID MAPPING ===
//   1st:        S1=ON  S2=OFF SLU=OFF
//   2nd:        S1=ON  S2=ON  SLU=OFF
//   3rd:        S1=OFF S2=ON  SLU=OFF
//   4th (OD):   S1=OFF S2=OFF SLU=OFF  ← also transmission electrical failsafe
//   4th+Lockup: S1=OFF S2=OFF SLU=ON
//   P/R/N:      S1=OFF S2=OFF SLU=OFF  ← all off (R and N are purely hydraulic)
//
// === REFERENCES ===
//   MaxxECU A340E/A341E wiring documentation
//   EveryCircuit A340 paddle shifter community implementation
//   Megasquirt A340 forum (PRND21 wiring, 12V inhibitor signal handling)
//   Toyota Nation forum (A340 9-pin inhibitor switch pinout + wire colors)
//   Adafruit SSD1351 library documentation
// =============================================================================

#include "PaddleShiftIndication.h"
#include "GearSelectorSwitch.h"
#include "SolenoidMapper.h"
#include "ScreenIndication.h"

// --- Paddle Switch Pins ---
#define PIN_SHIFT_UP    2
#define PIN_SHIFT_DOWN  3

// --- Inhibitor Switch Pins (via voltage dividers) ---
#define PIN_SEL_PARK    4
#define PIN_SEL_REVERSE 5
#define PIN_SEL_NEUTRAL 6
#define PIN_SEL_DRIVE   7
#define PIN_SEL_SECOND  8
#define PIN_SEL_LOW     9

// --- Solenoid Output Pins (via relay/driver board) ---
#define PIN_S1          11
#define PIN_S2          12
#define PIN_SLU         13

// --- Display SPI Pins (DIN→51, CLK→52 are fixed hardware SPI on Mega) ---
// CS, DC, RST must be digital output-capable pins — do NOT use analog-only pins
#define PIN_LCD_CS      44
#define PIN_LCD_DC      45
#define PIN_LCD_RST     46

// --- Gear Bounds ---
#define GEAR_MIN  1   // 1st
#define GEAR_MAX  5   // 4th + Lockup

// --- Class Instances ---
PaddleShiftIndication paddle(PIN_SHIFT_UP, PIN_SHIFT_DOWN);

GearSelectorSwitch selector(
    PIN_SEL_PARK,
    PIN_SEL_REVERSE,
    PIN_SEL_NEUTRAL,
    PIN_SEL_DRIVE,
    PIN_SEL_SECOND,
    PIN_SEL_LOW
);

SolenoidMapper   solenoids(PIN_S1, PIN_S2, PIN_SLU);
ScreenIndication screen(PIN_LCD_CS, PIN_LCD_DC, PIN_LCD_RST);

// --- Global State ---
int currentGear = 1;  // Always start in 1st

// =============================================================================
void setup() {
    Serial.begin(9600);
    Serial.println("A340 Controller — Starting up");

    paddle.begin();
    selector.begin();
    solenoids.begin();  // Calls allOff() — safe startup default
    screen.begin();

    // Apply initial display and solenoid state from current selector position
    applyState(selector.getState());
}

// =============================================================================
void loop() {
    paddle.update();
    selector.update();

    GearSelectorState state = selector.getState();

    // -------------------------------------------------------------------------
    // One-shot state entry handlers
    // Each justEntered flag fires for exactly one loop cycle on state change.
    // -------------------------------------------------------------------------

    if (selector.justEnteredPark()) {
        currentGear = 1;
        solenoids.allOff();
        screen.showPark();
        Serial.println("-> PARK | gear reset to 1 | solenoids off");
        return;
    }

    if (selector.justEnteredReverse()) {
        currentGear = 1;    // Reset so returning to Drive always starts in 1st
        solenoids.allOff(); // Reverse is purely hydraulic — solenoids irrelevant
        screen.showReverse();
        Serial.println("-> REVERSE | gear reset to 1 | solenoids off");
        return;
    }

    if (selector.justEnteredNeutral()) {
        solenoids.allOff(); // Neutral is purely hydraulic — solenoids irrelevant
        screen.showNeutral();
        Serial.println("-> NEUTRAL | solenoids off");
        return;
    }

    if (selector.justEnteredDrive()) {
        solenoids.applyGear(currentGear);
        screen.showGear(currentGear);
        Serial.print("-> DRIVE | gear ");
        Serial.println(currentGear);
        return;
    }

    if (selector.justEnteredSecond()) {
        currentGear = 2;
        solenoids.applyGear(2);
        screen.showGear(2);
        Serial.println("-> 2ND HOLD");
        return;
    }

    if (selector.justEnteredLow()) {
        currentGear = 1;
        solenoids.applyGear(1);
        screen.showLow();
        Serial.println("-> LOW HOLD");
        return;
    }

    // -------------------------------------------------------------------------
    // Ongoing state handling (runs every loop while in that state)
    // -------------------------------------------------------------------------
    switch (state) {

        case GEAR_SEL_PARK:
        case GEAR_SEL_REVERSE:
        case GEAR_SEL_NEUTRAL:
        case GEAR_SEL_SECOND:
        case GEAR_SEL_LOW:
            // All handled fully by justEntered above — nothing ongoing needed
            break;

        case GEAR_SEL_DRIVE: {
            bool wantUp   = paddle.shiftUpRequested();
            bool wantDown = paddle.shiftDownRequested();

            if (wantUp && currentGear < GEAR_MAX) {
                currentGear++;
                solenoids.applyGear(currentGear);
                screen.showGear(currentGear);
                Serial.print("SHIFT UP -> gear ");
                Serial.println(currentGear);

            } else if (wantDown && currentGear > GEAR_MIN) {
                currentGear--;
                solenoids.applyGear(currentGear);
                screen.showGear(currentGear);
                Serial.print("SHIFT DOWN -> gear ");
                Serial.println(currentGear);
            }
            break;
        }

        case GEAR_SEL_UNKNOWN:
            // Transitioning between positions — blank screen, hold solenoids
            screen.showBlank();
            break;
    }
}

// =============================================================================
// applyState() — sets initial display and solenoid state at startup.
// Cannot use justEntered flags at boot since no transition has occurred.
// =============================================================================
void applyState(GearSelectorState state) {
    switch (state) {
        case GEAR_SEL_PARK:
            currentGear = 1;
            solenoids.allOff();
            screen.showPark();
            Serial.println("INIT: PARK");
            break;

        case GEAR_SEL_REVERSE:
            currentGear = 1;
            solenoids.allOff();
            screen.showReverse();
            Serial.println("INIT: REVERSE");
            break;

        case GEAR_SEL_NEUTRAL:
            solenoids.allOff();
            screen.showNeutral();
            Serial.println("INIT: NEUTRAL");
            break;

        case GEAR_SEL_DRIVE:
            solenoids.applyGear(currentGear);
            screen.showGear(currentGear);
            Serial.print("INIT: DRIVE gear ");
            Serial.println(currentGear);
            break;

        case GEAR_SEL_SECOND:
            currentGear = 2;
            solenoids.applyGear(2);
            screen.showGear(2);
            Serial.println("INIT: 2ND HOLD");
            break;

        case GEAR_SEL_LOW:
            currentGear = 1;
            solenoids.applyGear(1);
            screen.showLow();
            Serial.println("INIT: LOW HOLD");
            break;

        case GEAR_SEL_UNKNOWN:
        default:
            solenoids.applyGear(currentGear);
            screen.showBlank();
            Serial.println("INIT: UNKNOWN/TRANSITIONING");
            break;
    }
}
