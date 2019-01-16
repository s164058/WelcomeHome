void BT_setup() {
  Serial.begin(115200);
  BTserial.begin(9600);
  Serial.println();
  Serial.println("BTserial started at 9600");
  Serial.println("Running setup . . .");
  delay(50);
  AT("AT", 0);
  AT("AT+RENEW", 0);
  AT("AT+NAMEWelcomeHome", 0);
  //AT("AT+MODE2", 0); <-- seems to break something
  AT("AT+ROLE0", 0); // slave
  //AT("AT+SHOW3", 0);
  //AT("AT+IMME1", 0);
  AT("AT+NOTI0", 0); // no notifications
  //AT("AT+NOTP1", 0);
  AT("AT+RESET", 0);
  Serial.println("Setup complete");
}

void BT_last(char * mac) { // give pointer to save MAC in
  BTserial.write("AT+RADD?");
  delay(100);
  int i = 0;
  BTserial.find("RADD:");
  while (BTserial.available()) {
    mac[i] = BTserial.read();
    i++;
  }
  Serial.println("_________________");
  Serial.println(mac);
}

void AT(char* cmd, bool output) {
  // mod = 0 output off
  // mod = 1 output on
  // mod = 2 only output

  if (output == 0) {
    BTserial.write(cmd);
    Serial.print(cmd);
    while (!BTserial.find("OK")) {
      Serial.print('.');
    }
    while (BTserial.available() > 0 ) {
      Serial.read();
    }
    Serial.println(" OK");
  } else if (output == 1) {
    BTserial.write(cmd);
    Serial.println(cmd);
    delay(100);
    char c = ' ';                 // char for reading input
    while (BTserial.available()) {
      c = BTserial.read();
      Serial.write(c);
    }
    Serial.println("");
  } else if (output == 2) {
    BTserial.write(cmd);
    delay(100);
    char c = ' ';                 // char for reading input
    while (BTserial.available()) {
      c = BTserial.read();
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
}

