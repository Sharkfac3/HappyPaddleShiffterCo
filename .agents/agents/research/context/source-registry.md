# Source Registry — HappyPaddleShifterCo Research

Trusted domains, known-good URL patterns, and supplier sources. Check here before searching. Also check `SOURCES.md` to see what has already been fetched.

---

## Factory Service Manuals (FSMs)

The FSM is the authoritative source for OEM wiring, connector pinouts, and continuity specs.

| Source | Domain | Notes |
|---|---|---|
| jeep-manual.ru | `jeep-manual.ru` | Has XJ FSMs for 1987–2001; URL pattern is `?page=NNN`; many pages successfully fetched (see SOURCES.md) |
| xjjeeps.com CDN | `cdn.xjjeeps.com/pdf/` | PDF FSMs and service info; some PDFs loaded wrong sections — verify page loaded |
| Internet Archive | `archive.org` | Hosts scanned FSMs; OCR quality varies; NSS section may not be text-extractable |

**FSM lookup strategy:**
1. Try jeep-manual.ru first — best coverage and text-extractable
2. Fall back to xjjeeps.com CDN for service bulletins
3. Use archive.org as a last resort; escalate image-only pages to human

---

## Transmission Technical References

| Source | Domain | Reliability | Notes |
|---|---|---|---|
| MaxxECU A340E wiring docs | `maxxecu.com` | ✅ High | Confirmed solenoid mapping; successfully fetched |
| ATSG AW4 Service PDF | `cdn.xjjeeps.com` | ✅ High | Confirms NSS is continuity-based, not 12V powered |
| Montana Fab AW4 override instructions | `montanafab.com` | ✅ High | NSS wiring, solenoid wire colours by year |
| EveryCircuit AW4 paddle build | `everycircuit.com` | ✅ Medium | Community build; cross-reference with factory sources |
| SCG-ATC (dvjcodec) | `github.com/dvjcodec` | ✅ Medium | Open source A340 controller; useful for implementation patterns |

---

## Parts & Components

| Category | Trusted Suppliers | Notes |
|---|---|---|
| OEM replacement parts | RockAuto (`rockauto.com`), Omix-ADA (`omix-ada.com`) | Good for OEM-spec replacement NSS, solenoids |
| Electronic components | Digi-Key (`digikey.com`), Mouser (`mouser.com`), LCSC (`lcsc.com`) | Datasheets available for all active components |
| Arduino-compatible boards | Adafruit (`adafruit.com`), SparkFun (`sparkfun.com`) | Driver boards, relay boards; product pages have datasheets |
| 3D printing / hardware | Amazon, McMaster-Carr (`mcmaster.com`) | Hardware BOM items |

---

## Arduino / Electronics References

| Source | Domain | Notes |
|---|---|---|
| Arduino official reference | `docs.arduino.cc` | Pin modes, hardware SPI, `millis()`, etc. |
| Arduino forum | `forum.arduino.cc` | Community reference; confirm Mega SPI pins (51/52) |
| Adafruit SSD1351 library | `github.com/adafruit` | Library source and examples for the OLED display |
| Adafruit GFX docs | `adafruit.com` | Text sizing and centering reference |

---

## Known Good URL Patterns

```
# jeep-manual.ru FSM pages
https://jeep-manual.ru/index.php?page=294   ← NSS continuity spec (XJ 1993)
https://jeep-manual.ru/index.php?page=330   ← System/Component Tests

# ATSG AW4
https://cdn.xjjeeps.com/pdf/en-us/aw4-transmission-service-information.pdf

# Montana Fab AW4 override instructions
https://montanafab.com/wp-content/uploads/2018/01/tranny_instructions_rev.-5-20-16.pdf

# MaxxECU A340E
https://www.maxxecu.com/webhelp/wirings-auto_transmission-toyota_a340e_a341e.html
```

---

## NSS Part Numbers by Year

| Years | Connector Type | OEM Part | Aftermarket |
|---|---|---|---|
| 1987–1996 | 8-pin Deutsch, pins A–H | OEM 83503712 | Omix-ADA 17216.03 |
| 1997–2001 | Different physical housing | OEM 4882173 | Omix-ADA 4882173 |

> Wire colours differ by year and cannot be read from scanned FSM images. Verify with multimeter before wiring. See `known-blockers.md` for image-only FSM pages.
