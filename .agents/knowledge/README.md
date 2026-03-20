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
    electrical/
      README.md              — Electrical section index
      power-distribution.md — 12V supply, fusing, ground points
    transfer-case/
      README.md              — Transfer case section index
      np231.md               — NP231 mechanics, 4WD Low procedure, why Neutral matters
  arduino/
    mega-2560.md             — Mega 2560 pin assignments, hardware SPI, memory
```
