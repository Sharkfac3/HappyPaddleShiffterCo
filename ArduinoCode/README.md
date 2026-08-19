# ArduinoCode — Build & Flash Guide

Firmware for the Jeep XJ AW4 paddle shifter controller.
For full technical specification (pin assignments, state machine, solenoid mapping)
see [`SYSTEM.md`](SYSTEM.md).

---

## Required Hardware

| Component | Specification | Notes |
|---|---|---|
| Microcontroller | Arduino Uno (default), Mega 2560, or Nano | Same firmware, same pin numbers, no `#ifdef` — solenoid outputs sit on A0–A2 so they don't collide with any board's hardware-SPI pins |
| Relay / driver board | 3-channel, 5V logic, 12V/2A per channel | Must handle inductive loads. Add flyback diodes (1N4007) if not built in |
| Solenoid flyback diodes | 1N4007 x3 | One across each solenoid coil. Skip if driver board has built-in protection |
| OLED display | WaveShare 1.5" RGB OLED (SSD1351 driver, 128×128) | 3.3V only — do not connect to 5V |
| Paddle trigger sensors | IR slot-type optocoupler, LM393-based, 3.3–5V, plain INPUT (not INPUT_PULLUP) | One per paddle (shift up / shift down). Generic/unbranded part — see `hardware-bom` skill |
| AW4 NSS connector | 1987–1996: 8-pin Deutsch (Omix-ADA 17216.03) | See SYSTEM.md for wiring |

---

## Arduino IDE Library Dependencies

Install via **Tools → Manage Libraries** in the Arduino IDE:

| Library | Install name | Notes |
|---|---|---|
| Adafruit SSD1351 | `Adafruit SSD1351` | OLED display driver |
| Adafruit GFX | `Adafruit GFX Library` | Required dependency of SSD1351 |

No other external libraries are required. All other code is in this folder.

---

## Flash Instructions

1. Open `ArduinoCode.ino` in the Arduino IDE (the IDE will load all `.h` and `.cpp` files automatically).
2. Go to **Tools → Board** and select **Arduino Uno** (default board), **Arduino Mega or Mega 2560** if using a Mega, or **Arduino Nano** if using a Nano.
3. If using the Mega, go to **Tools → Processor** and select **ATmega2560** (no processor selection needed for Uno).
   If using the Nano, go to **Tools → Processor** and select the correct bootloader variant —
   most Nanos (genuine or recent clones) use **ATmega328P**; older clones need
   **ATmega328P (Old Bootloader)**. Wrong selection uploads successfully but the board won't
   run — if the Nano doesn't respond after flashing, try the other processor option before
   suspecting a wiring fault. Firmware size is identical either way (compiled clean against
   both, arduino-cli 1.5.2-rc.1); only the bootloader differs.
4. Connect the board to your computer via USB.
5. Go to **Tools → Port** and select the correct COM port.
6. Click **Upload** (right arrow button, or Ctrl+U).
7. Wait for "Done uploading" in the status bar.

---

## Startup Verification (Serial Monitor)

After flashing, open **Tools → Serial Monitor** and set baud rate to **9600**.

With the selector in Park or Neutral, you should see:
```
AW4 Controller — Starting up
INIT: PARK/NEUTRAL
```

If you see nothing: check baud rate is 9600. Check the correct COM port is selected.

---

## Quick Sanity Check (Before Connecting to Vehicle)

Perform these checks on the bench before wiring into the vehicle:

1. **Display test:** Power on. The OLED should show "P" (Park/Neutral).
   If blank or corrupted: check DIN→MOSI (pin 11 on Uno, pin 51 on Mega), CLK→SCK (pin 13 on Uno,
   pin 52 on Mega), CS→A5, DC→A4, RES→A3. Check VCC is 3.3V.

2. **Paddle test:** With Serial Monitor open, press each paddle.
   Serial Monitor should show `SHIFT UP -> gear 2` or `SHIFT DOWN -> gear 1`.
   If no response: check paddle wiring to pins 2 and 3, confirm active LOW (pressed = GND).

3. **NSS test (with test leads):** Briefly short pin 4 to GND (simulates Park/Neutral).
   Serial Monitor should show `-> PARK/NEUTRAL | solenoids off | gear preserved at X`.
   Repeat for pins 5, 6, 7 (Reverse, 3rd, 1-2).

4. **Solenoid driver test:** With driver board connected (NO solenoids attached):
   Press shift up. Verify CH1 (S1) relay activates for 1st gear, CH1+CH2 for 2nd, etc.

> **WARNING:** Do NOT connect the solenoid driver board to the vehicle while the engine
> is running and the selector is in Drive during this test. Unexpected gear changes
> can cause loss of vehicle control. Perform all bench tests with the vehicle in Park
> and the key in the Off position.
