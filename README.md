# Lambda Terminal

This is a Half-Life themed controller I designed around an ESP32-S3. It has a rotary encoder, three Choc switches, a little OLED and a buzzer, but the part I'm most excited about is the touch stuff: a honeycomb of three hex pads and a four segment zigzag slider, all made out of copper on the PCB itself. No moving parts, no extra chips.

The board is exactly 100 x 100 mm, which keeps it in JLCPCB's cheapest size tier. It also has a big lambda on it, because of course it does.

## Features

- Waveshare ESP32-S3-Zero, so native USB
- 3 hex capacitive touch pads (12 mm flat to flat) in a honeycomb
- 4 segment zigzag touch slider, which gives you a position instead of just on/off
- EC11 rotary encoder
- 3x Kailh Choc low profile switches
- I2C OLED
- Buzzer
- 100 x 100 mm, 2 layers, rounded corners and 4 mounting holes
- Lambda logo in exposed copper and hazard stripes on the silkscreen

## Case

There isn't one yet. For now it's just the board, with 4 M3 holes in the corners so you can put it on standoffs.

## PCB

Here's the schematic and the board. Everything was made in KiCad.<img width="1452" height="1194" alt="Screenshot 2026-11-07 174923" src="https://github.com/user-attachments/assets/f5e75a64-d1bf-4909-aacc-aa7b0c76d74a" />


<img width="1558" height="1112" alt="Screenshot 2026-11-07 174553" src="https://github.com/user-attachments/assets/e8727eca-e229-40d7-8ba5-2d3167f477d2" /><img width="1402" height="1280" alt="Screenshot 2026-11-07 174541" src="https://github.com/user-attachments/assets/c04ff3ed-34cf-44be-84db-fc265c8d37f7" />
<img width="1041" height="887" alt="Screenshot 2026-11-07 174640" src="https://github.com/user-attachments/assets/ad055e5c-17c6-4585-9d40-7291652422ad" />


A few things I want to say about it:

- The touch pads are an ESP32-S3 thing. The chip can read capacitance on GPIO 1 to 14 by itself, so I didn't need a separate touch IC. I did think about an MPR121, but I only needed 7 channels and the S3 has enough.
- The pads are covered by solder mask. It's thin enough that touch still works, and your finger never touches bare copper.
- The touch traces go to the back of the board through a via and stay away from the other signals, because anything running near a touch pad ends up affecting it.
- They're long though (somewhere between 35 and 85 mm), so expect to tune the thresholds in firmware.
- I wanted orange pads. JLCPCB doesn't have an orange solder mask, and their silkscreen is white only, so the board is black with white text and the lambda is exposed copper. If you order ENIG it comes out gold, with HASL it's silver.
### Pin map

| Part | GPIO |
|---|---|
| Hex pad 1, 2, 3 | 1, 2, 3 |
| Slider segments (top to bottom) | 8, 9, 6, 7 |
| Encoder A, B | 10, 11 |
| Switch 1, 2, 3 | 12, 44 (RX), 43 (TX) |
| Buzzer | 13 |
| OLED SCL, SDA | 4, 5 |

The switches and the encoder go to GND, so use internal pull-ups.

## Firmware Overview

Nothing is flashed yet, the firmware is the next thing on the list. This is the plan:

- Show up as a USB MIDI device over the S3's native USB
- Hex pads play notes
- The slider sends a continuous value (position 0 to 127)
- The encoder changes volume
- The switches do octave down, octave up and sustain
- The OLED shows what's going on and the buzzer clicks when you hit something

## BOM

- 1x Waveshare ESP32-S3-Zero
- 1x EC11 rotary encoder with push switch
- 3x Kailh Choc low profile switches (and keycaps if you want them)
- 1x 128x64 I2C OLED (SSD1306)
- 1x buzzer, 12 mm
- 1x PCB, 100 x 100 mm
- 4x M3 screws and standoffs (optional)

One heads up on the OLED: the footprint is the 8 pin Adafruit SSD1306 breakout, so check that your module actually matches it before you order the boards. A lot of the cheap 4 pin ones don't.
