# PinsToVGA
Hardware display pins, to VGA video via microcontroller


# 20 pins, 128x64 LCD Display

## As found in Elektron Monomachine

Initial investigation:

pin 1 at right, ground
(all others measured relative to pin 1)
2 3.84v
3 -4.48v
4 5.04v
5 NC
6 Noise during transitions
7-17 Noise / data channels (5v)
18 roughly -3v
19 5v
20 NC

Actual pinout:

1) Ground
2) Supply voltage 5V
3) Contrast adjustment
4 high) to display data
4 low) for instruction code
5 high) read from register
5 low) write to register
6 high) read data
6 falling) write data
7-14) 8-bit data
15) Active high, select IC1
16) Active high, select IC2
17) Active low, reset signal
18) Output voltage for LCD driving
19) Backlight 5V
29) Backlight ground

# Memory Storage in C

128px wide = 16 bytes
64 lines = 64 rows

byte buffer[64][16] = {}

# Scaled to 640x480

128x64 @ 5x

128 * 5 = 640
64 * 5 = 320

Vertical back porch lines 33
Vertical front porch lines 10
Vertical line count 525

33 + (525 - 33 - 10 - 320 / 2)
33 + 81 = 114
Start drawing at line 115

# VGA Spec on Teensy 3.2

Teensy 3.2 @ 96 MHz

Vertical Sync (frames):

60 Hz
64µs low sync pulse
Normal high

525 Total Lines
2 sync pulse lines
33 back porch lines
480 visible lines
10 front porch lines



Horizontal Sync (lines):

85 nops
3.8 µs (sync pulse)

39 nops
33 pixels
1.92 µs (back porch)

611 register writes
or 603 nops
25.4µs (draw time)

10 nops
640ns (front porch)