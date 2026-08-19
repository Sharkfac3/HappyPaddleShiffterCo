# Firmware Patterns — HappyPaddleShifterCo

The standard patterns used in this codebase, shown in the current implementation language
(Arduino/AVR C++). All new code must follow these patterns for consistency and safety —
the underlying principles apply regardless of target board family; only the exact API
calls (`millis()`, `pinMode()`, `digitalWrite()`, etc.) are board/toolchain-specific.

---

## Non-Blocking Debounce (timestamp-based)

**Never use a blocking delay for debounce** (Arduino: `delay()`). The `loop()` must run continuously — any blocking call stalls the entire state machine.

The standard debounce pattern used in `PaddleShiftIndication` and `GearSelectorSwitch`:

```cpp
// Private members
int _lastPinState;
unsigned long _lastChangeTime;
static const unsigned long DEBOUNCE_MS = 50;

void update() {
    int reading = digitalRead(_pin);

    if (reading != _lastPinState) {
        _lastChangeTime = millis();  // Reset the timer on any change
        _lastPinState = reading;
    }

    if ((millis() - _lastChangeTime) >= DEBOUNCE_MS) {
        // Pin has been stable for DEBOUNCE_MS — this is the confirmed state
        if (_stableState == HIGH && reading == LOW) {
            // Falling edge detected — trigger the event
            _flag = true;
        }
        _stableState = reading;
    }
}
```

Key points:
- Timer resets on ANY change — only fires after the pin has been stable for the full window
- Trigger on **falling edge** (HIGH→LOW) — this project's active-LOW convention. Applies to
  both the pulled-up NSS inputs (`INPUT_PULLUP`) and the push-pull paddle sensor inputs
  (plain `INPUT`) — the two use different pin modes but the same idle-HIGH/active-LOW polarity
- The stable-state tracking prevents re-triggering while the pin holds LOW

---

## One-Shot Flag Pattern

Used by both `PaddleShiftIndication` and `GearSelectorSwitch`. The flag is set by `update()` and cleared by the accessor — `ArduinoCode.ino` never needs to manually reset anything.

```cpp
// In update() — set the flag on falling edge
_flag = true;

// Accessor — return and immediately clear
bool shiftUpRequested() {
    if (_upFlag) {
        _upFlag = false;  // Consume and clear
        return true;
    }
    return false;
}
```

This means:
- The flag is `true` for at most one `loop()` iteration
- Calling the accessor twice in the same loop returns `true` then `false` — callers must read once and store the result if needed (though in practice each flag is read only once per loop)

---

## Pulled-Up, Active-LOW Digital Inputs

Every digital input needs a defined idle state — no floating pins. The NSS switch inputs in
this project use the pulled-up, active-LOW convention: one terminal to a pulled-up pin, the
other to GND (Arduino: `pinMode(pin, INPUT_PULLUP)`).

```cpp
// In begin() / setup()
pinMode(_pin, INPUT_PULLUP);

// In update() — unpressed = HIGH, pressed/active = LOW
int reading = digitalRead(_pin);
if (reading == LOW) {
    // Input is active
}
```

Do not use external pull-up resistors — the internal pull-ups (any of Uno/Mega/Nano) are sufficient for the signal lengths in this build.

**Exception — paddle trigger sensors:** the paddle inputs are actively driven push-pull by
the sensor module itself, not switches needing a pull-up. They use plain `INPUT` (no
`INPUT_PULLUP`) but keep the same active-LOW polarity — see `PaddleShiftIndication`.

---

## Single Point of Output Control

`SolenoidMapper` routes all solenoid state changes through a private `write()` helper:

```cpp
void write(bool s1, bool s2, bool slu) {
    digitalWrite(_pinS1,  s1  ? HIGH : LOW);
    digitalWrite(_pinS2,  s2  ? HIGH : LOW);
    digitalWrite(_pinSLU, slu ? HIGH : LOW);
}
```

Apply this pattern to any new output subsystem. It makes state changes easy to audit, test, and add logging to without touching every call site.

---

## Safe Startup Default

Every output subsystem must call its safe-state function in `begin()`:

```cpp
void SolenoidMapper::begin() {
    pinMode(_pinS1,  OUTPUT);
    pinMode(_pinS2,  OUTPUT);
    pinMode(_pinSLU, OUTPUT);
    allOff();  // Safe startup — 4th gear hydraulic failsafe
}
```

For the solenoids, `allOff()` is the correct safe default. For a new output (e.g. an indicator LED), define what the safe initial state is and set it explicitly in `begin()`.

---

## Redraw Guard Pattern

Used in `ScreenIndication` to avoid unnecessary SPI writes on every `loop()` call:

```cpp
String _lastDisplayed = "";

void renderText(String text, uint16_t colour) {
    if (text == _lastDisplayed) return;  // Skip if nothing changed
    _lastDisplayed = text;
    // ... perform the SPI write / draw operations
}
```

Apply this pattern to any output that is expensive to update (SPI display, slow serial peripheral, etc.).

---

## millis() Overflow Safety

`millis()` rolls over after ~49.7 days. Use subtraction, not comparison, for all timeout checks:

```cpp
// CORRECT — handles rollover safely
if ((millis() - _lastChangeTime) >= DEBOUNCE_MS) { ... }

// WRONG — breaks at rollover
if (millis() >= _lastChangeTime + DEBOUNCE_MS) { ... }
```

Both `unsigned long` values are used — subtraction of unsigned integers wraps correctly in C++.
