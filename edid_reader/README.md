# About

This is an Arduino sketch for reading Extended Display Identification Data (EDID) https://en.wikipedia.org/wiki/Extended_Display_Identification_Data

It requires a compatible breakout board.

# Connections

* HDMI Breakout Board Pin 15 (SCL)- Arduino Pin 21 (SCL)
* HDMI Breakout Board Pin 16 (SDA) - Arduino Pin 20 (SDA)
* HDMI Breakout Board Pin 17 (GND) - Arduino GND
* HDMI Breakout Board Pin 18 (5V) - Arduino 5V
* HDMI Breakout Board Pin 19 (Hot Plug Detection) - Arduino Pin 31

# Problems

No EDID data is received. Tested with Chromecast and with camera HDMI monitor.
