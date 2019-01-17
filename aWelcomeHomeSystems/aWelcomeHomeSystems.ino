#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

#include "Arduino.h"
#include <EDB.h>    // Extended Database Library
#include <EEPROM.h> // Use the Internal Arduino EEPROM as storage

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

#define TABLE_SIZE 512 // Arduino 168 or greater, can be setted higher for MEGA
#define ResetTable 30

#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above

int currentState;
int nextState;
unsigned long startTime;
unsigned long timeElapsed;
int std_delay = 100; // delay per state in ms
bool first;

// Bluetooth setup_________________________________________________________________________________
SoftwareSerial BTserial(10, 11); // (SERIAL_RX, SERIAL_TX) CONNECT TO (BT_TX, BT_RX)

// RFID setup______________________________________________________________________________________
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance




// WiFi setup______________________________________________________________________________________


// Sensors setup___________________________________________________________________________________



<<<<<<< HEAD
// EDB setup_______________________________________________________________________________________
=======
// EDB setup_____________________________________________________________________________________:
// The read and write handlers for using the EEPROM Library
void writer(unsigned long address, byte data) {
  EEPROM.write(address, data);
}
byte reader(unsigned long address) {
  return EEPROM.read(address);
}
// Create an EDB object with the appropriate write and read handlers
EDB db(&writer, &reader);

// Arbitrary record definition for this table.
struct LogEvent {
  char *Mac;
  unsigned int UID[4];
  char *name;
  uint8_t Role;
}
logEvent;

>>>>>>> e11b33424c7c8e2a438dfdfdc9b64bd7c7b8f88d


int buttonState = 0;


// Output setup____________________________________________________________________________________



// LCD setup_______________________________________________________________________________________




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
  SPI.begin(); // Start SPI bus
  mfrc522.PCD_Init(); // Start RFID reader
  //Serial.println("RFID card starte");
  //Serial.print(F("Reader "));
  //Serial.print(F(": "));
  //mfrc522.PCD_DumpVersionToSerial();

  // WiFi setup_____________________________________________________________________________________:
  //WiFi.mode(WIFI_STA);


  // Thingspeak setup_____________________________________________________________________________________:
  //ThingSpeak.begin(client);  // Initialize ThingSpeak


  // Sensors setup_____________________________________________________________________________________:



  // EDB setup_____________________________________________________________________________________:
  pinMode(ResetTable, INPUT_PULLUP);


  // Output setup_____________________________________________________________________________________:



  // LCD setup_____________________________________________________________________________________:



}

char BTmac[] = "000000000000"; //4E4424073BB7 //6CB4F55C9646 //5F7F9129578C
unsigned int UID = {0,0,0,0};                // Unsigned integer array, for saving UID to an array(prevents overflow)

void loop() {
<<<<<<< HEAD
=======
  buttonState = digitalRead(ResetTable);
    if (buttonState == LOW) {
      db.create(0, TABLE_SIZE, sizeof(logEvent)); // Creates new table
      Serial.println("Table reset done!");
    }

<<<<<<< HEAD
  // put your main code here, to run repeatedly:
=======

>>>>>>> 12287848d4ed3fe731cb524895560cf731d720af
>>>>>>> e11b33424c7c8e2a438dfdfdc9b64bd7c7b8f88d
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
      Serial.println("--> STATE BT");
      BT_last(BTmac);
      if(strcmp("000000000000", BTmac) == 0){
        nextState = NFC;
      }else{
        nextState = WELCOME;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case NFC:
      if (first) {
        // Init of state
        // Runs only one time
        Serial.println("--> STATE NFC");
        first = false;
      }
      // State
      if (UID[0] == 0) { //Need timing? [ms]
        nextState = BT;
      }else{
        nextState = WELCOME;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case NFC_MASTER:
      if (first) {
        // Init of state
        // Runs only one time
        Serial.println("--> STATE NFC_MASTER");
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
        Serial.println("--> STATE NFC_NEW");
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
        // Init of state. Runs only one time
        Serial.println("--> STATE WELCOME");
        Serial.print("WELCOME");
        Serial.println(BTmac);
        first = false;
      }
      // State
      if (timeElapsed > 5000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WAIT:
      if (first) {
        Serial.println("--> STATE WAIT");
        first = false;
      }
      if (timeElapsed > 2000) {
        nextState = BT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WRONG:
      if (first) {
        // Init of state
        // Runs only one time
        Serial.println("--> STATE WRONG");
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
        Serial.println("--> STATE NEW_USER");
        first = false;
      }
      // State
      if (timeElapsed > 1000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    default:
      Serial.println("!!! Unknown state !!!");
      nextState = WAIT;
      break;
  }
  delay(std_delay);
}
