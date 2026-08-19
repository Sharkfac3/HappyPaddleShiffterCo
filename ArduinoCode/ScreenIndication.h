#ifndef SCREEN_INDICATION_H
#define SCREEN_INDICATION_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

// ScreenIndication
// Wraps the WaveShare 1.5" 128x128 RGB OLED display (SSD1351 driver chip).
//
// Uses hardware SPI. Supports Arduino Uno (default), Mega 2560, and Nano —
// the Adafruit_SSD1351 library auto-selects the board's fixed MOSI/SCK pins,
// no code change needed between boards:
//   Display DIN  → hardware MOSI (Uno/Nano pin 11 / Mega pin 51) — fixed, not reassignable
//   Display CLK  → hardware SCK  (Uno/Nano pin 13 / Mega pin 52) — fixed, not reassignable
//   Display CS   → A5 (digital output, active LOW)
//   Display DC   → A4 (digital output, HIGH=data LOW=command)
//   Display RES  → A3 (digital output, LOW=reset)
//   Display VCC  → 3.3V ONLY  (do NOT use 5V — will damage the OLED)
//   Display GND  → GND
//
// IMPORTANT: CS, DC, and RST must be proper digital output pins. A3-A5 work
// fine as digital outputs on both Uno and Mega (same technique used here).
//
// Library: Adafruit_SSD1351 (install via Arduino Library Manager)
// Depends on: Adafruit_GFX
//
// Supported display values:
//   showGear(1-4) → "1", "2", "3", "4"
//   showGear(5)   → "4L" (4th + lockup)
//   showPark()    → "P"
//   showReverse() → "R"
//   showNeutral() → "N"
//   showLow()     → "L" (manual Low/1st hold from selector)
//   showBlank()   → clears screen (used during UNKNOWN/transitioning)
//
// Only redraws if the displayed value has changed — prevents flicker.

#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128

// Adafruit_SSD1351 library does not ship BLACK/WHITE constants under a
// SSD1351_ prefix (only unprefixed BLACK/WHITE in its own example sketch).
// Defined here to avoid colliding with other libraries' color macros.
#define SSD1351_BLACK 0x0000
#define SSD1351_WHITE 0xFFFF

class ScreenIndication {
public:
    // pinCS  → Display CS  (any digital pin)
    // pinDC  → Display DC  (any digital pin)
    // pinRST → Display RES (any digital pin)
    ScreenIndication(int pinCS, int pinDC, int pinRST);

    void begin();

    void showGear(int gear);   // gear 1–5 (5 = "4L")
    void showPark();           // "P"
    void showReverse();        // "R"
    void showNeutral();        // "N"
    void showLow();            // "L"
    void showBlank();          // Clears display

private:
    Adafruit_SSD1351 _tft;
    char _lastDisplayed[3];  // Max displayed value is "4L" + null terminator

    void renderText(const char* text, uint16_t color);
};

#endif
