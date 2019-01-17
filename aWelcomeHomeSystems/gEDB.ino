// Extended Database - Save on EEPROM or SD


// Finds number for record which match the Mac address
unsigned int RecMac(EDB db, char *Mac) {
  unsigned int counter = Users(db);
  for (int rec = 1; rec <= counter; rec++)  {
    db.readRec(rec, EDB_REC logEvent);
    if (String(logEvent.Mac).equals(String(Mac))) {
      return rec;
      break;
    }
  }
}

// Finds number for record which match the UID address
unsigned int RecMac(EDB db, unsigned int UID[4]) {
  unsigned int counter = Users(db);
  for (int rec = 1; rec <= counter; rec++)  {
    db.readRec(rec, EDB_REC logEvent);
    if (logEvent.UID[0] == UID[0] && logEvent.UID[1] == UID[1] && logEvent.UID[2] == UID[2] && logEvent.UID[3] == UID[3]) {
      return rec;
      break;
    }
  }
}


// Print all records in EEPROM
void PrintData(EDB db) {
  unsigned int counter = Users(db);
  for (int rec = 1; rec <= counter; rec++)  {
    db.readRec(rec, EDB_REC logEvent);
    Serial.print("Mac: "); Serial.println(logEvent.Mac);
    Serial.print("UID: "); Serial.print(logEvent.UID[0]); Serial.print(logEvent.UID[1]); Serial.print(logEvent.UID[2]); Serial.println(logEvent.UID[3]);
    Serial.print("Name: "); Serial.println(logEvent.name);
    Serial.print("Role: "); Serial.println(logEvent.Role);
  }
}

// Finds number of users
unsigned int Users(EDB db) {
  unsigned int Users = db.count();
  Serial.print("Record Count: ");
  Serial.println(db.count());
  return Users;
}

// Add data if it's possible
void AddData(EDB db, char *Mac, unsigned int UID[4],  char *Name,  uint8_t Role) {
  if (Users(db) == db.limit()) {
    Serial.println("Error, No new users can be added!");
  }
  else {
    logEvent.Mac = Mac;
    for ( uint8_t i = 0; i < 4; i++) {
      logEvent.UID[i] = UID[i];
    }
    logEvent.name = Name;
    logEvent.Role = Role;
    db.appendRec(EDB_REC logEvent);
  }
}
