#include <Mouse.h>
#include <Keyboard.h>
#include <Keypad.h> // Third-party library, from here: https://playground.arduino.cc/Code/Keypad/

// You'll need to adjust these based on how you connected the joystick to your Arduino
int horzPin = A0; // Mapped to 'VR_x'
int vertPin = A1; // Mapped to 'VR_y'
int selectPin = 2; // Mapped to 'SW'

int vertZero, horzZero;  // Stores the initial value of each axis, usually around 512
int vertValue, horzValue;  // Stores current analog output of each axis
const int sensitivity = 200;  // Higher sensitivity value = slower mouse, should be <= about 500
int mouseClickFlag = 0;

//int invertMouse = 1;        //Invert joystick based on orientation
int invertMouse = -1;         //Noninverted joystick based on orientation

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// You'll need to adjust rowPins and colPins to match whatever pins your keypad is connected to on the Arduino
// On a 3x3 keypad, the pinout is (starting from left to right): [R1, R2, R3, R4, C1, C2, C3] (6 pins)
// On a 4x4 keypad, the pinout is (starting from left to right): [R1, R2, R3, R4, C1, C2, C3, C4] (8 pins)
// where R denotes rows and C denotes columns
byte rowPins[ROWS] = {12, 11, 10, 9}; 
byte colPins[COLS] = {8, 7, 6, 5};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  pinMode(horzPin, INPUT);  // Set both analog pins as inputs
  pinMode(vertPin, INPUT);
  pinMode(selectPin, INPUT);  // set button select pin as input
  digitalWrite(selectPin, HIGH);  // Pull button select pin high
  delay(1000);  // short delay to let outputs settle
  vertZero = analogRead(vertPin);  // get the initial values
  horzZero = analogRead(horzPin);  // Joystick should be in neutral position when reading these

  Mouse.begin(); // Init mouse emulation
  Keyboard.begin(); // Init keyboard emulation
}

void loop() {
  // put your main code here, to run repeatedly:
  vertValue = analogRead(vertPin) - vertZero;  // read vertical offset
  horzValue = analogRead(horzPin) - horzZero;  // read horizontal offset

  if (vertValue != 0)
    Mouse.move(0, (invertMouse * (vertValue / sensitivity)), 0); // move mouse on y axis
  if (horzValue != 0)
    Mouse.move((invertMouse * (horzValue / sensitivity)), 0, 0); // move mouse on x axis

  if ((digitalRead(selectPin) == 0) && (!mouseClickFlag))  // if the joystick button is pressed
  {
    mouseClickFlag = 1;
    Mouse.press(MOUSE_LEFT);  // click the left button down
  }
  else if ((digitalRead(selectPin)) && (mouseClickFlag)) // if the joystick button is not pressed
  {
    mouseClickFlag = 0;
    Mouse.release(MOUSE_LEFT);  // release the left button
  }

  // Keypad section
  char customKey = customKeypad.getKey();

  if (customKey) {
    Keyboard.write(customKey);
  }
}
