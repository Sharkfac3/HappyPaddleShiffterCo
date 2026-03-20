# Documentation Standards — HappyPaddleShifterCo

Standards and quality requirements for all documents produced by the documentation role.

---

## Document Structure

Every document must begin with:

```markdown
# [Document Title]

> **Applies to:** [system / component / year range]
> **Last verified:** [date or "unverified"]
> **Related files:** [links to relevant code, schematics, or other docs]
```

---

## Wiring Tables

The standard wiring table format for any harness or connection:

| From Device | From Pin/Label | Arduino Pin | Direction | Voltage | Active State | Notes |
|---|---|---|---|---|---|---|
| AW4 NSS | Pin B | D4 | INPUT | 5V pull-up | Active LOW | Park/Neutral — shared with pin C |

Rules:
- Direction is always from the Arduino's perspective: `INPUT` or `OUTPUT`
- Voltage is the logic-level voltage (5V or 3.3V) — not the device operating voltage
- Active state is `Active HIGH` or `Active LOW`
- Notes must include any shared-pin warnings or wiring gotchas

---

## Pinout Tables

For connector-level documentation (e.g. NSS 8-pin Deutsch):

| Pin Label | Signal | Wired To | Notes |
|---|---|---|---|
| A | Common (shared) | GND via pair closure | Common leg for Reverse, 3rd, 1-2 positions |
| B | Park/Neutral | Arduino D4 | Active LOW with INPUT_PULLUP |

Rules:
- Always label the connector name and part number in the section heading
- Include year range if the connector differs across years
- Mark untested pins as `[NOT USED — verify]`

---

## Step-by-Step Instructions

Each step must follow this format:

```markdown
### Step N — [Action Title]

**Do:** [What to physically do — clear, imperative, specific]

**Verify:** [How to confirm it worked — multimeter reading, LED state, serial monitor output, visual check]

> ⚠️ SAFETY: [Any safety note relevant to this step — omit if none]
```

Rules:
- Steps must be ordered — no branching within a step list
- Never skip the Verify section — if there is nothing to verify, add a continuity check
- Write for someone who has never done this before; assume no prior knowledge of this specific system

---

## Bills of Materials (BOM)

Standard BOM table:

| Qty | Description | Specification | Part Number | Notes |
|---|---|---|---|---|
| 1 | Arduino Mega 2560 | ATmega2560, 5V | — | Original or clone |
| 3 | Flyback diode | 1N4007, 1A, 1000V | 1N4007 | One per solenoid coil |

Rules:
- Always include the specification column — a part number alone is not enough
- Mark unconfirmed part numbers as `[UNVERIFIED]`
- If multiple acceptable alternatives exist, list the preferred option and note alternatives in the Notes column

---

## Safety Callouts

These warnings are **mandatory** whenever the associated component or operation appears:

| Trigger | Required Warning |
|---|---|
| SSD1351 OLED display | `⚠️ SAFETY: This display runs on 3.3V only. Connecting 5V to VCC will permanently damage it.` |
| Solenoid wiring | `⚠️ SAFETY: Solenoids run on 12V and draw up to 2A. Never connect solenoids directly to Arduino pins. Use a relay or high-side driver board. Install a 1N4007 flyback diode across each solenoid coil.` |
| NSS wiring | `⚠️ SAFETY: The AW4 NSS is a continuity switch — it is NOT powered. Do not apply 12V to NSS pins. Use INPUT_PULLUP on the Arduino and wire the common leg to GND only.` |

---

## Unverified Values

Any electrical value not confirmed by measurement or a cited primary source must be marked:

```
[UNVERIFIED — confirm with multimeter before connecting]
```

Do not present unverified values as fact. If a value is taken from a community source rather than a factory service manual or datasheet, note the source inline.
