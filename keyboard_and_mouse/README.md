# About

This is an Arduino sketch file that lets you use your Arduino as a keyboard and mouse, via USB.

Requires the following:
* 4x4 keypad: ![keypad-image](https://cdn3.volusion.com/btfzd.umflq/v/vspfiles/photos/AD481-2.jpg?v-cache=1524502812)
* 5-pin joystick: ![joystick-image](http://img.fasttechcdn.com/132/1320202/1320202-4.jpg)

(I'm using an **Arduino Leonardo**, but any Arduino should work)

Pressing keys on the keypad will trigger corresponding keyboard events, and using the joystick will trigger mouse events.
You can also "click" (L3/R3) on the joystick, which will simulate the left-mouse button.

# Wiring

Here's how my components are connected.

## Joystick

```
Joystick "GND" <--> Arduino "GND"
Joystick "+5V" <--> Arduino "5V"
Joystick "VR_x" <--> Arduino "A0"
Joystick "VR_y" <--> Arduino "A1"
```

## Keypad

```
Keypad "R1" <--> Arduino "12"
Keypad "R2" <--> Arduino "11"
Keypad "R3" <--> Arduino "10"
Keypad "R4" <--> Arduino "9"
Keypad "C1" <--> Arduino "8"
Keypad "C2" <--> Arduino "7"
Keypad "C3" <--> Arduino "6"
Keypad "C4" <--> Arduino "5"
```

# Dependencies

You'll need to install the Arduino 'Keypad' library: https://playground.arduino.cc/Code/Keypad/
