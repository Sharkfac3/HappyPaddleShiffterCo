# ArduinoCode — Build & Flash Guide

Firmware for the Jeep XJ AW4 paddle shifter controller.
For full technical specification (pin assignments, state machine, solenoid mapping)
see [`SYSTEM.md`](SYSTEM.md).

---

## Required Hardware

| Component | Specification | Notes |
|---|---|---|
| Microcontroller | Arduino Mega 2560 | Must be Mega — Uno SPI pins conflict with solenoid outputs |
| Relay / driver board | 3-channel, 5V logic, 12V/2A per channel | Must handle inductive loads. Add flyback diodes (1N4007) if not built in |
| Solenoid flyback diodes | 1N4007 x3 | One across each solenoid coil. Skip if driver board has built-in protection |
| OLED display | WaveShare 1.5" RGB OLED (SSD1351 driver, 128×128) | 3.3V only — do not connect to 5V |
| Paddle switches | Momentary normally-open, active LOW | One per paddle (shift up / shift down) |
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
2. Go to **Tools → Board** and select **Arduino Mega or Mega 2560**.
3. Go to **Tools → Processor** and select **ATmega2560**.
4. Connect the Arduino Mega to your computer via USB.
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
   If blank or corrupted: check DIN→51, CLK→52, CS→A5, DC→A4, RES→A3. Check VCC is 3.3V.

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
