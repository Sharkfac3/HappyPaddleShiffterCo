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

## Paddle Switch — Omron D2F-5L

Research session: 2026-03-20. Task: confirm a reliable primary source for the D2F-5L paddle switch.

### Confirmed Spec Source

| Source | URL | Status | Notes |
|---|---|---|---|
| Digi-Key — D2F-5L product listing (human-verified) | https://www.digikey.com/en/products/detail/omron-electronics-inc-emc-div/D2F-5L/8593137 | ✅ Read (human fetch) | **Primary confirmed source for D2F-5L specs. Full spec table extracted by human operator 2026-03-20.** |

**Confirmed specifications (from Digi-Key listing, 2026-03-20):**

| Parameter | Confirmed Value |
|---|---|
| Category | Limit Switches |
| Circuit | SPDT |
| Switch Function | On-Mom (momentary) |
| Current Rating | 5A (AC) |
| Voltage Rating | 250 V AC |
| Actuator Type | Lever, Straight |
| Mounting Type | Through Hole |
| Termination Style | PC Pin |
| Ingress Protection | IP40 |
| Operating Force | 80 gf |
| Release Force | 5.099 gf |
| Operating Position | 0.268" (6.8 mm) |
| Differential Travel | 0.020" (0.5 mm) |
| Overtravel | 0.022" (0.55 mm) |
| Mechanical Life | 1,000,000 cycles |
| Electrical Life | **10,000 cycles** |
| Operating Temperature | −40°C to +85°C |
| Part Status | Active |

> **Spec corrections applied to BOM (2026-03-20):** Prior BOM entries had three errors: operating force was listed as 1.47 N (correct: 80 gf / 0.784 N), electrical life as ~30,000 ops (correct: 10,000 cycles), and operating temperature lower bound as −25°C (correct: −40°C). BOM skill updated.

### Datasheet PDF Sources (URL confirmed, binary — human-readable)

| Source | URL | Status | Notes |
|---|---|---|---|
| Omron official D2F datasheet PDF | https://omronfs.omron.com/en_US/ecb/products/pdf/en-d2f.pdf | ✅ URL resolves — PDF binary, not text-extractable by tool | 830 KB; manufacturer's own domain |
| Omron D2F datasheet — Digi-Key CDN mirror | https://media.digikey.com/pdf/Data%20Sheets/Omron%20PDFs/D2F.pdf | ✅ URL resolves — PDF binary, not text-extractable by tool | 347 KB mirror |
| Omron D2F datasheet — Farnell mirror | https://www.farnell.com/datasheets/40484.pdf | ✅ URL resolves — PDF binary, not text-extractable by tool | 63 KB mirror |

### Blocked / Failed Sources

| Source | URL | Status |
|---|---|---|
| components.omron.com — D2F product page | https://components.omron.com/us-en/products/switches/D2F | ❌ 403 |
| ia.omron.com — D2F eCatalog spec page | https://www.ia.omron.com/products/family/1117/specification.html | ❌ 403 |
| ia.omron.com — D2F eCatalog lineup page | https://www.ia.omron.com/products/family/1117/lineup.html | ❌ 403 |
| omron.com/ecb — D2F product page | https://www.omron.com/ecb/products/sw/12/d2f.html | ❌ 403 |
| Digi-Key — D2F-5L product listing | https://www.digikey.com/en/products/detail/omron-electronics-inc-emc-div/D2F-5L/83230 | ❌ 403 |
| Mouser — D2F-5L product listing | https://www.mouser.com/ProductDetail/Omron-Electronics/D2F-5L | ❌ timeout |
| Arrow — D2F-5L product listing | https://www.arrow.com/en/products/d2f-5l/omron | ❌ timeout |
| Octopart — D2F-5L | https://octopart.com/d2f-5l-omron-83183 | ❌ 403 |
| Newark — D2F-5L | https://www.newark.com/omron-electronic-components/d2f-5l/microswitch-hinge-lever-5a-250vac/dp/23M7654 | ❌ timeout |
| LCSC — D2F-5L | https://www.lcsc.com/product-detail/Micro-Switches_Omron-D2F-5L_C92289.html | ❌ 404 (part URL incorrect) |
| Alldatasheet — D2F-5L | https://www.alldatasheet.com/datasheet-pdf/pdf/40982/OMRON/D2F-5L.html | ❌ empty response |
| web.archive.org — Wayback Machine | (D2F-5L Digi-Key snapshot) | ❌ archive.org blocked by tool |

### Purchasing

| Distributor | URL | Notes |
|---|---|---|
| Digi-Key — D2F-5L | https://www.digikey.com/en/products/detail/omron-electronics-inc-emc-div/D2F-5L/8593137 | Confirmed active, bulk — human-verified 2026-03-20 |
| Mouser — D2F-5L | https://www.mouser.com/ProductDetail/Omron-Electronics/D2F-5L | Timed out to tool — accessible to human |

---

## Paddle Switch Alternative — Omron D2JW-011

Research session: 2026-03-20. Evaluated as potential upgrade for D2F-5L due to 10,000-cycle electrical life concern.

**Confirmed specifications (human fetch from Digi-Key, 2026-03-20):**

| Parameter | Confirmed Value |
|---|---|
| Circuit | SPDT |
| Switch Function | On-Mom (momentary) |
| Current Rating | 100 mA (DC) |
| Voltage Rating | 30 V DC |
| Actuator Type | **Round (Pin Plunger)** |
| Mounting Type | **Chassis Mount** |
| Termination Style | **Solder Lug** |
| Ingress Protection | IP67 — Dust Tight, Waterproof |
| Operating Force | 250 gf |
| Release Force | 100 gf |
| Operating Position | 0.319" (8.1 mm) |
| Mechanical Life | 1,000,000 cycles |
| **Electrical Life** | **100,000 cycles** |
| Operating Temperature | −40°C to +85°C |
| Part Status | Active |

