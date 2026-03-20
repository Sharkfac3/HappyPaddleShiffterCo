# Known Blockers — HappyPaddleShifterCo Research

Sources that are known to fail, require authentication, or contain only image-based content. Do not waste a fetch attempt on these — escalate directly to a human or use the workaround noted.

---

## Sites That Return 403

These domains consistently return 403 for unauthenticated access:

| Domain | URLs Attempted | Workaround |
|---|---|---|
| `haltech.com` | `support.haltech.com/portal/en/kb/articles/toyota-a340e-control` | Human fetch required |
| `cherokeeforum.com` | NSS bypass wiring diagram thread | Human fetch required |
| `rusefi.com` | A340 controller forum thread | Human fetch required |
| `yotatech.com` | A340 Arduino paddle shift build thread | Human fetch required |
| `msextra.com` | A340 PRND21 wiring thread | Human fetch required |
| `waveshare.com` | 1.5" RGB OLED wiki | Human fetch required |
| `speeduino.com/forum` | ATC discussion thread | Human fetch required |

---

## Image-Only / Scanned PDFs

These sources have been fetched but contain content only as scanned images — text cannot be extracted programmatically:

| Source | URL | What's Needed | Status |
|---|---|---|---|
| Jeep XJ 1993 FSM — NSS connector wire colours | jeep-manual.ru connector diagram pages | Wire colour for each NSS pin by year | 🙋 Human needed |
| Jeep XJ 1995 FSM — NSS section | `archive.org/details/jeepcherokeexjfactoryservicemanual1995ocr2182pages` | NSS pin continuity table | ❌ Page found; NSS section not located in OCR |
| Jeep XJ 1997/1999/2001 FSMs | jeep-manual.ru | '97–'01 NSS connector pinout and wire colours | 🙋 Human needed — different physical connector |

> **Note on wire colours:** Factory FSM wire colour diagrams are consistently scanned-image-only across all XJ years. Wire colours cannot be reliably extracted. Always verify NSS connections with a multimeter before wiring. NSS pin *continuity* (which pairs close) has been confirmed from text-extractable FSM sections.

---

## Auth-Gated / Private Sources

| Source | Notes |
|---|---|
| Any Chrysler/Jeep TechAuthority content | OEM dealer technical site — requires subscription |
| Factory wiring diagram CDs / DVDs | Some XJ FSMs only available on physical media from dealer archives |

---

## Outstanding Human Escalations

Tasks that require a human to directly access a blocked source:

- [ ] **NSS wire colours for 1987–1996 XJ** — Read the NSS connector diagram from any '87–'96 XJ FSM (jeep-manual.ru or archive.org) and transcribe the wire colour for each pin (A, B, C, E, G, H). Add to `.agents/knowledge/jeep-xj/transmission/aw4/neutral-safety-switch.md`.

- [ ] **NSS connector and wire colours for 1997–2001 XJ** — The '97–'01 XJ uses a different physical NSS connector housing. Read the '97–'01 FSM connector diagram and transcribe pin designations and wire colours. Add to `.agents/knowledge/jeep-xj/transmission/aw4/neutral-safety-switch.md`.

- [ ] **Haltech A340E documentation** — Access `https://support.haltech.com/portal/en/kb/articles/toyota-a340e-control` and extract solenoid wiring and control strategy details. Add to `SOURCES.md` and cross-reference with MaxxECU solenoid mapping.

- [ ] **WaveShare 1.5" OLED wiki** — Access `https://www.waveshare.com/wiki/1.5inch_RGB_OLED_Module` and extract the SPI wiring table and library recommendation. Add to `SOURCES.md`.
