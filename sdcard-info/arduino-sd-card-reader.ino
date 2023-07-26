// For use with "Zittop SD Card Reader/Writer for Arduino and Other Microcontrollers"
// ASIN: B0089SYU9C
// For a schematic on how to connect, see the following:
// https://drive.google.com/file/d/1ojHocPKLzVT2TlntYW7HabNw_vPQlf8j/view?usp=sharing
//
// Scroll to the bottom to see example output.

#include <SPI.h>

#include <SD.h>

Sd2Card card;
cid_t cid;
const int chipSelect = 10;

void setup() {
  Serial.begin(9600);

  Serial.print("Initializing SD card.");
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("Init failed");
  } else {
    Serial.println("Init OK");
  }

  Serial.println("Checking CID...");

  card.readCID( & cid);

  if (cid.always1 != 1) {
    Serial.print("ERROR: CID data was miread.");
    exit(1);
  }

  uint8_t * p = (uint8_t * ) & cid;
  for (int i = 0; i < sizeof(cid); i++) {
    Serial.print(p[i], HEX);
  }

  Serial.println("---------------");
  Serial.print("Manufacturer ID (0x): ");
  Serial.println(cid.mid, HEX);

  Serial.print("Product name: ");
  Serial.print(cid.pnm[0]);
  Serial.print(cid.pnm[1]);
  Serial.print(cid.pnm[2]);
  Serial.print(cid.pnm[3]);
  Serial.println(cid.pnm[4]);

  Serial.print("Product revision (m.n): ");
  Serial.print(cid.prv_m);
  Serial.print(".");
  Serial.println(cid.prv_n);

  Serial.print("Product serial number: ");
  Serial.println(cid.psn);

  Serial.print("Product Mfg date (YYYY-MM): ");
  Serial.print(2000 + cid.mdt_year_high);
  Serial.print("-");
  Serial.println(cid.mdt_month);

}

void loop() {

}

// Exmaple output from a random SD card I had lying around.
//
// Initializing SD card.Init OK
// Checking CID...
// 9F54492020202020219E91AAA1471---------------
// Manufacturer ID (0x): 9F
// Product name:      
// Product revision (m.n): 2.0
// Product serial number: 2853890329
// Product Mfg date (YYYY-MM): 2001-7

