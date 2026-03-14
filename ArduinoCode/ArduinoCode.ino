// =============================================================================
// ArduinoCode.ino
// Jeep XJ AW4 Transmission Controller
//
// Controls the AW4 automatic transmission via paddle shifters.
// Reads selector position from the AW4 neutral safety switch (NSS)
// wired directly to the Arduino — no factory TCU involved.
//
// === AW4 NSS WIRING ('87-'96, 8-pin Deutsch connector, pins A-H) ===
//
// The AW4 NSS is a CONTINUITY switch — it closes pin pairs per position.
// Wire using INPUT_PULLUP. Active LOW (LOW = that position is selected).
// No voltage dividers needed — this is NOT a 12V powered switch.
//
//   Park/Neutral (B<->C): Arduino pin 4 ← NSS pin B,  NSS pin C → GND
//   Reverse      (A<->E): Arduino pin 5 ← NSS pin A,  NSS pin E → GND
//   3rd hold     (A<->G): Arduino pin 6 ← NSS pin A*, NSS pin G → GND
//   1-2 hold     (A<->H): Arduino pin 7 ← NSS pin A*, NSS pin H → GND
//   Drive: no continuity — detected when all NSS pins read HIGH
//
//   * Pin A is shared across Reverse, 3rd, and 1-2. Wire each to its own
//     Arduino pin via the unique side (E, G, H). Pin A connects to GND
//     through whichever pair is closed. Using INPUT_PULLUP handles this.
//
//   Park and Neutral share the same NSS signal (B<->C). They cannot be
//   distinguished by the switch alone. Both are treated as PARK/NEUTRAL.
//
// '97-'01 connector: different physical connector. Verify pinout from
// '97-'01 FSM before wiring. Same INPUT_PULLUP / active LOW logic applies.
//
// === PADDLE SWITCHES ===
//   Pin 2 → Shift Up   (active LOW, wired to GND, INPUT_PULLUP)
//   Pin 3 → Shift Down (active LOW, wired to GND, INPUT_PULLUP)
//
// === SOLENOID OUTPUTS (via relay/driver board — NOT direct) ===
//   Pin 11 → S1  |  Pin 12 → S2  |  Pin 13 → SLU
//   A340/AW4 solenoids run 12V, up to 2A each. Use flyback diodes (1N4007).
//
// === DISPLAY: WaveShare 1.5" RGB OLED (SSD1351, 128x128, 3.3V ONLY) ===
//   DIN  → Mega pin 51 (hardware MOSI — fixed)
//   CLK  → Mega pin 52 (hardware SCK  — fixed)
//   CS   → A5  |  DC → A4  |  RES → A3
//
// === VERIFIED AW4 SOLENOID MAPPING ===
//   1st:        S1=ON  S2=OFF SLU=OFF
//   2nd:        S1=ON  S2=ON  SLU=OFF
//   3rd:        S1=OFF S2=ON  SLU=OFF
//   4th (OD):   S1=OFF S2=OFF SLU=OFF  ← also electrical failsafe
//   4th+Lockup: S1=OFF S2=OFF SLU=ON
//   P/R/N:      S1=OFF S2=OFF SLU=OFF
// =============================================================================

#include "PaddleShiftIndication.h"
#include "GearSelectorSwitch.h"
#include "SolenoidMapper.h"
#include "ScreenIndication.h"

// --- Paddle Pins ---
#define PIN_SHIFT_UP    2
#define PIN_SHIFT_DOWN  3

// --- NSS Pins (INPUT_PULLUP, active LOW) ---
#define PIN_NSS_PN      4   // Park / Neutral (B<->C)
#define PIN_NSS_R       5   // Reverse        (A<->E)
#define PIN_NSS_3       6   // 3rd hold       (A<->G)
#define PIN_NSS_12      7   // 1-2 hold       (A<->H)

// --- Solenoid Output Pins (via relay/driver board) ---
#define PIN_S1          11
#define PIN_S2          12
#define PIN_SLU         13

// --- Display SPI Pins (DIN→51, CLK→52 fixed on Mega) ---
#define PIN_LCD_CS      A5
#define PIN_LCD_DC      A4
#define PIN_LCD_RST     A3

// --- Gear Bounds ---
#define GEAR_MIN  1   // 1st
#define GEAR_MAX  5   // 4th + Lockup

// --- Class Instances ---
PaddleShiftIndication paddle(PIN_SHIFT_UP, PIN_SHIFT_DOWN);

GearSelectorSwitch selector(
    PIN_NSS_PN,
    PIN_NSS_R,
    PIN_NSS_3,
    PIN_NSS_12
);

