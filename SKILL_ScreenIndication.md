# Skill: ScreenIndication

## Purpose
Drives the WaveShare 1.5" RGB OLED (SSD1351, 128×128) to display current gear/selector state.

## Hardware
- Driver: SSD1351 (NOT ST7735)
- VCC: 3.3V only — 5V will destroy display
- DIN → Mega pin 51 (hardware MOSI, fixed)
- CLK → Mega pin 52 (hardware SCK, fixed)
- CS → A5, DC → A4, RES → A3 (user-assigned)
- Library: Adafruit_SSD1351 + Adafruit_GFX

## Constructor
```cpp
Adafruit_SSD1351(128, 128, &SPI, pinCS, pinDC, pinRST)
```
Init with `_tft.begin()`. No initR() — that is ST7735 only.

## Display Values
| Method | Shows |
|---|---|
| showGear(1–4) | "1" "2" "3" "4" |
| showGear(5) | "4L" |
| showPark() | "P" |
| showReverse() | "R" |
| showNeutral() | "N" |
| showLow() | "L" |
| showBlank() | clears screen |

## Behavior
- Single char: textSize 8 — centered on 128×128
- Two chars ("4L"): textSize 5 — centered on 128×128
- Only redraws if `_lastDisplayed` has changed (prevents flicker)
- Color constants: `SSD1351_WHITE`, `SSD1351_BLACK`

## Interface
```cpp
ScreenIndication(int pinCS, int pinDC, int pinRST);
void begin();
void showGear(int gear);
void showPark();
void showReverse();
void showNeutral();
void showLow();
void showBlank();
```
