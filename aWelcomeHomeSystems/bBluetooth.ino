void BT_setup() {
  Serial3.begin(9600);
  Serial.println();
  Serial.println("BTserial started at 9600");
  Serial.println("Running setup . . .");
  delay(50);
  AT("AT", 0);
  AT("AT+RENEW", 0);
  AT("AT+NAMEWelcomeHome", 0);
  //AT("AT+MODE2", 0); <-- seems to break something
  AT("AT+ROLE0", 0); // slave
  AT("AT+SHOW3", 0);
  AT("AT+IMME0", 0);
  AT("AT+NOTI0", 0); // no notifications
  AT("AT+NOTP0", 0);
  AT("AT+RESET", 0);
  Serial.println("Setup complete");
}

unsigned long BT_last(unsigned int * lower, unsigned int * upper) { // give pointers to save MAC in
  Serial3.write("AT+RADD?");
  delay(100);
  int i = 0;
  char upp_hex[] = "000000";
  char low_hex[] = "000000";

  Serial3.find("RADD:");
  while (Serial3.available()) {
    if (i < 6) {
      upp_hex[i] = Serial3.read();
    } else {
      low_hex[i-6] = Serial3.read();
    }
    i++;
  }
  *lower = (int)strtol(low_hex, NULL, 16);
  *upper = (int)strtol(upp_hex, NULL, 16);
}

void AT(char* cmd, bool output) {
  // mod = 0 output off
  // mod = 1 output on
  // mod = 2 only output

  if (output == 0) {
    Serial3.write(cmd);
    Serial.print(cmd);
    while (!Serial3.find("OK")) {
      Serial.print('.');
    }
    while (Serial3.available() > 0 ) {
      Serial.read();
    }
    Serial.println(" OK");
  } else if (output == 1) {
    Serial3.write(cmd);
    Serial.println(cmd);
    delay(100);
    char c = ' ';                 // char for reading input
    while (Serial3.available()) {
      c = Serial3.read();
      Serial.write(c);
    }
    Serial.println("");
  } else if (output == 2) {
    Serial3.write(cmd);
    delay(100);
    char c = ' ';                 // char for reading input
    while (Serial3.available()) {
      c = Serial3.read();
      Serial.write(c);
    }
    Serial.println("");
  }

}
void BT_setting() {
  Serial.println("Current parameters");
  AT("AT+NAME?", 2);
  AT("AT+MODE?", 2);
  AT("AT+ROLE?", 2);
  AT("AT+SHOW?", 2);
  AT("AT+IMME?", 2);
  AT("AT+NOTI?", 2);
  AT("AT+NOTP?", 2);
  AT("AT+ADDR?", 2);
}
void BT_clearMAC() {
  AT("AT+CLEAR", 1);
}

