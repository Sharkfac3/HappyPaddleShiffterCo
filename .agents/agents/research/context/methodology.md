# Research Methodology

Step-by-step process for conducting research tasks on this project.

---

## Before You Search

1. Read `.agents/knowledge/` relevant section — the fact may already be confirmed.
2. Read `SOURCES.md` — the URL may already have been fetched.
3. Read `.agents/context/trusted-sources.md` — know which sites are accessible.

If the fact is already confirmed, cite the existing entry and stop. Do not re-fetch.

---

## Research Hierarchy

Use sources in this priority order:

1. **Factory Service Manual (FSM)** — Jeep/Chrysler or Toyota/Aisin official spec.
   These are the ground truth for NSS pin continuity, connector pinouts, and OEM part numbers.

2. **Manufacturer datasheet** — for components (relays, driver ICs, displays).
   Download PDFs where possible; log the direct URL.

3. **OEM parts databases** — Omix-ADA, Crown Automotive, Mopar for Jeep-specific parts.
   These give confirmed OEM and aftermarket part numbers.

4. **Reputable aftermarket documentation** — MaxxECU, Haltech, Megasquirt.
   Good for solenoid specs and wiring; must still cross-reference with FSM.

5. **Community build threads** — EveryCircuit, forum build logs.
   Acceptable for corroboration only. Never a sole source for a safety-critical spec.

---

## Handling Blocked Pages

If a page returns 403, 409, or redirects to a login:

1. Log it in `SOURCES.md` as ❌.
2. Try the Wayback Machine: `https://web.archive.org/web/*/[original-url]`.
3. Try a Google cache link: `cache:[original-url]`.
4. Search for an alternative source covering the same spec.
5. If still blocked after two alternatives: flag as `[ESCALATION NEEDED]`.

---

## Identifying Connector Pins from Scanned Images

The AW4 NSS connector diagrams in the FSM are scanned images — pin labels are
sometimes not extractable as text. If you cannot read a pin label:

1. Note which page of the FSM it is on and log in `SOURCES.md`.
2. Cross-reference with the Montana Fab override instructions (confirmed accessible).
3. Cross-reference with the ATSG AW4 service PDF (confirmed accessible).
4. If three independent sources conflict: flag in `HANDOFFS.md` as ESCALATION NEEDED.
   The human operator will verify with a physical multimeter.

**Never guess a pin number.** A wrong pin number can destroy the Arduino or the NSS.

---

## Logging Requirements

For every URL consulted, add to `SOURCES.md`:

```
| Description | URL | Status |
|---|---|---|
| What this page contains | https://... | ✅ Read / ❌ failed / — not fetched |
```

Under "Key Findings Summary" at the bottom of `SOURCES.md`, add a row for each new
confirmed fact:

```
| Decision/Fact | Source |
|---|---|
| [Confirmed fact] | [Source URL or name] |
```

---

## Escalation Format

When escalating in `.agents/HANDOFFS.md`:

```
## [ESCALATION NEEDED] — [brief description]

**Requesting role:** RESEARCH (blocked — needs human assist)
**What is needed:** [specific fact, part number, or pin]
**Already searched:**
  - [URL 1] — [why it failed]
  - [URL 2] — [why it failed]
**Suggested approach:** [physical manual, forum DM, multimeter test, etc.]
```
