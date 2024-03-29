#include <Wire.h>


const int hotPlugPin = 31;

void setup() {

  Wire.begin();
  SerialUSB.begin(9600);
  pinMode(hotPlugPin, OUTPUT);

}

void loop() {

  digitalWrite(hotPlugPin, HIGH);

  delay(10);

  int bytes_requested = 256;

  Wire.requestFrom(0x50, bytes_requested);

  if (Wire.available() > 1) {

    SerialUSB.println("EDID Data Received");

    while ((Wire.available() != 0) && (bytes_requested != 0)) {
      int data_byte = Wire.read();
      bytes_requested--;
      SerialUSB.print(data_byte);
    }

  } else {
    SerialUSB.println("No EDID data present");
    delay(5 * 1000);
  }
}
