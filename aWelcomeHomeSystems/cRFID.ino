byte * rfidfunc(MFRC522 mfrc522, int debug) { // RFID
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  if (debug == 1) {
    Serial.println(F("**Card Detected:**"));
  }

  //-------------------------------------------

  for ( uint8_t i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
    if (debug == 1) {
      Serial.print(readCard[i], HEX);
    }

  }
  if (debug == 1) {
    Serial.println("");
  }


  if (debug == 1) {
    Serial.println(F("\n**End Reading**\n"));
  }


  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

return readCard;
  // Returnerer UID
}
