// RFID
if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  Serial.println(F("**Card Detected:**"));

 //-------------------------------------------

  for ( uint8_t i = 0; i < 4; i++) {  //
   readCard[i] = mfrc522.uid.uidByte[i];
   Serial.print(readCard[i], HEX);
 }
 Serial.println("");

 //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

 //-------------------------------------------



 Serial.println(F("\n**End Reading**\n"));
 delay(1000); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
