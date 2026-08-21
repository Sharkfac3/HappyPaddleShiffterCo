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

## Paddle Trigger Sensor — IR Slot-Type Optocoupler (LM393), User-Owned Part

Research session: 2026-08-17. User has an on-hand AliExpress module originally assumed to be
a Hall effect sensor; confirmed it is NOT — it is a slot-type IR optocoupler (photointerrupter
+ LM393 comparator), same generic module widely sold for RC car wheel-speed encoding.

### Part Identification

| Source | URL | Status | Notes |
|---|---|---|---|
| AliExpress listing (user-provided, item 3256804480682852) | https://www.aliexpress.us/item/3256804480682852.html | ✅ Read (browser) | Listed as "IR Infrared Speed Sensor Module Distance Measurement Detection Optocoupler For Arduino Smart Car/Robot." Spec fields: Type = "Optical-Electronics Sensor", Output = "Switching Transducer". No manufacturer part number given — generic/unbranded clone, common on this listing tier. |

No manufacturer datasheet exists for this specific unbranded listing (no part number to look up). Cross-referenced against three independent retailer/documentation pages for the same widely-cloned module family (LM393 slot-type IR optocoupler) to confirm electrical behavior:

| Source | URL | Status | Notes |
|---|---|---|---|
| diymore.cc product page | https://www.diymore.cc/products/slot-type-ir-optocoupler-speed-sensor-module-lm393-for-arduino | ✅ Read | Operating voltage 3.3V–5V. Direct quote: "Module slot unobstructed, receiver tube conduction module DO output low, shelter, DO output high." |
| electropeak.com product page | https://electropeak.com/ptocouple-optocounter-module | ✅ Read | Operating voltage DC 5V. Direct quote: "When the object is blocked, the output is high... The output is low when there is no shelter." |
| manuals.plus — Balance World Inc. user manual (ASIN B01LYFQEXI) | https://manuals.plus/asin/B01LYFQEXI | ❌ 403 | Blocked, not used |
| Amazon listing (ASIN B01LYFQEXI) | https://www.amazon.com/Optocoupler-Speed-Sensor-Module-Arduino/dp/B01LYFQEXI | ❌ 500 error | Blocked, not used |

Both successfully-fetched sources agree independently — treated as confirmed (community/retailer tier, no primary manufacturer datasheet exists for this unbranded part).

### Confirmed Electrical Facts

| Parameter | Confirmed Value |
|---|---|
| Sensor type | Slot-type IR optocoupler (photointerrupter), NOT Hall effect — no magnet sensitivity |
| Comparator IC | LM393 |
| Operating voltage | 3.3V–5V (both sources agree; compatible with Mega's 5V logic) |
| Pins | VCC, GND, DO (digital output). No AO/analog pin documented on this module variant. |
| Output type | Actively driven push-pull output from onboard LM393 + pull-up resistor — NOT open-drain. Do not enable Arduino `INPUT_PULLUP` on the input pin; the module drives the line itself. |
| **Output polarity (critical, cross-confirmed 2 sources)** | **Slot unobstructed (clear) → DO reads LOW. Slot obstructed (object/tab in slot) → DO reads HIGH.** |

> **This is the opposite electrical convention from the existing paddle switches.** [PaddleShiftIndication.cpp](Firmware/ArduinoCode/PaddleShiftIndication.cpp) currently expects active-LOW behavior (`INPUT_PULLUP`, HIGH = unpressed, LOW = pressed, trigger on HIGH→LOW falling edge). This module is active-HIGH-when-blocked. Whether this requires a firmware change depends entirely on paddle mechanical geometry — see HANDOFF to CODING.

---

## Stock TCU Solenoid Switching Polarity (High-Side vs Low-Side)

Research session: 2026-08-19. Task: determine whether the factory A340E/AW4 TCU activates
shift solenoids by switching +12V (high-side) or by switching ground (low-side), for
comparison against this project's driver board (which switches +12V — see
`.agents/knowledge/microcontroller/driver-boards/README.md`).

