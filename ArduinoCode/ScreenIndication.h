#ifndef SCREEN_INDICATION_H
#define SCREEN_INDICATION_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

// ScreenIndication
// Wraps the WaveShare 1.5" 128x128 RGB OLED display (SSD1351 driver chip).
//
// Uses hardware SPI on the Arduino Mega 2560:
//   Display DIN  → Arduino Mega pin 51 (MOSI) — hardware SPI, fixed, not reassignable
//   Display CLK  → Arduino Mega pin 52 (SCK)  — hardware SPI, fixed, not reassignable
//   Display CS   → Arduino Mega pin 44 (digital output, active LOW)
//   Display DC   → Arduino Mega pin 45 (digital output, HIGH=data LOW=command)
//   Display RES  → Arduino Mega pin 46 (digital output, LOW=reset)
//   Display VCC  → 3.3V ONLY  (do NOT use 5V — will damage the OLED)
//   Display GND  → GND
//
// IMPORTANT: CS, DC, and RST must be proper digital output pins.
// Do NOT use analog-only pins (A0–A15) for these — they will not work
// reliably as SPI control lines on the Mega.
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
    String _lastDisplayed;

    void renderText(const String& text, uint16_t color);
};

#endif
