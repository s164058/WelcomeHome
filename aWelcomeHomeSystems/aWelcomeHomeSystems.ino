// Std. setup_____________________________________________________________________________________:
// State definitions
#define STATE_1 1
#define STATE_2 2
#define STATE_3 3

int currentState;
int nextState;
unsigned long startTime;
unsigned long timeElapsed;
int std_delay = 5; // delay per state in ms

// Bluetooth setup_____________________________________________________________________________________:
#include <SoftwareSerial.h>
SoftwareSerial BTserial(D6, D7); // (SERIAL_RX, SERIAL_TX) CONNECT TO (BT_TX, BT_RX)

// RFID setup_____________________________________________________________________________________:
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

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

byte readCard[4];   // Stores scanned ID read from RFID Module
byte UID;

// WiFi setup_____________________________________________________________________________________:
/*#include <ESP8266WiFi.h>

  char ssid[] = SECRET_SSID;   // your network SSID (name)
  char pass[] = SECRET_PASS;   // your network password
  int keyIndex = 0;            // your network key Index number (needed only for WEP)
  WiFiClient  client;


  // Thingspeak setup_____________________________________________________________________________________:
  #include "ThingSpeak.h"
  #include "secrets.h"

  unsigned long myChannelNumber = SECRET_CH_ID;
  const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
*/

// Sensors setup_____________________________________________________________________________________:



// EDB setup_____________________________________________________________________________________:



// Output setup_____________________________________________________________________________________:



// LCD setup_____________________________________________________________________________________:




void setup() {
  // Std. setup_____________________________________________________________________________________:
  Serial.begin(9600); // Starts a serial connection
  currentState = STATE_1;
  nextState = STATE_1;
  startTime = millis();   // Save starting time


  // Bluetooth setup_____________________________________________________________________________________:
  BT_setup();


  // RFID setup_____________________________________________________________________________________:
  SPI.begin(); // Start SPI bus
  mfrc522.PCD_Init(); // Start RFID reader

  // WiFi setup_____________________________________________________________________________________:
  //WiFi.mode(WIFI_STA);


  // Thingspeak setup_____________________________________________________________________________________:
  //ThingSpeak.begin(client);  // Initialize ThingSpeak


  // Sensors setup_____________________________________________________________________________________:



  // EDB setup_____________________________________________________________________________________:



  // Output setup_____________________________________________________________________________________:



  // LCD setup_____________________________________________________________________________________:



}

void loop() {
  // put your main code here, to run repeatedly:
  UID = rfidfunc(mfrc522, 1);
  Serial.println(UID);
  //Next state?
  if (nextState != currentState) {
    startTime = millis();
    currentState = nextState;
  }
  timeElapsed = millis() - startTime;

  // State Logic
  switch (currentState) {
    case STATE_1:
      Serial.println("Im in state 1");

      if (timeElapsed > 1000) {
        nextState = STATE_2;
      }
      break;
    case STATE_2:
      Serial.println("Im in state 2");
      if (timeElapsed > 1000) {
        nextState = STATE_3;
      }
      break;
    case STATE_3:
      Serial.println("Im in state 3");
      if (timeElapsed > 1000) {
        nextState = STATE_1;
      }
      break;
    default:
      Serial.println("Unknown state!");
      nextState = STATE_1;
      break;
  }

  delay(std_delay);
}
