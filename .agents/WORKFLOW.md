# Agent Workflow

How the three roles collaborate on this project. Read this before starting a
multi-step task that spans more than one role.

---

## Role Summary

| Role | Produces | Consumes |
|---|---|---|
| **Research** | Verified specs, part numbers, sources | Tasks from Documentation or Coding |
| **Coding** | Firmware (`.ino`, `.h`, `.cpp`) | Verified specs from Research |
| **Documentation** | Builder-facing docs (Markdown) | Verified specs from Research, firmware facts from Coding |

---

## Task Triage — Which Role Starts?

Before picking up any task, classify it to determine the starting role and sequence.

### Step 1 — Is the required information already confirmed?

Check `.agents/knowledge/` and `SOURCES.md` first.

- **If a required spec, part number, or electrical value is NOT yet confirmed:**
  → **Research role starts.** No other role may act on unconfirmed data.
- **If all required facts are already confirmed:**
  → Skip Research and go to Step 2.

### Step 2 — What is the primary output?

| Primary output | Starting role | Typical sequence |
|---|---|---|
| Code change (`.ino`, `.h`, `.cpp`) | **Coding** | (Research if spec unconfirmed) → Coding → Documentation if wiring/pinout changes |
| Builder-facing doc (wiring diagram, install guide, BOM) | **Documentation** | (Research if part number unconfirmed) → Documentation |
| Part number, datasheet, or source verification | **Research** | Research → drop findings in HANDOFFS.md for requesting role |
| Knowledge base update (`.agents/knowledge/`) | **Owning role** | See "Knowledge Base Ownership" below |

### Common Ambiguous Tasks

| Task | Correct routing |
|---|---|
| "Update the solenoid truth table" | Spec changing → Research → Coding (`SolenoidMapper.cpp`) → Documentation (wiring diagrams). Doc typo only → Documentation. KB file only → Research (owns transmission KB). |
| "Fix the display showing the wrong gear" | Coding (`ScreenIndication.cpp`) → HANDOFF to Documentation if display guide needs updating |
| "Add a part number to the BOM" | Research (verify) → Documentation (add to BOM) |
| "The NSS wiring looks wrong" | Research (verify against FSM) → Documentation (update diagram) → Coding only if pin assignments change |
| "Add a new selector position" | Coding (GearSelectorSwitch + state machine) → HANDOFF to Documentation |

---

## Typical Workflow Order

```
1. RESEARCH — confirm specs, find part numbers, verify sources
       ↓ drops findings in HANDOFFS.md
2. CODING — implement firmware changes based on confirmed specs
       ↓ drops HANDOFF to Documentation if wiring/pinout docs need updating
3. DOCUMENTATION — write/update builder docs based on confirmed specs + firmware
```

Not every task needs all three roles. A firmware bug fix may go directly to Coding.
A documentation typo may go directly to Documentation.

---

## Starting a Task

1. Read `CLAUDE.md` or `AGENTS.md` (already done if you're reading this).
2. **Check `.agents/HANDOFFS.md` for any `[PENDING]` tasks addressed to your role.**
   Change the status to `[IN PROGRESS]` before starting work.
   Do not start a task already marked `[IN PROGRESS]` — it is being handled.
3. Run the Task Triage above to confirm which role you are playing.
4. Load the role's `AGENT.md`.
5. Load the relevant sections of `.agents/knowledge/`.
6. Check `.agents/DECISIONS.md` before making any architectural choice.

---

## Passing Work Between Roles

All cross-role communication goes through `.agents/HANDOFFS.md`. Do not use inline
comments, emoji flags, or any other channel — HANDOFFS.md is the single source of
truth for pending work.

Format:

```
## [STATUS] — [brief title]

**From:** [ROLE]
**To:** [ROLE]
**Task:** [what needs to be done]
**Context:** [any relevant facts or file paths]
**Source:** [URL or file if applicable]
```

Status values:
- `[PENDING]` — not yet picked up
- `[IN PROGRESS]` — actively being worked on (change to this before starting)
- `[DONE]` — completed, leave for record
- `[ESCALATION NEEDED]` — blocked, needs human operator

### Pickup Protocol

When you pick up a `[PENDING]` task:
1. Change its status to `[IN PROGRESS]` in HANDOFFS.md before doing any work.
2. If you finish, change it to `[DONE]` and drop any follow-on tasks as new `[PENDING]` entries.
3. If you are blocked, change it to `[ESCALATION NEEDED]` and add what you attempted.

### Rework and Feedback Loops

The flow is typically linear (Research → Coding → Documentation) but roles may need to
hand back when they discover a problem upstream.

**If Coding discovers a Research finding is wrong:**
Stop. Do not implement based on incorrect data. Create a new `[PENDING]` HANDOFF
back to Research explaining what was found and why the original finding is suspect.
Wait for Research to re-confirm before continuing.

**If Documentation discovers a firmware gap or bug:**
Drop a `[PENDING]` HANDOFF to Coding. Do not modify firmware. Continue documenting
what IS confirmed; mark gaps inline with `[PENDING CODING — see HANDOFFS.md]`.

**If Research is blocked:**
Change the task to `[ESCALATION NEEDED]`. Describe what was searched, what failed,
and what the human operator should retrieve. Do not guess or fill in missing data.

---

## Which Role Owns What

| File or area | Owning role | Rule |
|---|---|---|
| `ArduinoCode/*.ino`, `*.h`, `*.cpp` | **Coding** | Only Coding writes firmware |
| `ArduinoCode/SYSTEM.md` | **Coding** | Coding maintains this as the authoritative firmware spec; Documentation reads it but does not modify it |
| `Schematics/`, `Models/`, `README.md` | **Documentation** | Only Documentation writes builder-facing docs |
| `ArduinoCode/README.md` | **Documentation** | Build/flash guide — Documentation owns it |
| `SOURCES.md` | **Research** | Only Research logs sources here; other roles must not add entries directly |
| `.agents/knowledge/` | **Subsystem-assigned** | See "Knowledge Base Ownership" below |

---

## Knowledge Base Ownership

Knowledge base sections are assigned by subsystem. Do not update a section you do not own —
drop a HANDOFF to the owning role instead.

| Section | Owning role |
|---|---|
| `.agents/knowledge/jeep-xj/transmission/` | **Research** |
| `.agents/knowledge/jeep-xj/electrical/` | **Research** |
| `.agents/knowledge/jeep-xj/transfer-case/` | **Research** |
| `.agents/knowledge/jeep-xj/body-chassis/` | **Documentation** |
| `.agents/knowledge/arduino/mega-2560/` | **Coding** |
| `.agents/knowledge/arduino/driver-boards/` | **Coding** |
| `.agents/knowledge/jeep-xj/overview.md` | **Research** |

**If you discover a new fact in a section you don't own:**
1. Do NOT update the file yourself.
2. Drop a `[PENDING]` HANDOFF to the owning role with the new fact and its source.
3. The owning role verifies and updates the file.

Only add verified facts. Mark anything uncertain with `[UNVERIFIED — see HANDOFFS.md]`.
