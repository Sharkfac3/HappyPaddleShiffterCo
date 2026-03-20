# Trusted Sources Reference

Known-good and known-bad sources for this project. Check here before searching
to avoid wasting time on sites that consistently return 403.

---

## Factory Service Manuals — AW4 / Jeep XJ

| Source | URL | Status | Notes |
|---|---|---|---|
| Jeep XJ 1993 FSM — NSS continuity spec | https://jeep-manual.ru/index.php?page=294 | CONFIRMED ACCESSIBLE | NSS pin pairs verified here |
| Jeep XJ 1993 FSM — System/Component Tests | https://jeep-manual.ru/index.php?page=330 | CONFIRMED ACCESSIBLE | — |
| xjjeeps.com — 1984-1993 FSM PDF | https://cdn.xjjeeps.com/pdf/en-us/1984-1993-factory-service-manual.pdf | CONFIRMED ACCESSIBLE | General manual, not AW4-specific |
| xjjeeps.com — ATSG AW4 Service PDF | https://cdn.xjjeeps.com/pdf/en-us/aw4-transmission-service-information.pdf | CONFIRMED ACCESSIBLE | Excellent technical reference |
| Internet Archive — 1995 FSM | https://archive.org/details/jeepcherokeexjfactoryservicemanual1995ocr2182pages | CONFIRMED ACCESSIBLE | Large PDF, navigate carefully |
| jeep-manual.ru — 1997+ FSMs | Various pages | NOT YET FETCHED | Likely accessible based on 1993 success |

---

## Transmission — Solenoid Mapping

| Source | URL | Status | Notes |
|---|---|---|---|
| MaxxECU A340E/A341E wiring docs | https://www.maxxecu.com/webhelp/wirings-auto_transmission-toyota_a340e_a341e.html | CONFIRMED ACCESSIBLE | Solenoid truth table verified here |
| EveryCircuit AW4/A340 paddle shifter build | https://everycircuit.com/circuit/4930966876323840/ | CONFIRMED ACCESSIBLE | Community build, SLU on/off confirmed |
| Haltech A340E documentation | https://support.haltech.com/portal/en/kb/articles/toyota-a340e-control | BLOCKED (403) | Do not retry without proxy |
| RuseEFI — A340 thread | https://rusefi.com/forum/viewtopic.php?t=620 | BLOCKED (403) | — |

---

## NSS / Wiring Harness

| Source | URL | Status | Notes |
|---|---|---|---|
| Montana Fab AW4 Override Instructions | https://montanafab.com/wp-content/uploads/2018/01/tranny_instructions_rev.-5-20-16.pdf | CONFIRMED ACCESSIBLE | NSS wiring, solenoid wire colors by year |
| Cherokee Forum — NSS bypass diagram | https://www.cherokeeforum.com/f2/bypass-nss-wiring-diagram-161784/ | BLOCKED (403) | — |

---

## Open Source Controllers (for reference)

| Source | URL | Status | Notes |
|---|---|---|---|
| SCG-ATC — Arduino Mega ATC (dvjcodec) | https://github.com/dvjcodec/SCG-ATC | CONFIRMED ACCESSIBLE | Good reference architecture |
| dxControl-Gears (dvjcodec) | https://github.com/dvjcodec/dxControl-Gears | NOT YET FETCHED | Linked from SCG-ATC |
| Megasquirt — A340 thread | https://www.msextra.com/forums/viewtopic.php?t=57676 | BLOCKED (409) | — |

---

## Display

| Source | URL | Status | Notes |
|---|---|---|---|
| WaveShare 1.5" RGB OLED wiki | https://www.waveshare.com/wiki/1.5inch_RGB_OLED_Module | BLOCKED (403) | Try Wayback Machine |
| Adafruit SSD1351 library | https://github.com/adafruit/Adafruit-SSD1351-library | ACCESSIBLE | Install via Library Manager |

---

## Search Strategy Notes

- `site:jeep-manual.ru` searches are productive for FSM content
- `site:cdn.xjjeeps.com` hosts several confirmed PDFs — try guessing related filenames
- Community forums (cherokeeforum.com, pirate4x4.com) frequently block scrapers — use
  Google cache or Wayback Machine as fallback
- Toyota A340E specs are interchangeable with AW4 specs for solenoid mapping
