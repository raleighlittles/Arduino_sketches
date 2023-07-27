# About

The sketch in this directory reads an attached SD card's [Card Identification register (CID)](https://www.cameramemoryspeed.com/sd-memory-card-faq/reading-sd-card-cid-serial-psn-internal-numbers/) and [Card-Specific Data (CSD) register](https://en.wikipedia.org/wiki/SD_card).

When connected, you'll see output that looks like this:

```
00:08:38.422 -> SD reader init. OK
00:08:41.535 -> 
00:08:41.535 -> ---------- CID ----------
00:08:41.535 -> 1D414453442020202A0901F814BBB
00:08:41.568 -> --------------------
00:08:41.600 -> Manufacturer ID: 0x1D
00:08:41.632 -> OEM/Application ID: 0x4144
00:08:41.664 -> Product name: SD   
00:08:41.664 -> Product revision (m.n): 2.0
00:08:41.697 -> Product serial number: 4160852128
00:08:41.729 -> Product Mfg date (YYYY-MM): 2001-11
00:08:41.793 -> 
00:08:41.793 -> ========== CSD ==========
00:08:41.826 -> 40E0325B590075AD7F80A40045
00:08:41.826 -> ====================
00:08:41.858 -> Trans speed: 50d | 25 MHz (SDSC/SDHC/SDXC in Default Speed mode)
00:08:41.921 -> Implements DSR? n
00:08:41.954 -> CSIZE = 30125 | 15424512 KB
00:08:41.986 -> Contains partition info? Y
```

# Setup

Obviously, you'll need some kind of SD card breakout board. Connect it to your Arduino, using PIN #10 as the Chip Select pin. Here's the mapping I used:


```
CHIP SELECT <--> PIN #10
MOSI <--> PIN #11
MISO <--> PIN #12
SCK <--> PIN #13
```

# Testing

Tested with an Arduino Uno. Used 8062 bytes of flash.