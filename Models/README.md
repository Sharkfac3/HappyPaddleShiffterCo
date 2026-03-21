# Models — Paddle Shifter Hardware

> **Applies to:** HappyPaddleShifterCo — Jeep XJ Cherokee AW4 paddle shifter controller
> **Last verified:** 2026-03-20
> **Related files:** `ArduinoCode/SYSTEM.md` (pin assignments), `Schematics/README.md` (wiring), `SOURCES.md` (component sources)

3D-printable STL files for the physical paddle hardware — the left and right paddles that
mount to the steering wheel and actuate the gear shift switches.

---

## Contents of This Directory

| File / Folder | Description |
|---|---|
| STL files | Printable paddle bodies, switch pockets, and mounting brackets (add filenames here as parts are finalised) |
| Source CAD files | `.f3d`, `.step`, or `.3mf` source files if available |

---

## Bill of Materials — Non-Printed Hardware

These are the purchased components required to complete each paddle assembly. Print quantities
are per paddle; the full build requires two paddles (left and right).

| Qty per Paddle | Qty Total (2 paddles) | Description | Specification | Part Number | Notes |
|---|---|---|---|---|---|
| 1 | 2 | Paddle switch | Omron D2JW-01K11, SPDT N/O momentary, straight lever, IP67, 30 VDC / 100 mA, chassis mount, solder lug termination | **Omron D2JW-01K11** | Selected switch. Chassis-mounts directly to paddle body. NOT interchangeable with D2F-5L — pocket geometry differs. See [Switch Detail](#switch-detail--omron-d2jw-01k11) below. |
| 2 | 4 | Switch mounting screw | M2 × 6 mm, countersunk or pan head | [UNVERIFIED — confirm before purchasing] | Matches 2.35 mm mounting holes in D2JW-01K11 body. Confirm thread and length against printed pocket depth before ordering. |
| — | — | Wire leads | Lightweight hookup wire, 26–28 AWG | — | Short runs from switch solder lugs to PCB or Arduino. Exact length depends on routing in your steering column. See `Schematics/README.md` for wiring. |
| — | — | Fasteners (steering wheel mount) | [UNVERIFIED — confirm before purchasing] | — | Fastener spec depends on your steering wheel and bracket design. Add here once mounting method is finalised. |

> **Total estimated cost:** [UNVERIFIED — confirm before purchasing]

[PENDING RESEARCH — see HANDOFFS.md]: Confirm M2 fastener spec against printed pocket geometry and D2JW-01K11 mounting hole dimensions. Confirm steering wheel mounting fastener type.

---

## Switch Detail — Omron D2JW-01K11

The D2JW-01K11 is the formally selected paddle switch as of 2026-03-20. It replaces the
former D2F-5L selection. **These two switches are not dimensionally interchangeable —
the 3D model switch pocket must be designed or updated for the D2JW-01K11 geometry.**

### Body Dimensions

| Dimension | Value |
|---|---|
| Body width | 12.7 mm |
| Body height | 12.3 mm |
| Body depth | 5.3 mm ± 0.1 mm |
| Mounting hole diameter | 2.35 mm |
| Mounting hole spacing | 3.95 × 3.95 mm |
| Lever material / thickness | Stainless steel, t0.3 mm |
| Lever arc radius | R16.5 mm |

### Actuation Geometry

| Parameter | Value |
|---|---|
| Operating Position (OP) — lever tip travel to actuation | 8.4 mm ± 0.8 mm |
| OP measurement arm height above body base | 6.15 mm |
| Pretravel | 6.4 mm max |
| Overtravel | 1.4 mm min |
| Movement Differential | 0.7 mm max |

### Switch Pocket Design Rule

> ⚠️ The switch pocket in the 3D-printed paddle body **must** position the lever tip
> **8.4 mm from the paddle contact surface** (the point the driver's finger presses).
>
> This is **1.6 mm deeper** than the former D2F-5L pocket, which was designed for a
> 6.8 mm operating position. A pocket designed for the D2F-5L will not reliably actuate
> the D2JW-01K11 — the lever will not reach its operating position under normal finger
> pressure. Update any existing pocket geometry before printing.

### Mounting Method

The D2JW-01K11 is a **chassis-mount** switch — it is not a PCB through-hole component.
The switch body screws directly into the printed paddle body via its two 2.35 mm mounting
holes. Short wire leads are soldered to the solder lug terminals and routed to the
Arduino or PCB.

Do not attempt to mount this switch to a PCB by its terminals. It is not rated or designed
for that method.

### Why This Switch Was Selected

| Requirement | D2JW-01K11 | Former D2F-5L |
|---|---|---|
| IP rating | IP67 — dust-tight, waterproof | IP40 — no water protection |
| Electrical life | 100,000 cycles (~13.7 yrs at 20 shifts/day) | 10,000 cycles |
| Mechanical life | 1,000,000 cycles | 1,000,000 cycles |
| Operating force | 82 gf — good tactile snap | 80 gf — similar feel |
| Temperature range | −40°C to +85°C | −40°C to +85°C |
| Mounting | Chassis mount — robust under vibration | PCB through-hole — less suited to paddle use |

The D2JW-01K11 offers 10× better electrical life and full IP67 sealing while preserving
near-identical paddle feel. It is the correct choice for street, off-road, and sustained use.

---

## Print Settings

> ⚠️ These settings are **[UNVERIFIED — confirm before printing]**. They represent
> reasonable starting points for structural paddle hardware; adjust to suit your printer
> and material.

[PENDING RESEARCH — see HANDOFFS.md]: Print settings (material, layer height, infill, orientation, supports) have not been formally specified or tested. Research role to confirm and document tested settings before these values are published as authoritative.

| Parameter | Recommended Starting Point | Notes |
|---|---|---|
| Material | PETG or ABS | [UNVERIFIED] — PETG preferred for dimensional stability and mild flexibility; ABS for higher heat resistance. PLA not recommended for in-cabin use (summer temperatures). |
| Layer height | 0.2 mm | [UNVERIFIED] |
| Infill | 40 % | [UNVERIFIED] — Switch pocket walls and mounting boss areas may need higher infill or solid layers for thread engagement. |
| Supports | Yes — switch pocket area | [UNVERIFIED] — Pocket geometry will determine support requirement. Review slicer preview. |
| Print orientation | [UNVERIFIED] | Optimise so the switch pocket floor prints as a flat surface without supports if possible. |
| Perimeters / walls | 3 minimum | [UNVERIFIED] — Additional perimeters recommended around mounting bosses. |

---

## Assembly Notes

### Step 1 — Prepare the Switch

**Do:** Solder two short wire leads (26–28 AWG, length to suit your routing) to the
normally-open (NO) terminal and the Common (C) terminal on the D2JW-01K11 solder lugs.
Insulate each connection with heat-shrink tubing.

**Verify:** Use a multimeter in continuity mode. With the lever at rest (not pressed), confirm
**no continuity** between the two leads. Press the lever to its operating position — confirm
**continuity** closes. Release — confirm it opens again.

---

### Step 2 — Mount the Switch in the Paddle Body

**Do:** Place the D2JW-01K11 into the switch pocket in the printed paddle body. Secure
with two M2 screws through the switch's 2.35 mm mounting holes.

**Verify:** The lever should sit flush with or proud of the paddle contact surface at rest.
Press the paddle face — the lever should actuate (click) before the paddle body bottoms
out. If the lever does not reach its operating position (8.4 mm travel) under normal
finger pressure, the pocket is too shallow — recheck the pocket depth in the model.

> ⚠️ Do not overtighten the M2 mounting screws. The D2JW-01K11 body is rated for
> chassis mounting loads — excessive clamping force on the body may crack the housing.

---

### Step 3 — Route and Connect Wiring

**Do:** Route the wire leads from the switch solder lugs through the paddle body and
steering column to the Arduino Mega 2560. Connect as follows:

| Paddle | Arduino Pin | Mode | Notes |
|---|---|---|---|
| Shift Up (right paddle) | D2 | INPUT_PULLUP, active LOW | Common leg → GND |
| Shift Down (left paddle) | D3 | INPUT_PULLUP, active LOW | Common leg → GND |

Wire the Common (C) terminal of each switch to GND. Wire the NO terminal to the
Arduino INPUT_PULLUP pin. When the paddle is pressed, the circuit closes and the pin
reads LOW — this is the active state the firmware expects.

**Verify:** With the Arduino powered and running the firmware, open the Serial Monitor
(115200 baud). Press the Shift Up paddle — confirm the display shows a gear increment.
Press Shift Down — confirm a decrement. No press should produce no change.

For full wiring details and the steering column routing guide, see `Schematics/README.md`.

> ⚠️ SAFETY: The NSS (neutral safety switch) is a continuity switch — NOT powered.
> Do not apply 12 V to any NSS or paddle switch pin. Use INPUT_PULLUP on the Arduino
> and wire common legs to GND only.

---

## Switch Alternatives

If the D2JW-01K11 is unavailable, the following alternatives were evaluated. All are
IP67-rated normally-open momentary types. **Do not substitute the D2F-5L** — it has
10× lower electrical life and no water sealing.

| Part | IP Rating | Electrical Life | Operating Force | Op. Position | Notes |
|---|---|---|---|---|---|
| **Omron D2JW-01K11** *(selected)* | IP67 | 100,000 cycles | 82 gf | 8.4 mm | Straight lever, chassis mount, solder lug |
| Omron D2JW-011 | IP67 | 100,000 cycles | 250 gf | — | Pin plunger — rejected; stiff feel, incompatible geometry |
| Omron D2JW-01K21 | IP67 | 100,000 cycles | 100 gf | 14.6 mm | Roller lever — superseded by D2JW-01K11 |
| Omron D2JW-AQ | IP67 | not confirmed | — | — | Automotive-rated; specs unconfirmed — [UNVERIFIED] |
| **Omron D2F-5L** *(replaced — do not use)* | IP40 | 10,000 cycles | 80 gf | 6.8 mm | Former selection — no water sealing, low electrical life. Pocket geometry incompatible with D2JW-01K11. |
