// Extended Database - Store data on EEPROM


// Check if Mac address is already in database, if true then it returns valid=true
unsigned int RecMac() {
  int valid = 0;
  for (int rec1 = 1; rec1 <= db.count(); rec1++)  {
    db.readRec(rec1, EDB_REC logEvent);
    if (logEvent.MAC_upp == current.MAC_upp && logEvent.MAC_low == current.MAC_low) {
      valid = 1;
      break;
    }

  }
  return valid;
}

// Check if UID is already in database, if true then it returns valid=true
boolean RecUID() {
  if (debug == true) {
    Serial.println("*******************");
    Serial.println("RecUID");
  }
  boolean valid = false;
  if (db.count() > 0) {
    for (int rec = 1; rec <= db.count(); rec++)  {
      if (debug == true) {
        Serial.print("Record number: ");
        Serial.println(rec);
      }

      db.readRec(rec, EDB_REC logEvent);
      if (logEvent.UID_upp == current.UID_upp && logEvent.UID_low == current.UID_low) {
        valid = true;
        break;
      }

    }
  }

  if (debug == true) {
    Serial.println("*******************");
  }
  return valid;
}


// Print all records in EEPROM
void PrintData() {
  Serial.println("*******************");
  Serial.println("DATABASE");
  for (int rec = 1; rec <= db.count(); rec++)  {
    db.readRec(rec, EDB_REC logEvent);
    Serial.print("Mac: "); Serial.print(logEvent.MAC_upp);  Serial.print("-");  Serial.println(logEvent.MAC_low);
    Serial.print("UID: "); Serial.print(logEvent.UID_upp);  Serial.print("-");  Serial.println(logEvent.UID_low);
    Serial.print("Name: "); Serial.print(logEvent.firstName);    Serial.print(" ");  Serial.println(logEvent.lastName);
  }
  Serial.println("*******************");
}


// Add data if it's possible
void AddCurrentToDB() {
  if (db.count() == db.limit()) {
    Serial.println("Error, No new users can be added!");
  }
  else {
    randomName();
    db.appendRec(EDB_REC current);
    Serial.println("Added data");
  }
}
