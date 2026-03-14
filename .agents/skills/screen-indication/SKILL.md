---
name: screen-indication
description: Modify or debug the ScreenIndication class — the SSD1351 OLED display wrapper for the Jeep XJ paddle shifter controller. Use when changing what is displayed for each gear or selector state, adding new display modes, or fixing display rendering issues. Source files are ArduinoCode/ScreenIndication.h and ArduinoCode/ScreenIndication.cpp.
---

# Skill: screen-indication

Wrapper around the Adafruit SSD1351 library for the WaveShare 1.5″ RGB OLED (128×128,
SSD1351 driver, 3.3V only). Displays current gear or selector state as a large centred
character or short string.

## Key Hardware Facts

- **Driver chip: SSD1351** — NOT ST7735. Do NOT call `initR()` (that is ST7735 only). Use `_tft.begin()`.
- **VCC: 3.3V only** — 5V will permanently damage the display
- **Hardware SPI on Mega** — DIN → pin 51 (MOSI), CLK → pin 52 (SCK). These are fixed; they cannot be reassigned.
- CS, DC, RST are user-assigned digital output pins (currently A5, A4, A3 in ArduinoCode.ino)

| Display Pin | Arduino Mega Pin | Notes |
|---|---|---|
| DIN | 51 | Hardware MOSI — fixed |
| CLK | 52 | Hardware SCK — fixed |
| CS | A5 | Chip select |
| DC | A4 | Data/command |
| RES | A3 | Reset |
| VCC | 3.3V | 3.3V ONLY |
| GND | GND | — |

## Source Files

- `ArduinoCode/ScreenIndication.h` — class declaration, `SCREEN_WIDTH`/`SCREEN_HEIGHT` constants
- `ArduinoCode/ScreenIndication.cpp` — `renderText()` core renderer, all `show*()` methods

## Public Interface

```cpp
ScreenIndication(int pinCS, int pinDC, int pinRST);
void begin();               // Initialises SPI + SSD1351, clears to black — call once in setup()
void showGear(int gear);    // gear 1–4 → "1"/"2"/"3"/"4", gear 5 → "4L"
void showPark();            // "P"
void showReverse();         // "R"
void showNeutral();         // "N" — also used as 3rd-hold placeholder (see note below)
void showLow();             // "L"
void showBlank();           // Clears screen — used during GEAR_SEL_UNKNOWN
```

## Rendering Behaviour

- Single character (P, R, N, L, 1–4): `textSize 8` (~48px tall) — centered on 128×128
- Two characters (4L): `textSize 5` — centered on 128×128
- Adafruit GFX metrics: 6px wide × 8px tall per base unit, scaled by textSize
- **Redraw guard:** `renderText()` compares against `_lastDisplayed` and skips the SPI write entirely if the value has not changed — prevents flicker on every `loop()` call

## Known Issue — 3rd Hold Display

The `GEAR_SEL_THIRD` selector position currently calls `showNeutral()` in `ArduinoCode.ino`,
which renders "N" instead of "3".

**To fix:** Add a `showThird()` method to `ScreenIndication.h/.cpp`:

```cpp
// In ScreenIndication.h — add to public interface:
void showThird();

// In ScreenIndication.cpp:
void ScreenIndication::showThird() { renderText("3", SSD1351_WHITE); }
```

Then update both call sites in `ArduinoCode.ino` (search for `TODO: currently shows "N"`).

## Adding a New Display Mode

1. Add the method declaration to `ScreenIndication.h`
2. Implement in `ScreenIndication.cpp` — call `renderText("<label>", SSD1351_WHITE)` (or another colour)
3. Call the new method from `ArduinoCode.ino` at the appropriate state transition
