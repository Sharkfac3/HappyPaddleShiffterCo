# Template Library — HappyPaddleShifterCo Documentation

Reusable section templates. Copy and fill in — do not modify the structure.

---

## Template: Wiring Guide Section

```markdown
## Wiring — [Component Name]

> **Applies to:** [years / variants]
> **Part number:** [OEM or aftermarket part number, or UNVERIFIED]

> ⚠️ SAFETY: [mandatory safety warning for this component]

### Connections

| From Device | From Pin | Arduino Pin | Direction | Voltage | Active State | Notes |
|---|---|---|---|---|---|---|
| [device] | [pin label] | [Dxx or Axx] | INPUT/OUTPUT | 5V / 3.3V | Active HIGH/LOW | [notes] |

### Wiring Diagram

[ASCII diagram — see diagram-conventions.md]

### Step-by-Step

#### Step 1 — [First action]
**Do:** [What to do]
**Verify:** [How to confirm]

#### Step 2 — [Next action]
**Do:** [What to do]
**Verify:** [How to confirm]
```

---

## Template: Pinout Table Section

```markdown
## Pinout — [Connector Name]

> **Connector:** [description, e.g. "8-pin Deutsch, pins A–H"]
> **Part number:** [part number or UNVERIFIED]
> **Years:** [year range this applies to]

| Pin Label | Signal | Connected To | Active State | Notes |
|---|---|---|---|---|
| A | [signal name] | [destination] | Active LOW | [notes] |
| B | [signal name] | [destination] | Active LOW | [notes] |

> ⚠️ SAFETY: [any relevant warning]

> ❓ UNVERIFIED: [any pins not yet confirmed — what needs to be checked]
```

---

## Template: Bill of Materials Section

```markdown
## Bill of Materials — [Assembly Name]

| Qty | Description | Specification | Part Number | Source | Notes |
|---|---|---|---|---|---|
| [n] | [part name] | [key spec] | [part number or UNVERIFIED] | [supplier] | [alternatives or notes] |

**Total estimated cost:** [$ or UNVERIFIED]

> 🔍 RESEARCH ROLE: [any open BOM questions — parts not yet sourced or confirmed]
```

---

## Template: Step-by-Step Installation Guide

```markdown
# Installation Guide — [System or Component]

> **Skill level:** [Beginner / Intermediate / Advanced]
> **Time estimate:** [duration or UNVERIFIED]
> **Tools required:** [list]
> **Parts required:** [link to BOM section]

---

## Before You Start

[Prerequisites — what must already be done, what state the vehicle should be in]

> ⚠️ SAFETY: [global safety warning for this installation — disconnect battery, etc.]

---

## Step 1 — [First Major Action]

**Do:** [Precise instruction]

**Verify:** [Measurable check]

> ⚠️ SAFETY: [step-specific warning, if any]

---

## Step 2 — [Next Major Action]

**Do:** [Precise instruction]

**Verify:** [Measurable check]

---

## Troubleshooting

| Symptom | Likely Cause | Fix |
|---|---|---|
| [symptom] | [cause] | [action] |
```

---

## Template: Cross-Role Handoff Note

Use these callouts to flag work that needs another role. Always be specific — say exactly what is needed.

```markdown
> 🔧 CODING ROLE: [Exact description of the firmware change needed and why]

> 🔍 RESEARCH ROLE: [Exact part or spec that needs to be found, including what's known so far]

> ⚠️ SAFETY: [Safety warning text]

> ❓ UNVERIFIED: [What needs to be confirmed, and how — e.g. "measure resistance between NSS pins A and E with selector in Reverse"]

> 🙋 HUMAN NEEDED: [Specific task a human must do — e.g. "read page 4-12 of 1997 FSM and copy the NSS wire colour table"]
```
