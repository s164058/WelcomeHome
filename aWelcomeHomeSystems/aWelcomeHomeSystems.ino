#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

// Std. setup_____________________________________________________________________________________:
// State definitions
#define BT 101
#define NFC 102
#define NFC_MASTER 103
#define NFC_NEW 104
#define WELCOME 105
#define WAIT 106
#define WRONG 107
#define NEW_USER 108


#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above

int currentState;
int nextState;
unsigned long startTime;
unsigned long timeElapsed;
int std_delay = 100; // delay per state in ms
bool first;

// Bluetooth setup_____________________________________________________________________________________:
//SoftwareSerial BTserial(D6, D7); // (SERIAL_RX, SERIAL_TX) CONNECT TO (BT_TX, BT_RX)

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




//MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

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


SoftwareSerial BTserial(D6, D7); // (SERIAL_RX, SERIAL_TX) CONNECT TO (BT_TX, BT_RX)


void setup() {
  // Std. setup_____________________________________________________________________________________:
  Serial.begin(115200); // Starts a serial connection
  currentState = WAIT;
  nextState = WAIT;
  startTime = millis();   // Save starting time
  first = true;           // Variable for init of states

  // Bluetooth setup_____________________________________________________________________________________:
  BT_setup();
  BT_setting();


  // RFID setup_____________________________________________________________________________________:
  //SPI.begin(); // Start SPI bus
  //mfrc522.PCD_Init(); // Start RFID reader

  // WiFi setup_____________________________________________________________________________________:
  //WiFi.mode(WIFI_STA);


  // Thingspeak setup_____________________________________________________________________________________:
  //ThingSpeak.begin(client);  // Initialize ThingSpeak


  // Sensors setup_____________________________________________________________________________________:



  // EDB setup_____________________________________________________________________________________:



  // Output setup_____________________________________________________________________________________:



  // LCD setup_____________________________________________________________________________________:



}

char BTmac[] = "00xxx0000000"; //4E4424073BB7 //6CB4F55C9646 //5F7F9129578C

void loop() {
  // put your main code here, to run repeatedly:
  //Next state?
  if (nextState != currentState) {
    startTime = millis();
    currentState = nextState;
    first = true;
  }
  timeElapsed = millis() - startTime;
  //UID = rfidfunc(mfrc522, 1);
  //Serial.println(UID);
  // State Logic
  switch (currentState) {
    //-----------------------------------------------------------------------------------------------
    case BT:
      Serial.println("Scanning BT");
      BT_last(BTmac);
      nextState = WAIT;
      break;
    //-----------------------------------------------------------------------------------------------
    case NFC:
      if (first) {
        // Init of state
        // Runs only one time
        first = false;
      }
      // State
      if (timeElapsed > 1000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case NFC_MASTER:
      if (first) {
        // Init of state
        // Runs only one time
        first = false;
      }
      // State
      if (timeElapsed > 1000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case NFC_NEW:
      if (first) {
        // Init of state
        // Runs only one time
        first = false;
      }
      // State
      if (timeElapsed > 1000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WELCOME:
      if (first) {
        // Init of state
        // Runs only one time
        first = false;
      }
      // State
      if (timeElapsed > 1000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WAIT:
      if (first) {
        Serial.println("Waiting . . .");
        first = false;
      }
      if (timeElapsed > 2000) {
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WRONG:
      if (first) {
        // Init of state
        // Runs only one time
        first = false;
      }
      // State
      if (timeElapsed > 1000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case NEW_USER:
      if (first) {
        // Init of state
        // Runs only one time
        first = false;
      }
      // State
      if (timeElapsed > 1000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    default:
      Serial.println("Unknown state!");
      nextState = WAIT;
      break;
  }
  delay(std_delay);
}
