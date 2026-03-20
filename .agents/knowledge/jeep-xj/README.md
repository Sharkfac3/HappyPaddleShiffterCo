# Jeep XJ Cherokee — Knowledge Index

The Jeep Cherokee XJ was produced from 1984 to 2001. This project targets the **1987–2001** model years, which are the years that received the AW4 automatic transmission option.

---

## Files in This Section

| File / Folder | Contents |
|---|---|
| [`overview.md`](overview.md) | Vehicle specs, powertrain options, model year changes relevant to this project |
| [`electrical/`](electrical/README.md) | XJ electrical system: power distribution, grounds, wiring conventions |
| [`transmission/`](transmission/README.md) | Transmission systems — see `aw4/` for the target transmission |
| [`transfer-case/`](transfer-case/README.md) | NP231 transfer case and 4WD engagement context |
| [`body-chassis/`](body-chassis/README.md) | Steering column and paddle mounting area |

---

## Quick Facts

| Spec | Value |
|---|---|
| Production years (XJ) | 1984–2001 |
| AW4 transmission years | 1987–2001 |
| Engine options (AW4-equipped) | 4.0L I6 (HO, most common), 2.5L I4 (less common) |
| Body style | Unibody — 2-door or 4-door |
| System voltage | 12V nominal (charging: ~13.5–14.5V) |
| ECU / TCU | This project **bypasses the factory TCU entirely** |

---

## Year Ranges That Matter for This Project

| Years | Significance |
|---|---|
| 1987–1991 | AW4 introduced; renix-era engine management |
| 1991+ | HO 4.0L becomes standard; improved factory calibration |
| 1987–1996 | NSS uses 8-pin Deutsch connector (pins A–H) |
| 1997–2001 | NSS uses different physical connector housing — different part number, same electrical behaviour |
| All years | NSS pin continuity map (B↔C, A↔E, A↔G, A↔H) is consistent |

See [`transmission/aw4/neutral-safety-switch.md`](transmission/aw4/neutral-safety-switch.md) for connector details.
