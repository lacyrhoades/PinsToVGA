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
