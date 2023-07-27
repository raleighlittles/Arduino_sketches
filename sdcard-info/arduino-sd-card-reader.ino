/**
  Sketch for reading Card Identification Registers and Card-Specific Data registers from SD cards.
  Most of the information came from "Part 1: Physical Layer Specification" published by the SD card standard.

  Additional links:
  * http://problemkaputt.de/gbatek-dsi-sd-mmc-protocol-csd-register-128bit-card-specific-data-version-2-0.htm

**/
#include <SPI.h>
#include <SD.h>

enum FileFormat {
    HARD_DISK_LIKE = 0,
    FLOPPY_LIKE = 1,
    UNIVERSAL = 2,
    UNKNOWN = 3,
};

Sd2Card sdCard;

const int sdChipSelect = 10;

const int TRAN_SPEED_25MHZ = 0x32;
const int TRAN_SPEED_50MHZ = 0x5A;
const int TRAN_SPEED_100MBPS = 0x0B;
const int TRAN_SPEED_200MBPS = 0x2B;

void setup() {

  Serial.begin(9600);

  delay(100);

  if (!sdCard.init(SPI_FULL_SPEED, sdChipSelect)) {
    Serial.println("ERROR init. SD reader");
    delay(100);
  }
  else {
    Serial.println("SD reader init. OK");
  }

  delay(100);
}

void loop() {

  delay(3000);

      /// Card Identification Register
      cid_t cid;
      sdCard.readCID(&cid);

      if (cid.always1 != 1) {
        delay(10);
        Serial.print("ERROR: CID register data was miread");
        exit(1);
      }

      Serial.println("\n---------- CID ----------");

      uint8_t* pCid = (uint8_t*) & cid;
      for (int i = 0; i < sizeof(cid); i++) {
        Serial.print(pCid[i], HEX);
      }

      Serial.println("\n--------------------");

      Serial.print("Manufacturer ID: 0x");
      Serial.println(cid.mid, HEX);

      Serial.print("OEM/Application ID: 0x");
      Serial.print(cid.oid[0], HEX);
      Serial.println(cid.oid[1], HEX);

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

      /// -------------------
      /// Card Specific Data
      csd_t csd;
      sdCard.readCSD(&csd);

      if (csd.v2.always1 != 1) {
        delay(10);
        Serial.print("ERROR: CSD register data was misread");
        exit(2);
      }

      Serial.println("\n========== CSD ==========");

      uint8_t* pCsd = (uint8_t*)& csd;
      for (int i = 0; i < sizeof(csd); i++) {
        Serial.print(pCsd[i], HEX);
      }

      Serial.println("\n====================");

      Serial.print("Trans speed: ");
      uint8_t transferSpeed = csd.v2.tran_speed;
      Serial.print(transferSpeed);
      Serial.print("d | ");

      switch (transferSpeed) {

        case TRAN_SPEED_25MHZ:
          Serial.println("25 MHz (SDSC/SDHC/SDXC in Default Speed mode)");
          break;


        case TRAN_SPEED_50MHZ:
          Serial.println("50 MHz (SDSC/SDHC/SDXC in High Speed mode)");
          break;

        case TRAN_SPEED_100MBPS:
          Serial.println("100 Mbps (SDHC/SDXC in SDR50 or DDR50 mode)");
          break;

        case TRAN_SPEED_200MBPS:
          Serial.println("200 Mbps (SDHC/SDXC in SDR104 mode)");
          break;

        default:
          Serial.println("Unknown transfer rate");
          break;
      }

      Serial.print("Implements DSR?");
      
      if (csd.v2.dsr_imp == 0) {
        Serial.println(" n");
      }
      else if (csd.v2.dsr_imp == 1) {
        Serial.println(" Y");
      }
      else {
        Serial.println(" ???");
      }


      Serial.print("CSIZE = ");

      // This is a 12-bit wide register. The 0x3F masks off the 2 upper bits
      uint32_t c_size = (((uint32_t)csd.v2.c_size_high & 0x3F) << 16) | ((uint16_t)csd.v2.c_size_mid << 8) | csd.v2.c_size_low;

      Serial.print(c_size);
      Serial.print(" | ");
      // TODO Figure out exactly how to determine whether the right value is 512 or not.
      // There's a read block length and a write block length, which one to use here? What's the difference?
      uint32_t memCapacity_kb = (c_size + 1) * 512;
      Serial.print(memCapacity_kb);
      Serial.println(" KB");

      if ((csd.v2.tmp_write_protect == 1) || (csd.v2.perm_write_protect == 1)) {
        Serial.println("!Write protection found!");
      }

      Serial.print("Contains partition info? ");

      switch (csd.v2.file_format) {

        case FileFormat::HARD_DISK_LIKE:
          Serial.println("Y");
          break;
        

        case FileFormat::FLOPPY_LIKE: 
          Serial.println("N, Boot sector only");
          break;
        

        case FileFormat::UNIVERSAL: 
          Serial.println("N/A ~ Universal file format");
          break;
        

        case FileFormat::UNKNOWN: 
          Serial.println("Unknown ???");
          break;
        

        default:
          Serial.println("Unable to decode file format");
          break;
      }

      // Can't read the Card Status Register, because the `readRegister()` method is private
      // uint8_t csr[32];
      // uint32_t csr_retcode = sdCard.readRegister(CMD13, &csr); // Page 89 of standards document
}

// Exmaple output from a random SD card I had lying around.
//
// 22:49:02.345 -> ---------------
// 22:49:02.378 -> 1D414453442020202A0901F814BBB
// 22:49:02.410 -> ---------------
// 22:49:02.410 -> Manufacturer ID: 0x1D
// 22:49:02.442 -> Product name: SD   
// 22:49:02.474 -> Product revision (m.n): 2.0
// 22:49:02.507 -> Product serial number: 4160852128
// 22:49:02.539 -> Product Mfg date (YYYY-MM): 2001-11