SolenoidMapper   solenoids(PIN_S1, PIN_S2, PIN_SLU);
ScreenIndication screen(PIN_LCD_CS, PIN_LCD_DC, PIN_LCD_RST);

// --- Global State ---
int currentGear = 1;

// =============================================================================
void setup() {
    Serial.begin(9600);
    Serial.println("AW4 Controller — Starting up");

    paddle.begin();
    selector.begin();
    solenoids.begin();  // Calls allOff() — safe startup default
    screen.begin();

    applyState(selector.getState());
}

// =============================================================================
void loop() {
    paddle.update();
    selector.update();

    GearSelectorState state = selector.getState();

    // -------------------------------------------------------------------------
    // One-shot state entry handlers
    // -------------------------------------------------------------------------

    if (selector.justEnteredParkNeutral()) {
        currentGear = 1;
        solenoids.allOff();
        screen.showPark();  // P covers both Park and Neutral
        Serial.println("-> PARK/NEUTRAL | gear reset to 1 | solenoids off");
        return;
    }

    if (selector.justEnteredReverse()) {
        currentGear = 1;    // Reset so returning to Drive always starts in 1st
        solenoids.allOff(); // Reverse is purely hydraulic
        screen.showReverse();
        Serial.println("-> REVERSE | gear reset to 1 | solenoids off");
        return;
    }

    if (selector.justEnteredDrive()) {
        solenoids.applyGear(currentGear);
        screen.showGear(currentGear);
        Serial.print("-> DRIVE | gear ");
        Serial.println(currentGear);
        return;
    }

    if (selector.justEnteredThird()) {
        // 3rd position: allows 1st–3rd only, clamp if currently in 4th or 4L
        if (currentGear > 3) currentGear = 3;
        solenoids.applyGear(currentGear);
        screen.showNeutral(); // TODO: currently shows "N" — add showThird() to ScreenIndication if "3" is preferred (see SKILL_ScreenIndication.md)
        Serial.println("-> 3RD HOLD | clamped to max 3rd");
        return;
    }

    if (selector.justEnteredOneTwo()) {
        // 1-2 position: allows 1st–2nd only, clamp if currently above 2nd
        if (currentGear > 2) currentGear = 2;
        solenoids.applyGear(currentGear);
        screen.showGear(2);
        Serial.println("-> 1-2 HOLD | clamped to max 2nd");
        return;
    }

    // -------------------------------------------------------------------------
    // Ongoing state handling
    // -------------------------------------------------------------------------
    switch (state) {

        case GEAR_SEL_PARK_NEUTRAL:
        case GEAR_SEL_REVERSE:
            // Fully handled by justEntered — nothing ongoing needed
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

        case GEAR_SEL_THIRD:
            // Manual 3rd hold — paddle shifting disabled in this range
            break;

        case GEAR_SEL_ONE_TWO:
            // Manual 1-2 hold — paddle shifting disabled in this range
            break;

        case GEAR_SEL_UNKNOWN:
            screen.showBlank();
            break;
    }
}

// =============================================================================
// applyState() — sets initial display and solenoid state at startup.
// =============================================================================
void applyState(GearSelectorState state) {
    switch (state) {
        case GEAR_SEL_PARK_NEUTRAL:
            currentGear = 1;
            solenoids.allOff();
            screen.showPark();
            Serial.println("INIT: PARK/NEUTRAL");
            break;

        case GEAR_SEL_REVERSE:
            currentGear = 1;
            solenoids.allOff();
            screen.showReverse();
            Serial.println("INIT: REVERSE");
            break;

        case GEAR_SEL_DRIVE:
            solenoids.applyGear(currentGear);
            screen.showGear(currentGear);
            Serial.print("INIT: DRIVE gear ");
            Serial.println(currentGear);
            break;

        case GEAR_SEL_THIRD:
            if (currentGear > 3) currentGear = 3;
            solenoids.applyGear(currentGear);
            screen.showNeutral(); // TODO: currently shows "N" — add showThird() if "3" is preferred (see SKILL_ScreenIndication.md)
            Serial.println("INIT: 3RD HOLD");
            break;

        case GEAR_SEL_ONE_TWO:
            if (currentGear > 2) currentGear = 2;
            solenoids.applyGear(currentGear);
            screen.showGear(2);
            Serial.println("INIT: 1-2 HOLD");
            break;

        case GEAR_SEL_UNKNOWN:
        default:
            solenoids.applyGear(currentGear);
            screen.showBlank();
            Serial.println("INIT: UNKNOWN");
            break;
    }
}
