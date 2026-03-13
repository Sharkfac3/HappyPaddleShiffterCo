#include "ScreenIndication.h"

ScreenIndication::ScreenIndication(int pinCS, int pinDC, int pinRST)
    : _tft(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, pinCS, pinDC, pinRST),
      _lastDisplayed("")
{}

void ScreenIndication::begin() {
    // begin() initializes hardware SPI and sends the SSD1351 init sequence
    _tft.begin();
    _tft.fillScreen(SSD1351_BLACK);
    _lastDisplayed = "";
}

void ScreenIndication::renderText(const String& text, uint16_t color) {
    // Skip redraw if display value hasn't changed — prevents flicker
    if (text == _lastDisplayed) return;

    _tft.fillScreen(SSD1351_BLACK);
    _tft.setTextColor(color);

    // Single characters use large text size 8 (~48px tall) for visibility while driving
    // Two-character strings (e.g. "4L") use size 5 to fit on 128px wide screen
    int textSize  = (text.length() > 1) ? 5 : 8;
    int charW     = 6 * textSize;   // Adafruit GFX: 6px per char width unit
    int charH     = 8 * textSize;   // Adafruit GFX: 8px per char height unit
    int textWidth = text.length() * charW;

    // Center on 128x128 display
    int x = (SCREEN_WIDTH  - textWidth) / 2;
    int y = (SCREEN_HEIGHT - charH)     / 2;

    _tft.setTextSize(textSize);
    _tft.setCursor(x, y);
    _tft.print(text);

    _lastDisplayed = text;
}

void ScreenIndication::showGear(int gear) {
    String label;
    switch (gear) {
        case 1:  label = "1";  break;
        case 2:  label = "2";  break;
        case 3:  label = "3";  break;
        case 4:  label = "4";  break;
        case 5:  label = "4L"; break;
        default: label = "?";  break;
    }
    renderText(label, SSD1351_WHITE);
}

void ScreenIndication::showPark()    { renderText("P", SSD1351_WHITE); }
void ScreenIndication::showReverse() { renderText("R", SSD1351_WHITE); }
void ScreenIndication::showNeutral() { renderText("N", SSD1351_WHITE); }
void ScreenIndication::showLow()     { renderText("L", SSD1351_WHITE); }

void ScreenIndication::showBlank() {
    if (_lastDisplayed == "") return; // Already blank
    _tft.fillScreen(SSD1351_BLACK);
    _lastDisplayed = "";
}
