# Research Methodology — HappyPaddleShifterCo

How to approach research tasks for this project. Follow this process in order.

---

## Step 0 — Check What's Already Known

Before searching, read:
1. `SOURCES.md` — every previously fetched or attempted URL is logged here with status ✅/❌
2. `.agents/knowledge/` — confirmed facts are already written up; don't re-research them
3. `./known-blockers.md` — sites that have previously failed; don't waste a fetch attempt on them

If the fact you need is already confirmed and cited, document it and stop.

---

## Step 1 — Identify the Source Tier

| Tier | Source Type | Reliability | Use For |
|---|---|---|---|
| 1 | Factory Service Manual (FSM) | Highest | OEM wiring, connector pinouts, continuity specs |
| 2 | OEM service bulletins, ATSG manuals | High | Transmission specs, solenoid data |
| 3 | Manufacturer datasheets | High | Electronic component specs |
| 4 | Professional aftermarket instructions | Medium | Montana Fab, MaxxECU, Haltech |
| 5 | Community builds (forums, GitHub) | Medium | Practical implementation patterns — cross-reference with Tier 1/2 |
| 6 | Retail product pages | Low | Part numbers and availability only — not specs |

Always use the highest tier available. Never cite a Tier 5/6 source alone for a safety-critical electrical value.

---

## Step 2 — Search Strategy

For **FSM / wiring / OEM specs:**
1. Try jeep-manual.ru first (best XJ FSM coverage, text-extractable)
2. Search for the specific page or section using known URL patterns from `source-registry.md`
3. Try xjjeeps.com CDN for PDF versions
4. If all fail, log as blocked and escalate to human (see Step 5)

For **component specs / part numbers:**
1. Look up the part on Digi-Key or Mouser — datasheets are always available
2. For OEM parts, try RockAuto or Omix-ADA product listings
3. Cross-check the part number on a second supplier before recording as confirmed

For **implementation patterns:**
1. Check the existing open-source references in SOURCES.md (SCG-ATC, EveryCircuit)
2. Search GitHub for A340/AW4 Arduino controller repositories
3. Tag community-sourced facts clearly — they must be cross-referenced before being treated as confirmed

---

## Step 3 — Verify the Fact

Safety-critical electrical values must be confirmed from **two independent sources** before being recorded as confirmed:

Safety-critical values include:
- Solenoid coil resistance (Ω)
- Solenoid operating voltage and current draw (V, A)
- NSS pin continuity map (which pins close for each selector position)
- Display supply voltage limits (VCC max)

Record both source URLs and their fetch status in `SOURCES.md`.

---

## Step 4 — Record the Finding

Every new confirmed fact must:
1. Be written into the appropriate `.agents/knowledge/` file (if cross-role relevant) or delivered as structured output (table / list)
2. Be cited with the source URL inline: `[MaxxECU A340E docs](https://www.maxxecu.com/...)`
3. Have its source URL added to `SOURCES.md` with ✅ status

Every failed fetch must:
1. Be added to `SOURCES.md` with ❌ status and the failure mode noted
2. Be logged in `./known-blockers.md` if the failure is likely to affect future attempts

---

## Step 5 — Escalate Blocked Sources

When a required source cannot be accessed:

**403 / authentication-gated page:**
> 🙋 HUMAN NEEDED: The page at [URL] returns 403. Please access it directly and copy [specific table / section / data] into this file.

**Image-only / scanned PDF (text not extractable):**
> 🙋 HUMAN NEEDED: The PDF at [URL] contains only scanned images. Please open page [N] and transcribe the [connector table / wire colour chart / pinout diagram] as text.

**Datasheet with image-only pin diagram:**
> 🙋 HUMAN NEEDED: The datasheet for [part number] at [URL] has a pin diagram that is an image. I can see [description of what is visible]. Please read the pin labels and numbers from the diagram and add them to [this file / knowledge file].

Be specific — tell the human exactly what page, what table, and what data format you need.

---

## Step 6 — Update SOURCES.md

After every research session, add new rows to `SOURCES.md`:

```markdown
| [Description] | [URL] | ✅ Read / ❌ Blocked |
```

Update existing rows if a previously blocked source was successfully accessed by a human.
