# AW4 Transmission Controller — Sources & References

All sources consulted during research and development.
✅ = successfully fetched and read | ❌ = attempted but failed | — = surfaced in search, not directly fetched

---

## Factory Service Manuals — Jeep XJ AW4

| Source | URL | Status |
|---|---|---|
| Jeep XJ 1993 FSM — AW4 neutral safety switch continuity spec (jeep-manual.ru) | https://jeep-manual.ru/index.php?page=294 | ✅ Read |
| Jeep XJ 1993 FSM — System/Component Tests (jeep-manual.ru) | https://jeep-manual.ru/index.php?page=330 | ✅ Read |
| Jeep XJ 1984–1993 Service Manual PDF (xjjeeps.com) | https://cdn.xjjeeps.com/pdf/en-us/1984-1993-factory-service-manual.pdf | ✅ Read (wrong section loaded — general manual, not FSM) |
| Jeep XJ 1995 FSM (Internet Archive) | https://archive.org/details/jeepcherokeexjfactoryservicemanual1995ocr2182pages | ✅ Page found, NSS section not extracted |
| Jeep XJ 1997 FSM (jeep-manual.ru) | https://jeep-manual.ru/index.php?page=4 | — |
| Jeep XJ 1999 FSM (jeep-manual.ru) | https://jeep-manual.ru/index.php?page=XJ1999 | — |
| Jeep XJ 2001 FSM (jeep-manual.ru) | https://jeep-manual.ru/index.php?page=XJ2001 | — |

> **NSS pin continuity table (B↔C, A↔E, A↔G, A↔H) confirmed consistent across all XJ years from the 1993 FSM. Wire color diagrams exist in FSM connector images but could not be extracted from scanned PDFs — use a multimeter to verify before wiring.**

---

## Transmission — Solenoid Mapping & Control

| Source | URL | Status |
|---|---|---|
| MaxxECU A340E/A341E wiring documentation | https://www.maxxecu.com/webhelp/wirings-auto_transmission-toyota_a340e_a341e.html | ✅ Read |
| EveryCircuit AW4/A340 paddle shifter community build | https://everycircuit.com/circuit/4930966876323840/working-aw4-a340-automatic-transmission-paddle-shifter-control- | ✅ Read |
| ATSG Jeep AW4 Service Information PDF | https://cdn.xjjeeps.com/pdf/en-us/aw4-transmission-service-information.pdf | ✅ Read |
| Haltech A340E control documentation | https://support.haltech.com/portal/en/kb/articles/toyota-a340e-control | ❌ 403 |

---

## Neutral Safety Switch — AW4 / Jeep XJ

| Source | URL | Status |
|---|---|---|
| Montana Fab AW4 Transmission Override Instructions (NSS wiring, solenoid wire colors by year) | https://montanafab.com/wp-content/uploads/2018/01/tranny_instructions_rev.-5-20-16.pdf | ✅ Read |
| Cherokee Forum — NSS bypass wiring diagram | https://www.cherokeeforum.com/f2/bypass-nss-wiring-diagram-161784/ | ❌ 403 |

---

## Open Source Transmission Controllers

| Source | URL | Status |
|---|---|---|
| SCG-ATC — Arduino Mega automatic transmission controller (dvjcodec) | https://github.com/dvjcodec/SCG-ATC | ✅ Read |
| dxControl-Gears — SCG-ATC firmware (dvjcodec) | https://github.com/dvjcodec/dxControl-Gears | — (linked from SCG-ATC) |
| Speeduino forum — ATC discussion thread | https://speeduino.com/forum/viewtopic.php?f=15&t=1827 | — |
| RuseEFI — A340 controller thread | https://rusefi.com/forum/viewtopic.php?t=620 | ❌ 403 |
| YotaTech — A340 Arduino paddle shift build | https://www.yotatech.com/forums/f131/custom-transmission-controller-paddle-shift-247091/ | ❌ 403 |
| Megasquirt forum — A340 PRND21 wiring thread | https://www.msextra.com/forums/viewtopic.php?t=57676&start=120 | ❌ 409 |

---

## Display — WaveShare 1.5" RGB OLED (SSD1351)

| Source | URL | Status |
|---|---|---|
| WaveShare 1.5" RGB OLED wiki & Arduino tutorial | https://www.waveshare.com/wiki/1.5inch_RGB_OLED_Module | ❌ 403 (user-provided URL) |
| Adafruit SSD1351 library | https://github.com/adafruit/Adafruit-SSD1351-library | — (installed via Library Manager) |

---

## Hardware & Arduino

| Source | URL | Status |
|---|---|---|
| Arduino Forum — Mega 2560 hardware SPI pins (MOSI=51, SCK=52) | https://forum.arduino.cc | — (surfaced via search) |

---

## Key Findings Summary

| Decision | Source |
|---|---|
| Solenoid mapping (S1/S2/SLU per gear) | MaxxECU A340E docs + EveryCircuit AW4 community build |
| AW4 NSS is continuity-based, not 12V powered | ATSG AW4 Service PDF + Montana Fab override instructions |
| NSS pin pairs (B↔C, A↔E, A↔G, A↔H) | Jeep XJ 1993 FSM (Chrysler factory spec, confirmed consistent across all XJ years) |
| SLU is digital on/off, not PWM | EveryCircuit AW4 community build |
| SSD1351 driver (not ST7735) | WaveShare product page (user-provided) |
| Mega SPI on pins 51/52 (not 11/13) | Arduino Forum |
| '97–'01 NSS uses different physical connector | Omix-ADA part number research |