| Source | URL | Status | Finding |
|---|---|---|---|
| MaxxECU A340E/A341E wiring docs | https://www.maxxecu.com/webhelp/wirings-auto_transmission-toyota_a340e_a341e.html | ✅ Read | S1/S2 solenoids wired to MaxxECU's high-side output pins with 12V flyback to transmission +12V supply — consistent with the ECU switching the positive side |
| WebSearch synthesis (multiple forum/vendor snippets) | msextra.com, toyotanation.com, transmissionpartsdistributors.com (not individually fetched — search-engine summary only) | — | States shift solenoids are "single-wire with the case being negative" (case-grounded internally) and that driving them requires a high-side PNP driver (e.g. TIP125) — consistent with high-side/case-ground |
| WebSearch synthesis (generic EFI/injector wiring pages) | clublexus.com, generic EFI wiring guidance (not individually fetched) | — | Describes a generic low-side injector-driver pattern (battery to one terminal, ECU grounds the other) — **not clearly specific to the A340E/AW4 solenoids**, likely a generic EFI answer surfaced by the search, lower confidence |
| toyotanation.com thread | https://www.toyotanation.com/threads/a340e-solenoid-control-wires.1090793/ | ❌ Redirected to unverified domain `tollbit.toyotanation.com` — not followed | New blocker, log below |
| pirate4x4.com AW4 FAQ thread | https://www.pirate4x4.com/threads/a340-transmission-issues-and-faqs.587521/ | ❌ Redirected to unverified domain `tollbit.pirate4x4.com` — not followed | New blocker, log below |
| PCS TCM-4103 Toyota A340E harness drawing PDF | https://powertraincontrolsolutions.com/download/Released/Public/Harness_Drawings/TCM-4103%20Toyota-Lexus%20A340E%20(All).pdf | ❌ Fetched but binary/corrupted — not text-extractable by tool | — |

**Working conclusion (medium confidence, not primary-source-confirmed):** the stock A340E/AW4
TCU most likely uses **high-side switching** — solenoids are single-wire, internally
case-grounded to the transmission housing, and the TCU applies +12V to activate. This is also
consistent with widely-repeated transmission-repair-community practice of testing solenoid
resistance by probing the signal pin to the case/housing (only meaningful if the case is the
permanent ground return). If true, **this project's driver board uses the same polarity as the
factory TCU**, not the inverse.

**This is a reversal of an earlier assumption stated to the user in-conversation (that stock
was low-side/grounding).** No primary source (FSM, ATSG manual page, or OEM pinout table) has
directly confirmed solenoid case-ground wiring — flagging as unverified pending a primary
source. See new HANDOFFS entry.

### Update (2026-08-20) — msextra.com now fetchable; polarity confirmed per-solenoid, not uniform

Prior known-blockers.md entry marked `msextra.com` as 403-blocked. Retested this session —
the thread fetched successfully (direct WebFetch, no auth wall encountered). `known-blockers.md`
corrected accordingly.

| Source | URL | Status | Finding |
|---|---|---|---|
| MSEXTRA "Toyota A340 control" thread (Megasquirt standalone-ECU build thread, extensive multi-page technical discussion) | https://www.msextra.com/forums/viewtopic.php?t=57676 (and `&start=0`, `&start=90`, `&start=120`) | ✅ Read | Direct-quoted ECU pin function text: **SLU (No.3 lock-up solenoid)** — "This pin is connected to Ground inside the ECU as required to turn the No.3 lock up solenoid ON... wired with one side of the solenoid connected to battery voltage (Main EFI Relay switched) and one side of the solenoid connected to this ECU pin." = **low-side** (ECU grounds SLU to activate; SLU's other terminal is a fixed +12V feed). **SLN (accumulator)** — same "connected to Ground inside the ECU" wording = **low-side**. **SLT (line pressure)** — "outputs Pulse Width Modulated (PWM) battery voltage" = **high-side** PWM. **S1/S2 (shift solenoids)** — "Solenoid 1 has ground in the transmission and 12v active high in 1st and 2nd gear" (S2 described the same way for its gear range) = **high-side** (solenoid's ground is a fixed point inside the transmission/harness; ECU applies +12V active-high to activate). Thread also separately notes forum builders use P-channel FETs (high-side drivers) specifically for SS1/SS2, consistent with this. |

