# Architectural Decisions

Decisions that affect the firmware design, hardware choices, or project approach.
Read this before making any significant change. Many of these decisions exist because
violating them reintroduced a real bug.

---

## ADR-001: Do NOT reset currentGear when entering Park/Neutral

**Decision:** `justEnteredParkNeutral()` calls `solenoids.allOff()` but does NOT
reset `currentGear`.

**Reason:** The physical selector gate is P → R → N → D. Engaging 4WD Low (NP231
transfer case) requires moving the selector to Neutral while working the transfer
case lever, then returning to Drive. If `currentGear` were reset on every Neutral
entry, the transmission would always drop back to 1st when returning from the 4WD
Low engagement procedure — forcing an unwanted downshift while the vehicle is in
motion or at low speed.

**Consequence:** When the selector returns to Drive, `justEnteredDrive()` fires and
calls `solenoids.applyGear(currentGear)` — re-engaging at the preserved gear.

**Startup exception:** `applyState()` (called once in `setup()`) DOES initialise
`currentGear = 1` for the `GEAR_SEL_PARK_NEUTRAL` case. This is correct — there is
no previous gear to preserve at power-on.

**Reverse is different:** `justEnteredReverse()` DOES reset `currentGear = 1`. Reverse
always requires the vehicle to be fully stopped; 1st gear on return is always correct.

**Do not reverse this decision** without considering the 4WD Low use case.

---

## ADR-002: Solenoids driven via relay/driver board, not directly from Arduino pins

**Decision:** S1, S2, and SLU outputs go to a relay or high-side driver board, which
then switches the 12V solenoid circuit. Arduino pins never carry 12V or solenoid current.

**Reason:** AW4 solenoids run on 12V and draw up to 2A each. Arduino output pins are
rated to ~40mA. Direct connection would immediately destroy the Arduino.

**Required:** Flyback diodes (1N4007) across each solenoid coil to protect the driver
board from inductive kickback.

**SLU note:** SLU is digital on/off on this AW4 variant — NOT PWM. Do not attempt to
implement torque-converter slip control with PWM; it is not supported by this hardware.

---

## ADR-003: Display is SSD1351, initialised with begin() not initR()

**Decision:** `ScreenIndication` uses `_tft.begin()` (Adafruit SSD1351 init),
not `initR()` (which is ST7735-only).

**Reason:** The WaveShare 1.5" RGB OLED uses the SSD1351 driver chip. `initR()` is
for the ST7735 family. Calling `initR()` produces a blank or corrupted display.

**VCC:** The display is 3.3V only. Connecting it to 5V permanently damages it.

---

## ADR-004: All debounce is non-blocking (timestamp-based)

**Decision:** All input debounce uses `millis()` timestamps with a 50ms settle window.
No `delay()` calls in the main loop.

**Reason:** `delay()` blocks the entire loop, preventing the selector state machine and
paddle inputs from being sampled. A 50ms delay would make the controller unresponsive
and potentially cause solenoid state glitches during gear transitions.

---

## ADR-005: justEntered*() handlers use return to exit loop() immediately

**Decision:** Each `justEntered*()` handler in `loop()` ends with `return` to exit
the loop iteration immediately after a state transition.

**Reason:** Prevents double-processing. Without `return`, a state transition on one
iteration could also be processed by the `switch(state)` block below it in the same
cycle, potentially applying conflicting solenoid states.

---

## ADR-006: Hardware SPI pins 51 (MOSI) and 52 (SCK) are fixed on the Mega

**Decision:** The SSD1351 display uses hardware SPI. On the Arduino Mega 2560,
hardware SPI is on pins 51 (MOSI) and 52 (SCK). These cannot be reassigned.

**Reason:** The Adafruit SSD1351 library in hardware SPI mode uses the hardware SPI
peripheral. Software SPI (bit-banging) is an alternative but is significantly slower
and has not been tested on this project.

---

## ADR-007: Park and Neutral are treated identically

**Decision:** Both Park and Neutral cause `GEAR_SEL_PARK_NEUTRAL` — they cannot be
distinguished by the NSS alone (both close pins B↔C).

**Reason:** This is a hardware limitation of the AW4 NSS. Distinguishing them would
require an additional park pawl sensor or a separate input.

**Display:** Both show "P". If hard differentiation is required in future, a separate
park switch must be added to the hardware.