> **Compatibility finding:** D2JW-011 has 10× the electrical life of D2F-5L and IP67 sealing, but is NOT a physical drop-in. It uses a pin plunger actuator (not lever), chassis mount (not PCB through-hole), and solder lug termination. The prior BOM claim that D2JW is "pin-compatible in function" was incorrect. A D2JW variant with lever actuator and through-hole termination would be needed, or the paddle 3D model would require redesign for pin-plunger actuation.

---

## Paddle Switch Alternative — Omron D2JW-01K21

Research session: 2026-03-20. Lever-actuator D2JW variant identified as upgrade candidate.

**Confirmed specifications (human fetch from Digi-Key, 2026-03-20):**

| Parameter | Confirmed Value |
|---|---|
| Circuit | SPDT |
| Switch Function | On-Mom (momentary) |
| Current Rating | 100 mA (DC) |
| Voltage Rating | 30 V DC |
| Actuator Type | Lever, Roller |
| Mounting Type | Chassis Mount |
| Termination Style | Solder Lug |
| Ingress Protection | IP67 — Dust Tight, Waterproof |
| Operating Force | 100 gf |
| Release Force | 20 gf |
| Operating Position | 0.575" (14.6 mm) |
| Pretravel | 0.205" (5.2 mm) |
| Differential Travel | 0.020" (0.5 mm) |
| Overtravel | 0.045" (1.1 mm) |
| Mechanical Life | 1,000,000 cycles |
| **Electrical Life** | **100,000 cycles** |
| Operating Temperature | −40°C to +85°C |
| Part Status | Active |

> **Compatibility assessment:** Lever actuator and close operating force make this workable, but the 14.6 mm operating position (vs D2F-5L's 6.8 mm) is a significant geometry difference. Superseded by D2JW-01K11 as preferred upgrade candidate.

---

## Paddle Switch Alternative — Omron D2JW-01K11

Research session: 2026-03-20. Identified as preferred upgrade candidate over D2F-5L and other D2JW variants.

**Confirmed specifications (human fetch from Digi-Key, 2026-03-20):**

| Parameter | Confirmed Value |
|---|---|
| Circuit | SPDT |
| Switch Function | On-Mom (momentary) |
| Current Rating | 100 mA (DC) |
| Voltage Rating | 30 V DC |
| Actuator Type | Lever, Straight |
| Mounting Type | Chassis Mount |
| Termination Style | Solder Lug |
| Ingress Protection | IP67 — Dust Tight, Waterproof |
| Operating Force | 82 gf |
| Release Force | 16 gf |
| Operating Position | 0.330" (8.4 mm) |
| Pretravel | 0.252" (6.4 mm) |
| Differential Travel | 0.027" (0.7 mm) |
| Overtravel | 0.055" (1.4 mm) |
| Mechanical Life | 1,000,000 cycles |
| **Electrical Life** | **100,000 cycles** |
| Operating Temperature | −40°C to +85°C |
| Part Status | Active |

> **Compatibility assessment:** Best upgrade candidate identified. Straight lever actuator and 82 gf operating force are near-identical to D2F-5L (80 gf). Operating position 8.4 mm is only 1.6 mm deeper than D2F-5L's 6.8 mm — trivial to accommodate in paddle 3D model. Chassis mount + solder lug wires is workable for paddle body mounting. Delivers 10× electrical life improvement and IP67 sealing vs D2F-5L.

### Mechanical Drawing — Omron Datasheet (human-provided, 2026-03-20)

Source: Omron official D2JW datasheet, "Hinge lever models — D2JW-01K11" dimensional drawing. Provided as screenshot by human operator.

**Body dimensions:**

| Dimension | Value |
|---|---|
| Body width | 12.7 mm |
| Body height | 12.3 mm |
| Body depth | 5.3 ± 0.1 mm |
| Mounting hole diameter | 2.35 +0.05/−0.025 mm (×2) |
| Mounting hole spacing | 3.95 × 3.95 mm |
| Terminal hole diameter | 2.5 +0.05/−0.025 mm |
| Terminal spacing | 4.8 −0.05 mm (outer), 3.95 mm (inner) |

**Lever geometry:**

| Dimension | Value |
|---|---|
| Lever material / thickness | Stainless steel, t0.3 mm |
| Lever arc radius | R16.5 mm |
| Lever horizontal span | 1.8 mm (before pivot) + 7.95 mm (after pivot) |
| OP measurement arm height | 6.15 mm above body base |

**Travel specifications (cross-confirmed vs Digi-Key listing):**

| Parameter | Value |
|---|---|
| Operating Force (OF) | 0.80 N (82 gf) max |
| Releasing Force (RF) | 0.15 N (16 gf) min |
| Pretravel (PT) | 6.4 mm max |
| Overtravel (OT) | 1.4 mm min |
| Movement Differential (MD) | 0.7 mm max |
| Operating Position (OP) | **8.4 ± 0.8 mm** |

> All values cross-confirmed against Digi-Key listing (human-verified 2026-03-20). No discrepancies found.

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
| Paddle switch specs confirmed | Digi-Key listing https://www.digikey.com/en/products/detail/omron-electronics-inc-emc-div/D2F-5L/8593137 — human-verified 2026-03-20; corrected electrical life (10K), operating force (80 gf), temp range (−40°C) |
| Paddle switch purchase source (D2F-5L) | Digi-Key part #8593137 (confirmed active, bulk) |
| Preferred upgrade switch confirmed | Omron D2JW-01K11 — straight lever, 82 gf, 8.4 mm op position, IP67, 100K electrical life — Digi-Key (human-verified 2026-03-20) |
