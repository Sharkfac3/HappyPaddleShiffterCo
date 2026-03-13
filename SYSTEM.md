# A340 Transmission Controller — System Spec

## Architecture
Arduino Mega 2560. Five classes tied together in ArduinoCode.ino.
Single source of truth for selected gear: `int currentGear` (1–5) in ArduinoCode.ino.

| File | Role |
|---|---|
| ArduinoCode.ino | setup(), loop(), state machine, owns currentGear |
| PaddleShiftIndication | Debounced shift up/down paddle reads |
| GearSelectorSwitch | PRND21 inhibitor switch reads, one-shot entry flags |
| SolenoidMapper | Gear 1–5 → S1/S2/SLU output states |
| ScreenIndication | SSD1351 OLED display wrapper |

## Pin Assignments

| Pin | Dir | Description |
|---|---|---|
| 2 | INPUT_PULLUP | Shift Up paddle (active LOW) |
| 3 | INPUT_PULLUP | Shift Down paddle (active LOW) |
| 4 | INPUT | Park — inhibitor via voltage divider (active HIGH) |
| 5 | INPUT | Reverse — inhibitor via voltage divider |
| 6 | INPUT | Neutral — inhibitor via voltage divider |
| 7 | INPUT | Drive — inhibitor via voltage divider |
| 8 | INPUT | 2nd — inhibitor via voltage divider |
| 9 | INPUT | Low — inhibitor via voltage divider |
| 11 | OUTPUT | S1 solenoid (via driver board) |
| 12 | OUTPUT | S2 solenoid (via driver board) |
| 13 | OUTPUT | SLU solenoid (via driver board) |
| 51 | OUTPUT | Display DIN — hardware MOSI, fixed on Mega |
| 52 | OUTPUT | Display CLK — hardware SCK, fixed on Mega |
| A3 | OUTPUT | Display RES |
| A4 | OUTPUT | Display DC |
| A5 | OUTPUT | Display CS |

## Solenoid Mapping (A340, verified)

| Gear | S1 | S2 | SLU |
|---|---|---|---|
| 1 | ON | OFF | OFF |
| 2 | ON | ON | OFF |
| 3 | OFF | ON | OFF |
| 4 | OFF | OFF | OFF |
| 5 (4th+lockup) | OFF | OFF | ON |
| P/R/N | OFF | OFF | OFF |

SLU is digital on/off — NOT PWM.
4th (all off) is also the transmission's electrical failsafe state.
R and N are hydraulic — solenoid state has no mechanical effect there.

## State Machine

| State | Screen | Solenoids | Shifting | Gear Reset |
|---|---|---|---|---|
| PARK | P | all off | no | → 1 |
| REVERSE | R | all off | no | → 1 |
| NEUTRAL | N | all off | no | — |
| DRIVE | 1/2/3/4/4L | per map | yes | — |
| 2ND | 2 | gear 2 | no | — |
| LOW | L | gear 1 | no | — |
| UNKNOWN | blank | hold | no | — |

## Inhibitor Switch Hardware
9-pin factory switch on transmission body. Common = 12V (pin 6, Red/Blue).
Outputs 12V per position — must use voltage divider per input (10kΩ + 4.7kΩ to GND → ~3.8V).

| Position | Wire Color |
|---|---|
| Park | Green/White |
| Reverse | Red/Black |
| Neutral | Red |
| Drive | Black/Orange |
| 2nd | Orange |
| Low | Yellow/Blue |

## Debounce
All switch inputs: 50ms timestamp-based debounce.
Paddles: INPUT_PULLUP, trigger on falling edge.
Inhibitor: plain INPUT via dividers, trigger on rising edge.

## Libraries
- Adafruit_SSD1351 (Library Manager)
- Adafruit_GFX (Library Manager)
- SPI (built-in)
