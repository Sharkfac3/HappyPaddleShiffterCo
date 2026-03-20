# Jeep XJ Cherokee — Overview

## Production Years

1984–2001. The XJ Cherokee is a unibody compact SUV. This project targets the
**1987–2001** model years, which are the years the AW4 automatic transmission was offered.

## Drivetrain Variants Relevant to This Project

| Transmission | Years Available | Notes |
|---|---|---|
| AW4 (A340E) automatic | 1987–2001 | The transmission this project controls |
| AX-15 5-speed manual | 1988–1999 | Not relevant — no solenoids |
| AX-5 5-speed manual | 1987–1989 | Not relevant — no solenoids |

## Engine Options (Reference Only)

The most common engine in AW4-equipped XJs:
- 4.0L inline-6 (AMC/Jeep HO) — 1991–2001, most common
- 2.5L inline-4 — 1987–2001, some markets

Engine type does not affect this project's firmware or wiring.

## Transfer Cases (Important for Firmware Behaviour)

All XJs with 4WD use the **NP231** (Command-Trac) part-time transfer case.
See `.agents/knowledge/jeep-xj/transfer-case/np231.md` for details.

The physical selector gate — **P → R → N → D → 3 → 1** — means the driver
must pass through Neutral to engage 4WD Low. This is why `currentGear` must be
preserved through Neutral. See `DECISIONS.md` ADR-001.

## NSS Connector Variants by Year

The AW4 neutral safety switch uses different physical connectors across model years:

| Years | Connector type | NSS Part Number |
|---|---|---|
| 1987–1996 | 8-pin Deutsch connector, pins labeled A–H | Omix-ADA 17216.03 / OEM 83503712 |
| 1997–2001 | Different physical connector | Omix-ADA 4882173 / OEM 4882173 |

The continuity map (which pins close for which position) is consistent across all years.
Only the physical connector housing differs.

> **Verify before wiring:** Always use a multimeter to confirm continuity for each
> selector position. Do not rely solely on documentation for safety-critical wiring.
