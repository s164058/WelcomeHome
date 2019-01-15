// Bluetooth
#include <SoftwareSerial.h>
SoftwareSerial BTserial(D6, D7);// (RX, TX)

void BT_setup() {
  Serial.begin(115200);
  BTserial.begin(9600);
  Serial.println();
  Serial.println("BTserial started at 9600");
  Serial.println("Running setup . . .");
  delay(50);
  AT("AT+RENEW");
  AT("AT+NAMEWelHo");
  AT("AT+ROLE0");
  AT("AT+SHOW3");
  AT("AT+IMME1");
  AT("AT+SCAN8");
  AT("AT+RESET");
}
void BT_last() {
  AT("AT+RESET");
}
void AT(char* cmd, int mod) {
  // mod = 0 output off
  // mod = 1 output on
  if (mod) {
    BTserial.write(cmd);
    Serial.print(cmd);
    char c = ' ';                 // char for reading input
    while (BTserial.available()) {
      c = BTserial.read();
      Serial.write(c);
    }
    Serial.println(". OK!");
  } else {
    BTserial.write(cmd);
    Serial.print(cmd);
    while (!BTserial.find("OK")) {
      Serial.print('.');
    }
    while (BTserial.available() > 0 ) {
      Serial.read();
    }
    Serial.println(". OK!");
  }
}
