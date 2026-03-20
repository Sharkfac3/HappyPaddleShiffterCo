# External Driver Boards — Solenoid Switching

## Why an External Driver Board is Required

The AW4 solenoids run at **12V** and draw up to **2A each**. The Arduino Mega 2560 I/O pins have an absolute maximum current of **40mA** (20mA recommended). Connecting a solenoid directly to an Arduino pin would immediately destroy the ATmega2560.

An external driver board sits between the Arduino's 5V logic output and the 12V solenoid load:
- Accepts 5V logic signal from the Arduino
- Switches a 12V power path to the solenoid
- Isolates the Arduino from the 12V automotive electrical environment

---

## Driver Board Options

### Option 1 — Relay Board (Most Common for This Build)

Electromechanical relays that open/close a 12V circuit.

| Attribute | Value |
|---|---|
| Switching type | Mechanical contact |
| Logic input | 5V (some boards are active HIGH, some active LOW — check before wiring) |
| Contact rating | Typically 10A / 250VAC — well above the solenoid's 2A at 12V |
| Switching speed | Slow (~10ms) — acceptable for gear shift events |
| Noise | Relay click audible; coil produces EMI on activation |
| Cost | Low (~$1–3 per channel) |
| Availability | Widely available as 1-, 2-, 4-, and 8-channel boards |

**Recommended configuration:** 4-channel relay board (3 channels used: S1, S2, SLU; 1 spare)

> ⚠️ SAFETY: Some relay boards have active-LOW inputs (relay activates when Arduino pin is LOW). Verify before wiring — this is the inverse of what the code expects if using HIGH for "ON". The `SolenoidMapper` outputs HIGH for ON — use an active-HIGH relay board, or invert the logic in code if using an active-LOW board.

### Option 2 — High-Side Driver IC (e.g. ULN2003, VNQ5E160K)

Transistor-based solid-state switching.

| Attribute | Value |
|---|---|
| Switching type | Solid state (BJT, MOSFET, or Darlington) |
| Logic input | 5V (TTL-compatible) |
| Current rating | Varies by IC — select for > 2A per channel |
| Switching speed | Fast (microseconds) — no impact on gear shift use |
| Noise | No audible click; lower EMI than relay |
| Cost | Low per-channel; requires PCB or breakout |
| Availability | Widely available; requires more assembly than relay boards |

**ULN2003A** (Darlington array, 7 channels, 500mA each): sufficient for solenoids if current draw is confirmed under 500mA per solenoid. Verify coil resistance before selecting this part.

**VNQ5E160K** or similar automotive-grade high-side switches: rated for automotive environments, built-in flyback protection — recommended if building a dedicated PCB.

---

## Flyback Diode Requirement

Regardless of driver board type, **install a 1N4007 flyback diode across each solenoid coil**:

```
           1N4007
    ┌──────┤>├──────┐
    │    (cathode   │
    │    toward     │
    │    12V+)      │
   12V+         Driver
                output ──→ Solenoid coil ──→ GND
```

- Cathode (striped end) toward the 12V supply
- Anode toward the driver board output / solenoid terminal
- Rating: 1N4007 (1A, 1000V) is the standard choice — cheap and widely available

The flyback diode clamps the inductive spike when the solenoid de-energises to approximately 0.7V above the supply voltage, protecting the driver board transistors or relay contacts.

> ⚠️ SAFETY: Omitting the flyback diode will eventually damage the driver board and may produce voltage transients that cause the Arduino to reset or malfunction during solenoid switching.

---

## Wiring Summary

```
Arduino Mega       Driver Board          AW4 Solenoids
(5V logic out)     (12V switching)       (12V loads)

Pin 11 ─────────→  CH1 IN               CH1 OUT ──[1N4007]──→ S1 coil ──→ GND
Pin 12 ─────────→  CH2 IN               CH2 OUT ──[1N4007]──→ S2 coil ──→ GND
Pin 13 ─────────→  CH3 IN               CH3 OUT ──[1N4007]──→ SLU coil ──→ GND
GND ─────────────→ Driver GND
                   12V IN ←──── Fused 12V supply (10A)
```

The Arduino's 5V and GND are independent of the 12V solenoid supply. The only shared connection is GND — the Arduino GND must be connected to the same ground reference as the driver board and solenoids (chassis ground).
