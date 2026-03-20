# Existing Class API Reference

Quick reference for the public interfaces of all four subsystem classes.
For full context (electrical facts, behaviour notes, modification guidance)
load the corresponding skill from `.agents/skills/`.

---

## PaddleShiftIndication

**Files:** `ArduinoCode/PaddleShiftIndication.h/.cpp`
**Skill:** `.agents/skills/paddle-shift-indication/SKILL.md`

```cpp
PaddleShiftIndication(int pinUp, int pinDown);
void begin();               // Call once in setup() — configures INPUT_PULLUP
void update();              // Call every loop() — samples pins, updates flags
bool shiftUpRequested();    // True once per press, then auto-resets
bool shiftDownRequested();  // True once per press, then auto-resets
```

Key: Both pins are INPUT_PULLUP active LOW. Debounce is 50ms timestamp-based.
Flags are consumed-and-cleared by the accessor — do not reset manually.

---

## GearSelectorSwitch

**Files:** `ArduinoCode/GearSelectorSwitch.h/.cpp`
**Skill:** `.agents/skills/gear-selector-switch/SKILL.md`

```cpp
GearSelectorSwitch(int pinPN, int pinR, int pin3, int pin12);
void begin();
void update();
GearSelectorState getState();
bool justEnteredParkNeutral();
bool justEnteredReverse();
bool justEnteredDrive();
bool justEnteredThird();
bool justEnteredOneTwo();
```

State enum values: `GEAR_SEL_PARK_NEUTRAL`, `GEAR_SEL_REVERSE`, `GEAR_SEL_DRIVE`,
`GEAR_SEL_THIRD`, `GEAR_SEL_ONE_TWO`, `GEAR_SEL_UNKNOWN`.

Key: All pins INPUT_PULLUP active LOW. Drive is detected by absence (all pins HIGH).
UNKNOWN fires when multiple pins are simultaneously LOW (mid-travel transition).
`justEntered*()` flags auto-clear on the next `update()` call.

---

## SolenoidMapper

**Files:** `ArduinoCode/SolenoidMapper.h/.cpp`
**Skill:** `.agents/skills/solenoid-mapper/SKILL.md`

```cpp
SolenoidMapper(int pinS1, int pinS2, int pinSLU);
void begin();               // Sets OUTPUT + calls allOff()
void applyGear(int gear);   // Gear 1–5; out-of-range falls back to allOff()
void allOff();              // De-energises all three solenoids
```

Solenoid truth table (verified):
| Gear | S1 | S2 | SLU |
|---|---|---|---|
| 1 | ON | OFF | OFF |
| 2 | ON | ON | OFF |
| 3 | OFF | ON | OFF |
| 4 | OFF | OFF | OFF |
| 5 | OFF | OFF | ON |
| P/R/N | OFF | OFF | OFF |

Key: 4th (all off) is the electrical failsafe. Solenoids run on 12V via driver board.

---

## ScreenIndication

**Files:** `ArduinoCode/ScreenIndication.h/.cpp`
**Skill:** `.agents/skills/screen-indication/SKILL.md`

```cpp
ScreenIndication(int pinCS, int pinDC, int pinRST);
void begin();           // Initialises SSD1351, clears to black
void showGear(int gear); // 1–4 → "1"/"2"/"3"/"4", 5 → "4L"
void showPark();        // "P"
void showReverse();     // "R"
void showNeutral();     // "N" (also used as 3rd-hold placeholder — known issue)
void showLow();         // "L"
void showBlank();       // Clears screen
```

Key: Hardware SPI — DIN→51, CLK→52, fixed on Mega. Display is 3.3V ONLY.
Has redraw guard: skips SPI write if display content has not changed.

Known issue: `showNeutral()` is called for GEAR_SEL_THIRD (displays "N" not "3").
See `screen-indication` skill for the `showThird()` fix.
