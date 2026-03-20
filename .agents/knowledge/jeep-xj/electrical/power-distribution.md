# Electrical Power Distribution

## Controller Power Supply

The Arduino Mega 2560 and logic-level components (display, NSS inputs, paddle inputs)
run at **5V** (Arduino internal regulator from VIN) or **3.3V** (Arduino 3.3V output pin).

| Component | Supply Voltage | Source |
|---|---|---|
| Arduino Mega 2560 | 7–12V input (VIN) | Fused 12V from vehicle |
| SSD1351 OLED display | 3.3V ONLY | Arduino 3.3V pin |
| NSS inputs | Internal pull-up (~5V) | Arduino INPUT_PULLUP |
| Paddle switch inputs | Internal pull-up (~5V) | Arduino INPUT_PULLUP |
| Relay/driver board logic | 5V typical | Arduino 5V pin or separate |
| Solenoids (S1, S2, SLU) | 12V, up to 2A each | Fused 12V from vehicle |

> **WARNING:** The SSD1351 display is 3.3V only. Connecting it to 5V permanently damages it.
> Wire the display VCC pin to the Arduino's 3.3V output pin — not to 5V.

## Fusing Requirements

- **Arduino supply:** Fuse at 2A inline. The Arduino Mega draws well under 1A in normal operation.
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
