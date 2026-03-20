# Class Reference — ArduinoCode Firmware

Quick reference for all classes in the transmission controller firmware. For full implementation details see the corresponding SKILL.md files in `.agents/skills/`.

---

## Ownership Rule

**`currentGear` (int, 1–5) is declared in `ArduinoCode.ino` and is the single source of truth for the selected gear. No class may store, shadow, or modify it.**

---

## `ArduinoCode.ino` — Main Sketch

Owns: `currentGear`, `setup()`, `loop()`, `applyState()`

Key responsibilities:
- Calls `update()` on all input objects every `loop()` iteration
- Processes one-shot entry flags from `GearSelectorSwitch` first
- Handles ongoing state in the `switch (state)` block
- `applyState()` is called once in `setup()` to initialise display and solenoids to match the current physical selector position

Pin defines:
```cpp
#define PIN_SHIFT_UP    2
#define PIN_SHIFT_DOWN  3
#define PIN_NSS_PN      4
#define PIN_NSS_R       5
#define PIN_NSS_3       6
#define PIN_NSS_12      7
#define PIN_S1          11
#define PIN_S2          12
#define PIN_SLU         13
#define PIN_LCD_CS      A5
#define PIN_LCD_DC      A4
#define PIN_LCD_RST     A3
#define GEAR_MIN        1
#define GEAR_MAX        5
```

---

## `PaddleShiftIndication`

Skill: `.agents/skills/paddle-shift-indication/SKILL.md`

```cpp
PaddleShiftIndication(int pinUp, int pinDown);
void begin();               // Call once in setup() — configures INPUT_PULLUP
void update();              // Call every loop() — samples pins, runs debounce
bool shiftUpRequested();    // Returns true once per press, then auto-clears
bool shiftDownRequested();  // Returns true once per press, then auto-clears
```

Key behaviour:
- Active LOW, INPUT_PULLUP — triggers on falling edge (HIGH→LOW)
- 50ms timestamp-based debounce (non-blocking)
- One-shot: flag is consumed and cleared by the accessor — never needs manual reset
- Held paddle does NOT repeat — only the initial press edge fires

---

## `GearSelectorSwitch`

Skill: `.agents/skills/gear-selector-switch/SKILL.md`

```cpp
GearSelectorSwitch(int pinPN, int pinR, int pin3, int pin12);
void begin();                    // Call once in setup()
void update();                   // Call every loop()
GearSelectorState getState();    // Returns current stable state
bool justEnteredParkNeutral();   // One-shot on entry — auto-clears next update()
bool justEnteredReverse();
bool justEnteredDrive();
bool justEnteredThird();
bool justEnteredOneTwo();
```

State enum:
```cpp
enum GearSelectorState {
    GEAR_SEL_PARK_NEUTRAL,  // B↔C closed
    GEAR_SEL_REVERSE,       // A↔E closed
    GEAR_SEL_DRIVE,         // All pins HIGH (no continuity)
    GEAR_SEL_THIRD,         // A↔G closed
    GEAR_SEL_ONE_TWO,       // A↔H closed
    GEAR_SEL_UNKNOWN        // Multiple pins LOW — selector mid-travel
};
```

Key behaviour:
- `justEntered*()` flags auto-clear on next `update()` call
- Drive is detected by **absence** of any signal — all four pins HIGH
- UNKNOWN fires when multiple pins are stably LOW simultaneously

**Critical: do NOT reset `currentGear` in the `justEnteredParkNeutral()` handler.** See `ArduinoCode/SYSTEM.md`.

---

## `SolenoidMapper`

Skill: `.agents/skills/solenoid-mapper/SKILL.md`

```cpp
SolenoidMapper(int pinS1, int pinS2, int pinSLU);
void begin();               // Sets OUTPUT + calls allOff() — safe startup state
void applyGear(int gear);   // 1–5; out-of-range silently calls allOff()
void allOff();              // De-energises all three solenoids
```

Truth table (verified, AW4 / A340E):
| Gear | S1 | S2 | SLU |
|---|---|---|---|
| 1 | ON | OFF | OFF |
| 2 | ON | ON | OFF |
| 3 | OFF | ON | OFF |
| 4 | OFF | OFF | OFF |
| 5 | OFF | OFF | ON |
| P/R/N | OFF | OFF | OFF |

Key behaviour:
- `begin()` calls `allOff()` — transmission starts in electrical failsafe (4th gear hydraulic)
- All state changes route through private `write(bool s1, bool s2, bool slu)` — single control point
- SLU is digital on/off on this AW4 variant — NOT PWM

---

## `ScreenIndication`

Skill: `.agents/skills/screen-indication/SKILL.md`

```cpp
ScreenIndication(int pinCS, int pinDC, int pinRST);
void begin();           // Initialises SSD1351, clears to black — call once in setup()
void showGear(int gear); // gear 1–4 → "1"/"2"/"3"/"4"; gear 5 → "4L"
void showPark();         // "P"
void showReverse();      // "R"
void showNeutral();      // "N" — also placeholder for 3rd hold (known issue)
void showLow();          // "L"
void showBlank();        // Clears screen — used for GEAR_SEL_UNKNOWN
```

Key behaviour:
- **Hardware SPI on Mega: DIN→51, CLK→52 — fixed, cannot be reassigned**
- **VCC: 3.3V only** — 5V permanently damages the display
- Driver: SSD1351 — do NOT call `initR()` (that is ST7735 only); use `_tft.begin()`
- Redraw guard: skips SPI write if displayed value has not changed

Known issue: `GEAR_SEL_THIRD` calls `showNeutral()` — displays "N" instead of "3". See SKILL.md for fix.
