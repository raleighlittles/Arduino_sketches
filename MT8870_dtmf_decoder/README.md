# About

This is a simple sketch that uses the [MT8870 DTMF Decoder module](https://www.digikey.com/en/products/detail/microchip-technology/MT8870DE1/4309766) with an Arduino.

# Hardware

Obviously, you'll need a MT8870 board. I like [this](https://www.amazon.com/DEVMO-MT8870-Decoder-Telephone-Decoding/dp/B07T4G37XM) version.

Connect it as follows:

```
(board) (Arduino)
Q1  <--> Pin #3
Q2 <--> Pin #4
Q3 <--> Pin #5
Q4 <--> Pin #6
STQ <--> Pin #7
```

# Testing

Tested on an Arduino Due.
