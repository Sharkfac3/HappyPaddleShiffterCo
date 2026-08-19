# Electrical Power Distribution

## Controller Power Supply

The Arduino board (Uno default, Mega or Nano supported — see `.agents/knowledge/arduino/board-comparison.md`)
and logic-level components (display, NSS inputs, paddle inputs) run at **5V** (Arduino
internal regulator) or **3.3V** (Arduino 3.3V output pin).

| Component | Supply Voltage | Source |
|---|---|---|
| Arduino board (Uno/Mega) | 5V regulated | **Buck converter output** — see below, NOT raw VIN from vehicle 12V |
| SSD1351 OLED display | 3.3V ONLY | Arduino 3.3V pin |
| NSS inputs | Internal pull-up (~5V) | Arduino INPUT_PULLUP |
| Paddle sensor inputs | Sensor-driven push-pull (3.3–5V) | Arduino plain INPUT — do not use INPUT_PULLUP |
| Relay/driver board logic | 5V typical | Arduino 5V pin or separate |
| Solenoids (S1, S2, SLU) | 12V, up to 2A each | Fused 12V from vehicle |

> **WARNING:** The SSD1351 display is 3.3V only. Connecting it to 5V permanently damages it.
> Wire the display VCC pin to the Arduino's 3.3V output pin — not to 5V.

## Arduino Power — Buck Converter Required, Not Raw VIN

**Do not power any Arduino board (Uno, Mega, or Nano) from vehicle 12V directly into VIN
or the barrel jack.** All three boards use a linear (LDO) onboard regulator rated for a
7–12V *recommended* input:

| Board | Onboard regulator | Recommended input | Absolute max input |
|---|---|---|---|
| Uno | NCP1117ST50T3G | 7–12V | 20V |
| Mega 2560 | LD1117S50CTR | 7–12V | **15V** (tightest of the three) |
| Nano | NCP1117/LM1117-5.0 | 7–12V | 20V |

A running vehicle's charging system holds **13.8–14.2V** at the alternator — already
above every board's recommended ceiling. This is not board-specific: Uno, Mega, and Nano
all use the same class of linear regulator and all overheat under load at this voltage
range, per multiple confirmed reports (see sources). There is no board in this project's
comparison set that is safe to run straight off vehicle power long-term.

**Fix:** Step down vehicle 12–14V to a clean regulated 5V with a buck converter (e.g. an
MP1584EN-based module), then feed the Arduino's **5V pin** directly — bypassing the
onboard linear regulator entirely. This is the standard approach for automotive Arduino
installs regardless of which board ships.

`[PENDING RESEARCH — see HANDOFFS.md]` — exact buck converter part number, current rating,
and BOM entry not yet sourced/verified.

## Reverse Polarity Protection

**The VIN pin (and any 5V pin fed directly from an external source) has no built-in
reverse-polarity protection on any board** — Uno, Mega, and Nano alike. The Uno's DC
barrel jack has a protection diode, but this project does not use the barrel jack, and
the Nano has no barrel jack at all. Wiring the controller's power feed directly (not
through a barrel jack) means reverse polarity risk is identical across all three boards.

**Fix:** Add a series protection diode (or a fused, correctly-keyed connector) on the
12V feed line ahead of the buck converter input. This protects both the buck converter
and the Arduino from a reversed connection during install or service.

`[PENDING RESEARCH — see HANDOFFS.md]` — specific diode/fuse part number not yet sourced.

## Fusing Requirements

- **Arduino supply:** Fuse at 2A inline, ahead of the buck converter input. The Arduino
  board (Uno, Mega, or Nano) draws well under 1A in normal operation.
- **Solenoid supply:** Fuse each solenoid channel at **3A** individually, or use a common 10A
  fuse for all three channels (S1, S2, SLU combined max ~6A). Individual fusing preferred.
- **Driver board supply:** Check driver board datasheet for its fusing requirements.

## Ground Strategy

- All grounds (Arduino GND, driver board GND, solenoid return GND) should share a common
  ground point tied to the vehicle chassis.
- Use a single-point ground star topology at the controller enclosure to avoid ground loops.
- The AW4 solenoid bodies ground through the transmission case — the transmission case must
  have a good chassis ground strap for solenoid return current.

## 12V Source Recommendation

Power the controller from a **switched 12V source** (ignition-on power), not a constant
12V source. This ensures the controller initialises fresh each key cycle and does not
drain the battery when the vehicle is parked.

Recommended: tap the fuse box at an ignition-switched circuit rated at least 15A.
