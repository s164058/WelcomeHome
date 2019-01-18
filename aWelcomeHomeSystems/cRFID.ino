
/*

   Uses MIFARE RFID card using RFID-RC522 reader
   Uses MFRC522 - Library
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15



   NodeMCU
   // SDA/SS -> D2(GPIO 4)
   // SCK -> D5(GPIO 14)
   // MOSI -> D7(GPIO 13)
   // MISO/SCL -> D6(GPIO 12)
   // IRQ -> NOT CONNECTED
   // GND -> GND
   // RST -> D1(GPIO 5)
   // VCC -> 3.3V
*/


void RFIDfunc(MFRC522 mfrc522_func, boolean debug_func) {

  if (debug_func == true) {
    Serial.println("*******************");
    Serial.println("RFID");
  }

  byte readCard[4];                   // Byte array for reading UID in RFID function
  String str1 = "";                   // String for saving first two bytes of UID
  String str2 = "";                   // String for saving last two bytes of UID

  if ( mfrc522_func.PICC_IsNewCardPresent() ) {
    if (mfrc522_func.PICC_ReadCardSerial()) {

      // Read UID from RFID tag, then convert to unsigned integer array by first converting to String then to integer(keep integer values without converting to ASCII)
      for ( uint8_t i = 0; i < 4; i++) {
        readCard[i] = mfrc522_func.uid.uidByte[i];

        if (debug_func == true) {
          str += String(readCard[i]);
          Serial.print(readCard[i]);
          Serial.print("-");
        }

        // Seperate to 2 parts of the total UID
        if (i < 2) {
          str1 += String(readCard[i]);
        }
        else {
          str2 += String(readCard[i]);
        }

      }


      // Convert parts of UID to uint32_t
      UIDupper = str1.toInt();
      UIDlower = str2.toInt();


      if (debug_func == true) {
        Serial.println("");
        Serial.print("UID1: "); Serial.println(UID_upper_func);
        Serial.print("UID2: "); Serial.println(UIDlower);
        Serial.println("*******************");
      }

      mfrc522_func.PCD_StopCrypto1(); // Exit/stop communication with device/tag
    }

  }
  else {
    setZero(); // Reset when no card detected
  }
  return;
}

// Reset UID
void setZero() {
  UIDupper = 0;
  UIDlower = 0;
  return;
}

// Print UID to Serial monitor
void PrintUID(uint32_t UID_upper, uint32_t UIDlower) {
  Serial.println("*******************");
  Serial.println("PrintUID");
  Serial.print("UID1: "); Serial.println(UIDupper);
  Serial.print("UID2: "); Serial.println(UIDlower);
  Serial.println("*******************");
}
