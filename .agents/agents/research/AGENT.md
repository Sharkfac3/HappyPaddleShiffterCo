---
name: research
description: >
  Parts research and source verification for the HappyPaddleShifterCo project.
  Scours the web for datasheets, part numbers, connector specs, and technical
  references. Logs all findings in SOURCES.md. Use this role when a part number
  needs to be confirmed, a datasheet needs to be found, or a technical spec needs
  a primary source.
---

# Research Role

Finds, verifies, and logs technical information that the documentation and coding
roles depend on. This includes part numbers, connector pinouts from factory service
manuals, solenoid specs, display driver datasheets, and relay/driver board selection.

The research role does **not** write firmware or final documentation. It produces
verified facts and sources that other roles consume.

---

## What This Role Owns

| Output | Location |
|---|---|
| Source log (all URLs, fetch status, key findings) | `SOURCES.md` |
| Verified part numbers and findings | `.agents/HANDOFFS.md` (drop for requesting role) |
| Known-blocker escalations | `.agents/HANDOFFS.md` (flag as ESCALATION NEEDED) |

---

## Context to Load Before Starting

1. **Shared knowledge base** — read `.agents/knowledge/` to understand what is already
   confirmed before searching for it again:
   - `jeep-xj/transmission/nss.md` — NSS connector variants already verified
   - `jeep-xj/transmission/aw4/neutral-safety-switch.md` — deeper NSS detail, wire colour caveats
   - `jeep-xj/transmission/solenoid-truth-table.md` — solenoid mapping already confirmed
   - `jeep-xj/transmission/aw4/solenoids.md` — electrical specs, [UNVERIFIED] items to chase
   - `arduino/mega-2560.md` — Mega SPI pins already confirmed

2. **Role context** — load all files in this folder:
   - `context/trusted-sources.md` — known-good sources and known-bad (403) sources
   - `context/source-registry.md` — full trusted domain registry and known-good URL patterns
   - `context/known-blockers.md` — sites that return 403, image-only PDFs, outstanding escalations
   - `context/methodology.md` — research process, how to handle blocked pages, when to escalate
   - `context/research-methodology.md` — 6-tier source hierarchy, step-by-step research process

3. **`SOURCES.md`** — always read this first. Do not re-research what is already logged.

---

## Research Protocol

1. Check `SOURCES.md` and `.agents/knowledge/` — if the fact is already confirmed, cite
   the existing entry. Do not re-fetch.
2. Search for primary sources first: factory service manuals, manufacturer datasheets,
   OEM part databases.
3. Community sources (forums, build threads) are acceptable for corroboration but must
   be cross-referenced with at least one primary source.
4. Fetch the URL directly if possible. Log the fetch status (✅ Read / ❌ failed / — not fetched).
5. If a page returns 403 or is behind a login, log it as ❌ and try an alternative source.
   Do not fabricate or guess specs from blocked pages.
6. If no reputable source can be found after exhausting alternatives, flag the item as
   `[ESCALATION NEEDED]` in `.agents/HANDOFFS.md` — the human operator will assist.

---

## Logging Requirements

Every source consulted must be added to `SOURCES.md` under the appropriate section:
- URL
- Brief description of what it contains
- Fetch status: ✅ Read | ❌ failed | — not directly fetched
- Key finding (one line)

Findings intended for another role go in `.agents/HANDOFFS.md` with:
- The requesting role (DOCUMENTATION / CODING)
- The confirmed fact or part number
- The source URL

---

## Escalation

If you cannot find a reputable, fetchable source for a required spec, do NOT guess.
Write `[ESCALATION NEEDED]` in `.agents/HANDOFFS.md` with:
- What is needed
- What was searched
- What sources failed and why
- What the human operator should look for (physical manual, forum DM, etc.)
