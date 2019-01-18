// Extended Database - Save on EEPROM or SD


// Finds number for record which match the Mac address
unsigned int RecMac(unsigned int wMAC_upp, unsigned int wMAC_low) {
  unsigned int counter = Users();
  int valid = 0;
  for (int rec1 = 1; rec1 <= counter; rec1++)  {
    db.readRec(rec1, EDB_REC logEvent);
    Serial.print(logEvent.MAC_upp); Serial.print("-");  Serial.println(logEvent.MAC_low);
    Serial.print(wMAC_upp);          Serial.print("-");  Serial.println(wMAC_low);


    if (logEvent.MAC_upp == wMAC_upp && logEvent.MAC_low == wMAC_low) {
      valid = 1;
      break;
    }

  }
  return valid;
}

// Finds number for record which match the UID address
unsigned int RecUID(unsigned int UID[4]){
  unsigned int counter = Users();
  for (int rec = 1; rec <= counter; rec++)  {
    db.readRec(rec, EDB_REC logEvent);
    if (logEvent.UID[0] == UID[0] && logEvent.UID[1] == UID[1] && logEvent.UID[2] == UID[2] && logEvent.UID[3] == UID[3]) {
      return rec;
    }
    else {
      int NotValid = 0;
      return NotValid;
    }
  }
}


// Print all records in EEPROM
void PrintData() {
  Serial.println("*******************");
  Serial.println("DATABASE");
  unsigned int counter = Users();
  for (int rec = 1; rec <= counter; rec++)  {
    db.readRec(rec, EDB_REC logEvent);
    Serial.print("Mac: ");  Serial.print(logEvent.MAC_upp); Serial.print("-"); Serial.println(logEvent.MAC_low);
    Serial.print("UID: ");  Serial.print(logEvent.UID[0]); Serial.print(logEvent.UID[1]); Serial.print(logEvent.UID[2]); Serial.println(logEvent.UID[3]);
    Serial.print("Name: "); Serial.println(logEvent.Name);
    Serial.print("Role: "); Serial.println(logEvent.Role);
  }
  Serial.println("*******************");
}

// Finds number of users
unsigned int Users() {
  unsigned int Users = db.count();
  Serial.print("Record Count: ");
  Serial.println(db.count());
  return Users;
}

// Add data if it's possible
void AddData(unsigned int wMAC_upp, unsigned int wMAC_low, unsigned int UID[4], char *Name1, uint8_t Role) {
  if (Users() == db.limit()) {
    Serial.println("Error, No new users can be added!");
  }
  else {
    logEvent.MAC_upp = wMAC_upp;
    logEvent.MAC_low = wMAC_low;
    for ( uint8_t i = 0; i < 4; i++) {
      logEvent.UID[i] = UID[i];
    }
    logEvent.Name = Name1;
    logEvent.Role = Role;
    db.appendRec(EDB_REC logEvent);
    Serial.println("Added data");
  }
}
