
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


int RFIDfunc() {
  /*if (UID[0] != 0 && UID[1] != 0 && UID[2] != 0 && UID[3] != 0) {
    for ( uint8_t i = 0; i < 4; i++) {
      oldUID[i] = UID[i];
    }
  }*/

  byte readCard[4];   // Stores scanned ID read from RFID Module

  if ( mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      // Read UID from RFID tag, then convert to unsigned integer array by first converting to String then to integer(keep integer values without converting to ASCII)
      for ( uint8_t i = 0; i < 4; i++) {
        readCard[i] = mfrc522.uid.uidByte[i];
        //Cur[i] = String(readCard[i]).toInt();
        //if (oldUID[i] != String(readCard[i]).toInt()) {
          UID[i] = String(readCard[i]).toInt();
        /*}
        else {
          UID[i] = 0;
        }*/
      }

      mfrc522.PCD_StopCrypto1(); // Exit/stop communication with device/tag
    }
  }
  else {
    //setZero(); // Return UID = 0000, when no tag is identified
  }

  return UID;
}

int setZero() {
  for ( uint8_t i = 0; i < 4; i++) {
    UID[i] = 0;
  }
  return UID;
}

void PrintUID() {
  // Print UID to Serial monitor
  for (int i = 0; i < 4; i++) {
    Serial.print(UID[i]);
    Serial.print("  ");
  }
  Serial.println("");
}
