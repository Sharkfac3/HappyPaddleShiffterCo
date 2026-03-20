# Documentation Standards

Formatting rules, diagram conventions, and tone guidelines for all documentation
produced by the documentation role.

---

## Tone and Audience

- Write for a competent DIYer with basic electrical skills.
- Assume the reader knows how to use a multimeter and can follow a wiring diagram.
- Do not assume they know Arduino IDE, transmission internals, or Jeep-specific terminology.
- Explain acronyms on first use: AW4 (Jeep's name for the A340E automatic transmission),
  NSS (neutral safety switch), SLU (shift lock-up solenoid), TCU (transmission control unit).
- Safety warnings are non-negotiable. Any step involving 12V, solenoids, or display VCC
  must have a warning immediately before it.

---

## Formatting Rules

### Headers
- H1 (`#`) — document title only
- H2 (`##`) — major sections
- H3 (`###`) — subsections within a section
- Never skip levels

### Tables
Use Markdown tables for all pinout references and part lists. Columns must include units
where applicable (e.g. "Current (A)", "Voltage (V)").

### Wiring Diagrams
- Use ASCII art or Markdown tables — no image-only diagrams.
- Every connection must show both ends: `Arduino Pin 4 → NSS Pin B (Park/Neutral)`
- Show direction: INPUT or OUTPUT from the Arduino's perspective.
- Include mode where relevant: `INPUT_PULLUP`, `OUTPUT`.

### Step-by-Step Guides
- Each step is one sentence describing one action.
- Number all steps. Do not use bullets for procedural content.
- Safety warnings appear as a blockquote immediately before the step they apply to:

  > **WARNING:** Solenoids run on 12V and draw up to 2A. Disconnect the vehicle battery
  > before connecting or disconnecting solenoid wiring.

### Code References
- When referencing firmware behaviour, link to or quote from `ArduinoCode/SYSTEM.md`.
- Do not restate firmware logic in docs — link to the source of truth.

---

## Part Numbers and Sources

- Never publish a part number without a source. Use `[UNVERIFIED]` if unconfirmed.
- All confirmed part numbers must have a corresponding entry in `SOURCES.md`.
- When in doubt, drop a task in `.agents/HANDOFFS.md` for the research role.

---

## Known Terminology Gotchas

| Do say | Do not say |
|---|---|
| AW4 / A340E | "the transmission" (ambiguous) |
| NSS (neutral safety switch) | "the selector switch" |
| Arduino Mega 2560 | "the Arduino" (model matters for SPI pins) |
| 3.3V only (display) | "low voltage" |
| relay/driver board | "relay" (SLU needs driver, not bare relay) |
| INPUT_PULLUP | "pull-up resistor" (the Mega has internal ones; no external needed) |
