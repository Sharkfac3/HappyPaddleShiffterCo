# XJ Steering Column and Steering Wheel

## Overview

The XJ Cherokee uses a collapsible safety steering column with a tilt option on higher trim levels. The steering wheel is a 3-spoke design on most production vehicles.

This section covers mounting considerations for the custom paddle trigger sensors that are the primary driver input for the transmission controller.

---

## Steering Wheel

| Attribute | Detail |
|---|---|
| Bolt pattern | Standard Jeep/Chrysler 3-bolt or slip-ring type (year-dependent) |
| Horn contact | Clock spring / slip ring — maintains electrical continuity through steering rotation |
| Airbag (SRS) | Present on some XJ years — see year notes below |

### Airbag (SRS) Years

| Years | SRS Status | Notes |
|---|---|---|
| 1987–1992 | No airbag | Simpler steering wheel — no SRS concerns |
| 1993–2001 | Driver airbag standard | **Do not modify or pierce the steering wheel SRS system**; route wiring carefully to avoid SRS components |

> ⚠️ SAFETY: On 1993–2001 XJs, the driver airbag is in the steering wheel hub. Disconnect the battery and wait at least 15 minutes before working near airbag components. Do not pierce, cut, or route wires near the yellow SRS wiring.

---

## Paddle Sensor Mounting Options

The paddles use an IR slot-type optocoupler sensor (LM393-based) — an opaque tab passes
through a slot as the driver squeezes behind the steering wheel spokes. See the
`hardware-bom` skill and `Models/README.md` for sensor electrical specs and the (not yet
designed) slot pocket geometry.

| Option | Description | Pros | Cons |
|---|---|---|---|
| Column-mounted (fixed) | Paddles mount to the steering column, not the wheel — they do not rotate | Wire routing is simple; no clock spring needed | Paddles are fixed; driver must remember position |
| Wheel-mounted (rotating) | Paddles mount to the steering wheel — they rotate with it | Natural racing-style feel | Requires clock spring or slip ring to pass signals; SRS interference risk on '93+ |
| Spoke-mounted | Paddles mount behind or on the spokes | Intermediate option; some rotation | Limited mounting surface on XJ 3-spoke wheel |

**This project uses column-mounted paddles** (fixed, non-rotating) to avoid SRS and clock spring complexity.

---

## Wiring Routing

From the paddle sensors to the Arduino:

- Route wires along the steering column, bundled with existing harness
- Pass through or alongside the existing firewall grommet (driver side)
- Keep signal wires (22–24 AWG, low current) away from the starter and alternator cables to minimise noise pickup
- Use a grommet or loom wherever wires pass through sheet metal edges

Each sensor needs three wires (VCC, GND, DO) rather than the two a switch would need.
Signal wires carry logic-level signals (3.3–5V, low current). Standard automotive hook-up
wire is sufficient — no shielding required in typical installations.

---

## Arduino Mounting Location

The Arduino (Uno, Mega 2560, or Nano — the controller brain) is typically mounted:

- Under the dash on the driver or passenger side (sheltered from weather and heat)
- In the centre console area if available

Avoid:
- Under-hood mounting (excessive heat, vibration, and moisture)
- Near the transmission tunnel (heat and vibration)
- Near the battery or high-current cables (EMI)

The controller must be accessible for programming (USB connection to a laptop) and diagnostic monitoring (Serial monitor at 9600 baud).