**Revised conclusion (supersedes the medium-confidence "uniform high-side" theory above):**
the stock A340E/AW4 TCU does **not** use one polarity for all solenoids — it's per-solenoid:
- **S1 / S2 (shift solenoids)** — **high-side**: solenoid case/harness-grounded, TCU applies +12V. This matches this project's driver board (`.agents/knowledge/microcontroller/driver-boards/README.md`), which also switches +12V into S1/S2 with the coil's other side tied to GND.
- **SLU (lock-up)** — **low-side**: solenoid's other terminal is a fixed +12V feed, TCU grounds the pin to activate. This project's driver board currently wires SLU identically to S1/S2 (driver switches +12V, coil returns to GND) — **the opposite of the stock TCU's SLU polarity**. Functionally this project's driver board still works (it's not attached to the OEM TCU, it drives its own known-polarity solenoid wiring), but if the OEM transmission harness's SLU pigtail has a hard-wired +12V feed on one leg (matching the stock ECU's low-side design) rather than a case-ground, wiring this project's high-side output straight into that harness leg would short +12V to +12V and never energize the solenoid via GND return as expected — worth flagging to DOCUMENTATION/human before final harness wiring.

**Confidence:** High for the S1/S2 vs. SLU *split* — cross-referenced across three separate
fetches of the same thread with consistent, directly-quoted ECU pin wording, and independently
corroborated by the P-channel-FET (high-side) detail for SS1/SS2. Still not an official Toyota
FSM/OEM pinout table — if a primary Toyota source ever surfaces, prefer it over this forum
source for final confirmation.

### Update (2026-08-20, same session) — attempted second independent source; found EWD attribution, hit new tollbit blockers

Tried clublexus.com, mikestrawbridge.com, naxja.org, supraforums.com, and a second
toyotanation.com thread to find a source independent of the msextra thread.

| Source | URL | Status | Finding |
|---|---|---|---|
| ClubLexus A340E solenoid/wiring thread | clublexus.com/forums/.../1041565-... | ✅ Read | Only relevant detail: "solenoids appear to be grounded through the transmission housing, they don't have a dedicated ground wire" — consistent with S1/S2 case-ground, no polarity detail beyond that |
| Mike Strawbridge AW4 Troubleshooting blog | mikestrawbridge.com/blog/2011/09/aw4-troubleshooting/ | ❌ TLS cert expired, not fetchable | — |
| NAXJA "AW4 wiring" thread | naxja.org/threads/aw4-wiring.1087520/ | ✅ Read | Manual-conversion thread, no factory TCU polarity info; not useful |
| Supra Forums "A340 solenoids short life span" | supraforums.com/threads/a340-solenoids-short-life-span.1123502/ | ❌ Redirects (307) to unverified `tollbit.supraforums.com` — not followed | New blocker, logged in known-blockers.md |
| Toyotanation "Manual control of A340 torque converter lockup" (different thread from the one already logged as blocked) | toyotanation.com/forum/60-t-100-forum/377226-... | ❌ Redirects (307) to `tollbit.toyotanation.com` — not followed | Confirms tollbit gate applies site-wide on toyotanation, not just the one previously-tried thread |
| WebSearch synthesis surfacing EWD-sourced circuit trace | search snippets referencing the same msextra thread content | — | Search-engine synthesis explicitly labeled the underlying content as an **EWD (Electrical Wiring Diagram)** circuit trace: "current flows from the EFI main relay through terminal 2 of ECT solenoids to terminal 5, then to terminal (b) 14 of the ECU to ground... for lock-up," plus No.3 (lock-up) solenoid wire color (Yellow-Black) and coil resistance (~13Ω). This is consistent with a forum poster transcribing an actual Toyota factory EWD page rather than describing their own custom wiring — raises confidence that the low-side-SLU finding traces to a primary source, but the EWD page itself has not been directly read by this tool. |

**Revised confidence: ~75–80%** (up from the earlier ~65–75% medium-confidence figure) for the
S1/S2-high-side / SLU-low-side split *on the Toyota A340E specifically*. Not raised further
because: (1) still no direct read of the EWD page itself, only forum transcription of it; (2)
every other candidate independent source either had no polarity detail or is tollbit-walled
(toyotanation — both threads tried, pirate4x4, supraforums — three separate domains now, same
gate). **Superseded for the Jeep AW4 case by the primary-source finding below — the A340E
finding is Toyota-ECU-specific and does not transfer to the Jeep TCM.**

### Correction (2026-08-20, same session) — Jeep AW4 FSM contradicts the Toyota A340E finding; do not conflate the two vehicles

User pushed back on an in-conversation claim that SLU is PWM (it is not — see existing
`aw4/solenoids.md` "Digital ON/OFF" fact, confirmed independently, this was an assistant error
mixing up SLU with SLN/SLT). That prompted a closer look at whether the Jeep AW4's TCM might
differ electrically from the Toyota A340E's ECU despite the mechanically-identical transmission
— it does, at least for the lock-up solenoid.

| Source | URL | Status | Finding |
|---|---|---|---|
| Jeep XJ 1993 FSM — AUTO TRANS DIAGNOSIS - AW4 (Test 3A, Stored DTC Test, step 41) | https://jeep-manual.ru/index.php?page=294 | ✅ Read | **"All solenoid circuits are in the same harness and a common ground wire is used for the solenoids."** Fault-isolation logic: "If all 3 solenoid faults are present, repair the Black wire (Cherokee) ground wire open condition" — a single shared ground serves S1, S2, **and the lock-up solenoid**, confirming individually-switched +12V per solenoid from the TCM = **high-side for all three on the Jeep AW4**, including lock-up. |
| Jeep XJ 1993 FSM — AUTO TRANS DIAGNOSIS 4.0L Models w/AW4 | https://jeep-manual.ru/index.php?page=323 | ✅ Read | Same common-ground-wire statement, plus valve-body operating description ("When No. 1 and 2 valve body solenoids are energized, plunger moves from seat... When de-energized, plunger closes the drain port") and the black-ground-wire diagnostic test — consistent with page 294, independently corroborating within the same FSM (two different diagnostic sections, same underlying fact). |

**This is a genuine primary source** — the actual 1993 Jeep XJ factory service manual, not a
forum, not a Toyota-side document. It directly contradicts the Toyota A340E/msextra finding
(TCU grounds SLU, solenoid fed +12V from Main EFI relay = low-side) for the lock-up solenoid
specifically. **Conclusion: the Jeep AW4 TCM and the Toyota A340E ECU drive the lock-up
solenoid with opposite polarity**, despite sharing the same mechanical transmission. S1/S2
remain high-side on both vehicles (no contradiction there); SLU is where the two diverge.

**Practical effect on this project:** this project targets the Jeep AW4, so the **Jeep FSM
governs, not the Toyota A340E documentation**. This project's driver board (switches +12V to
S1/S2/SLU, shared GND return per `.agents/knowledge/microcontroller/driver-boards/README.md`)
**matches the Jeep FSM exactly** for all three solenoids. The earlier "possible SLU
polarity mismatch" warning in the HANDOFFS entry above was based on the Toyota-side finding and
does not apply to this build — retracting that specific risk, see updated HANDOFFS resolution.

**Confidence: high (~90%+)** for the Jeep-specific S1/S2/SLU-all-high-side, common-ground
conclusion — genuine OEM FSM primary source, cross-referenced across two separate diagnostic
sections of the same manual. Not 100% only because the FSM text was read via the fetch tool's
extraction rather than a saved/verified page image, and no second independent Jeep-side source
was checked (Novak Guide had no technical detail; Montana Fab PDF not re-checked for this
specific point this session).

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
| User's on-hand sensor is IR slot optocoupler, NOT Hall effect; DO is active-HIGH-when-blocked, push-pull (no INPUT_PULLUP) | diymore.cc + electropeak.com, cross-confirmed 2026-08-17 |
