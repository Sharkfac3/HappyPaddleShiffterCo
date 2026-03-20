# Agent Handoffs

Cross-role task queue. Drop tasks here when work needs to be picked up by another role.

**Check this file before starting any session.** If you see a `[PENDING]` task addressed
to your role, change its status to `[IN PROGRESS]` before beginning work. Do not start a
task already marked `[IN PROGRESS]` — it is being handled by another agent.

Do not use inline emoji flags (`🔧`, `🔍`, `🙋`) anywhere in the project. All cross-role
communication goes through this file.

Status values:
- `[PENDING]` — not yet picked up
- `[IN PROGRESS]` — actively being worked on (set this before you start)
- `[DONE]` — completed (leave for record; move to Completed Tasks section)
- `[ESCALATION NEEDED]` — blocked, human operator required

---

## Active Tasks

## [PENDING] — Verify 1997–2001 AW4 NSS connector pinout from primary source

**From:** DOCUMENTATION
**To:** RESEARCH
**Task:** Find and confirm the pin-label-to-wire mapping for the 1997–2001 Jeep XJ AW4
neutral safety switch connector from a primary source (FSM or OEM wiring diagram).
The physical connector housing differs from the 1987–1996 8-pin Deutsch unit, and the
exact pinout has not been independently verified from a primary source.

**What is already known:**
- The continuity map (which pairs close for which selector position) is the same across all years
- The 1997–2001 connector part number is Omix-ADA 4882173 / OEM 4882173
- The 1987–1996 connector is confirmed: 8-pin Deutsch, pins A–H (B↔C, A↔E, A↔G, A↔H)
- Source already tried: 1993 FSM confirms 1987–1996 pinout only

**What is needed:** A factory service manual page, wiring diagram, or OEM source that
shows the 1997–2001 NSS connector pin layout — specifically which physical pin corresponds
to which NSS signal (PN, R, 3rd, 1-2) so a builder can wire it without guessing.

**Why it matters:** A builder wiring a 1997–2001 XJ with incorrect pin assignments
will either get no transmission control or potentially damage the Arduino.

**Suggested search approach:**
- jeep-manual.ru 1997, 1999, and 2001 XJ FSM pages (see `context/trusted-sources.md`)
- Wayback Machine fallback for any blocked FSM sources
- Montana Fab override instructions (confirmed accessible) may show wire colours by year
- Omix-ADA product page for part 4882173 may include a pinout diagram

**Output:** Drop confirmed pinout in a follow-up HANDOFFS entry addressed to DOCUMENTATION,
and log the source in `SOURCES.md` under "Neutral Safety Switch — AW4 / Jeep XJ".
If no primary source is found, escalate as `[ESCALATION NEEDED]` with sources attempted.

---

## Completed Tasks

_Completed handoffs will be recorded here for traceability._

---

## Escalations Awaiting Human Input

_Human-operator escalations will be recorded here._

---

## How to Add a Handoff

Copy this template and fill it in:

```
## [PENDING] — Brief task title

**From:** DOCUMENTATION / CODING / RESEARCH
**To:** DOCUMENTATION / CODING / RESEARCH
**Task:** What needs to be done
**Context:** Relevant facts, file paths, or constraints
**Source:** URL or file reference if applicable
```
