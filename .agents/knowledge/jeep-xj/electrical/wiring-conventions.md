# XJ Wiring Conventions

Factory wire colour conventions, connector types, and harness layout notes for the Jeep XJ.

---

## Wire Colour Conventions

The XJ uses Chrysler/Jeep wire colour conventions. These are relevant when splicing into factory harnesses.

> ⚠️ Wire colours for the AW4 NSS harness specifically **cannot be reliably extracted from scanned FSM diagrams**. Always probe with a multimeter to confirm continuity before connecting to the Arduino. See `transmission/aw4/neutral-safety-switch.md`.

### General Colour Conventions (Chrysler/Jeep)

| Colour | Common Use |
|---|---|
| Red | Battery positive, unswitched power |
| Black | Ground / chassis |
| Dark Green | Ignition-switched power |
| Pink / Pink-Black | Ignition-switched power (ASD-related) |
| Dark Blue | Non-switched accessory power |
| Orange | Battery-direct, high current |
| Grey | Various — context-dependent |
| Tan / Brown | Sensor signals |
| Violet/Purple | Various — context-dependent |
| White | Various — often with tracer stripe |

Wires with tracer stripes are described as `BASE COLOUR / TRACER COLOUR` — e.g. `Red/White` = red wire with white tracer.

---

## Connector Types

| Connector Type | Where Used | Notes |
|---|---|---|
| Deutsch 8-pin (DT series) | AW4 NSS, 1987–1996 | Pins A–H; grey body common; sealing plugs for unused positions |
| Molex MX-150 | Various factory engine/trans harness | Common in '90s Chrysler applications |
| Weather Pack | Various | Used in exposed under-hood locations |
| Factory blade connectors | Interior, under-dash | Standard blade terminals |

---

## Harness Routing — AW4 Area

The AW4 harness runs along the driver-side of the transmission tunnel and exits through a firewall grommet. Relevant connectors:

| Connector | Location | Access |
|---|---|---|
| NSS | Left (driver's) side of transmission, near selector shaft | Accessible from underneath, forward of crossmember |
| Solenoid connector | Passenger-side of transmission, under heat shield | May require dropping the exhaust heat shield |
| Factory TCU (if present) | Varies by year — often under passenger seat or in engine bay | This project bypasses the factory TCU |

---

## Probing the NSS Before Wiring

Because wire colours for the NSS are not reliably documented in text form, use this procedure:

1. Disconnect the NSS connector from the transmission
2. Set multimeter to continuity mode
3. For each selector position (P, R, N, D, 3, 2-1), probe pairs of NSS connector pins until you find the pair that shows continuity
4. Record which pin labels show continuity at each position — compare against the known continuity map in `transmission/aw4/neutral-safety-switch.md`
5. Once you know which physical wire goes to which NSS pin label, wire accordingly

This approach makes wire colour irrelevant — you work from confirmed continuity, not colour assumptions.
