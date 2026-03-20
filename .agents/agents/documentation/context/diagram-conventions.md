# Diagram Conventions — HappyPaddleShifterCo

How to draw wiring diagrams and block diagrams in this project's documentation. All diagrams are text-based (ASCII or Markdown) so they render correctly in any Markdown viewer and remain diff-able in git.

---

## ASCII Wiring Diagrams

### Signal Flow Convention

Signals flow left to right. The source (power or signal origin) is on the left; the sink (load or receiver) is on the right.

```
[Source]──────────────────────────[Sink]
```

### Wire Styles

| Symbol | Meaning |
|---|---|
| `──` or `━━` | Wire (horizontal) |
| `│` or `┃` | Wire (vertical) |
| `┼` | Wire crossing (connected) |
| `╋` | Wire crossing (not connected — rare, avoid) |
| `─┬─` | Junction / T-split |
| `>` or `→` | Signal direction indicator |
| `[ ]` | Component or device |
| `( )` | Pin or terminal |

### Example — NSS to Arduino Wiring

```
AW4 NSS (8-pin Deutsch)              Arduino Mega 2560
┌─────────────────┐
│ Pin B (Park/N)  │──── INPUT_PULLUP ────→ D4
│ Pin C           │──── GND ──────────────→ GND
│ Pin A (Common)  │──┬─ INPUT_PULLUP ────→ D5 (Reverse)
│ Pin E (Reverse) │──┘
│ Pin A (Common)  │──┬─ INPUT_PULLUP ────→ D6 (3rd hold)
│ Pin G (3rd)     │──┘
│ Pin A (Common)  │──┬─ INPUT_PULLUP ────→ D7 (1-2 hold)
│ Pin H (1-2)     │──┘
└─────────────────┘
```

### Example — Solenoid Driver Block

```
Arduino Mega 2560         Driver Board              AW4 Solenoids (12V)
┌────────────┐            ┌────────────┐            ┌───────────┐
│ D11 (S1)   │────────→  │ CH1 IN     │──[relay]──→│ S1 coil   │
│ D12 (S2)   │────────→  │ CH2 IN     │──[relay]──→│ S2 coil   │
│ D13 (SLU)  │────────→  │ CH3 IN     │──[relay]──→│ SLU coil  │
└────────────┘            │ GND        │←───────────│ Common GND│
                          │ 12V IN     │←───────────│ 12V supply│
                          └────────────┘            └───────────┘
                                ↑
                    1N4007 flyback diode across
                    each solenoid coil (mandatory)
```

---

## Block Diagrams

Use block diagrams to show system architecture, not individual signals.

```
┌──────────────────────────────────────────────────────┐
│                  Arduino Mega 2560                    │
│                                                       │
│  ┌──────────────┐    ┌──────────────┐                │
│  │ PaddleShift  │    │ GearSelector │                │
│  │ Indication   │    │ Switch       │                │
│  └──────┬───────┘    └──────┬───────┘                │
│         │                   │                         │
│         └────────┬──────────┘                         │
│                  ↓                                    │
│           ArduinoCode.ino                             │
│           (currentGear)                               │
│                  │                                    │
│         ┌────────┴──────────┐                         │
│         ↓                   ↓                         │
│  ┌──────────────┐    ┌──────────────┐                │
│  │ SolenoidMap  │    │ Screen       │                │
│  │ per          │    │ Indication   │                │
│  └──────────────┘    └──────────────┘                │
└──────────────────────────────────────────────────────┘
         │                       │
         ↓                       ↓
  [Driver Board]           [SSD1351 OLED]
  S1 / S2 / SLU            3.3V only
```

---

## Markdown Wiring Tables

For simple point-to-point connections, prefer a table over ASCII art:

| From | From Pin | To | To Pin | Signal | Notes |
|---|---|---|---|---|---|
| AW4 NSS | B | Arduino | D4 | Park/Neutral — active LOW | Wire NSS pin C to GND |

---

## Labelling Rules

- Always label voltage levels at the power entry point: `+12V`, `+5V`, `+3.3V`, `GND`
- Always label the active state of signals: `active LOW` or `active HIGH`
- Label connectors with both part name and part number if known: `NSS (Deutsch 8-pin, Omix-ADA 17216.03)`
- Label year-specific variants inline: `('87–'96 connector only — '97–'01 uses different physical housing)`
