# Shared Knowledge Base

Vehicle, transmission, and hardware facts shared across all agent roles.

This knowledge base contains information that is NOT specific to any single role.
Role-specific context (standards, checklists, APIs) lives in each role's own
`context/` folder.

Only add verified facts here. Mark anything uncertain with `[UNVERIFIED]`.

---

## Structure

```
knowledge/
  jeep-xj/
    overview.md              — XJ Cherokee variants, years, production history
    transmission/
      README.md              — Transmission section index
      aw4-overview.md        — AW4 mechanics, A340E relationship, what we're controlling
      solenoid-truth-table.md — Verified S1/S2/SLU states per gear
      nss.md                 — NSS connector, pin pairs, wiring method, year variants
      aw4/                   — Deeper AW4 detail: selector gate, solenoid specs, NSS wiring
    electrical/
      README.md              — Electrical section index
      power-distribution.md — 12V supply, fusing, ground points
    transfer-case/
      README.md              — Transfer case section index
      np231.md               — NP231 mechanics, 4WD Low procedure, why Neutral matters
    body-chassis/
      README.md              — Body/chassis section index
      steering-column.md     — Paddle mounting options, airbag years, wiring routing
  microcontroller/
    board-comparison.md      — Uno vs Nano vs Mega 2560 comparison, how to choose a board
    pin-reference/           — This project's pin assignments, hardware SPI, memory (all boards)
    driver-boards/           — Relay vs high-side driver, flyback diodes, wiring
```
