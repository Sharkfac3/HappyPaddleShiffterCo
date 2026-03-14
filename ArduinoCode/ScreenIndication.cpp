#include "ScreenIndication.h"

// =============================================================================
// ScreenIndication.cpp
//
// Wrapper around the Adafruit SSD1351 library for the WaveShare 1.5" RGB OLED
// (128×128 pixels, SSD1351 driver, 3.3V ONLY).
//
// Hardware SPI is used for maximum write speed (DIN→pin51, CLK→pin52 on Mega).
// CS, DC, and RST are user-assigned digital output pins (A5, A4, A3 in .ino).
//
// Rendering is guarded by a _lastDisplayed cache — the screen is only redrawn
// when the displayed value changes. This avoids the visible flicker that would
// result from clearing and re-drawing every loop() cycle.
//
// Text sizing:
//   Single character  (P, R, N, 1–4, L) : textSize 8  (~48px tall — easy to read at a glance)
//   Two characters    (4L)               : textSize 5  — scaled down to fit the 128px width
// Both are centered on the 128×128 canvas using Adafruit GFX character metrics
// (6px per unit wide × textSize, 8px per unit tall × textSize).
// =============================================================================

ScreenIndication::ScreenIndication(int pinCS, int pinDC, int pinRST)
    : _tft(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, pinCS, pinDC, pinRST),
      _lastDisplayed("")  // Empty string = nothing displayed yet
{}

// -----------------------------------------------------------------------------
// begin() — initialise hardware SPI and the SSD1351, then clear the screen.
// Must be called once in setup() before any show*() calls.
// NOTE: Use _tft.begin() (SSD1351 API) — NOT initR() (that is ST7735 only).
// -----------------------------------------------------------------------------
void ScreenIndication::begin() {
    _tft.begin();
    _tft.fillScreen(SSD1351_BLACK);
    _lastDisplayed = "";  // Reset cache to match the now-blank display
}

// -----------------------------------------------------------------------------
// renderText() — private core renderer.
//
// Clears the screen, then draws `text` centered on the 128×128 canvas.
// Skips the redraw entirely if `text` matches what is already displayed.
//
// Parameters:
//   text  — the string to display (1 or 2 characters)
//   color — 16-bit RGB565 colour constant (e.g. SSD1351_WHITE)
// -----------------------------------------------------------------------------
void ScreenIndication::renderText(const String& text, uint16_t color) {
    // Guard: skip if already showing this value — prevents flicker
    if (text == _lastDisplayed) return;

    // Clear the previous content
    _tft.fillScreen(SSD1351_BLACK);
    _tft.setTextColor(color);

    // Choose text size based on character count:
    //   1 char  → size 8 (large, easy to read while driving)
    //   2+ chars → size 5 (fits "4L" within 128px width)
    int textSize  = (text.length() > 1) ? 5 : 8;

    // Adafruit GFX character metrics: each glyph cell is 6×8 base units
    int charW     = 6 * textSize;   // Pixel width per character
    int charH     = 8 * textSize;   // Pixel height per character
    int textWidth = text.length() * charW;

    // Calculate top-left cursor position to center the string on the canvas
    int x = (SCREEN_WIDTH  - textWidth) / 2;
    int y = (SCREEN_HEIGHT - charH)     / 2;

    _tft.setTextSize(textSize);
    _tft.setCursor(x, y);
    _tft.print(text);

    // Update cache so we don't redraw until the value changes
    _lastDisplayed = text;
}

// -----------------------------------------------------------------------------
// showGear() — display the current gear number.
//
// gear 1–4 renders as "1"/"2"/"3"/"4".
// gear 5   renders as "4L" (4th gear + torque converter lockup).
// Any other value renders "?" as an error indicator.
// -----------------------------------------------------------------------------
void ScreenIndication::showGear(int gear) {
    String label;
    switch (gear) {
        case 1:  label = "1";  break;
        case 2:  label = "2";  break;
        case 3:  label = "3";  break;
        case 4:  label = "4";  break;
        case 5:  label = "4L"; break;  // 4th + lockup — two chars, uses smaller text size
        default: label = "?";  break;  // Should never occur; signals a logic error
    }
    renderText(label, SSD1351_WHITE);
}

// One-liner show methods — each renders a single fixed character in white.
// They all delegate to renderText() which handles the redraw guard.
void ScreenIndication::showPark()    { renderText("P", SSD1351_WHITE); }
void ScreenIndication::showReverse() { renderText("R", SSD1351_WHITE); }
void ScreenIndication::showNeutral() { renderText("N", SSD1351_WHITE); }  // Also used as 3rd-hold placeholder — see SKILL_ScreenIndication.md
void ScreenIndication::showLow()     { renderText("L", SSD1351_WHITE); }

// -----------------------------------------------------------------------------
// showBlank() — clear the display (used during GEAR_SEL_UNKNOWN transitions).
//
// Skips the fill if the display is already blank (_lastDisplayed == "") to
// avoid an unnecessary SPI write every loop cycle during unknown state.
// -----------------------------------------------------------------------------
void ScreenIndication::showBlank() {
    if (_lastDisplayed == "") return;   // Already blank — nothing to do
    _tft.fillScreen(SSD1351_BLACK);
    _lastDisplayed = "";
}
