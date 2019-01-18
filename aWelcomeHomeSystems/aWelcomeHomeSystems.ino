//#include <SoftwareSerial.h>
#include <SPI.h>
#include <MFRC522.h>

#include "Arduino.h"
#include <EDB.h>    // Extended Database Library
#include <EEPROM.h> // Use the Internal Arduino EEPROM as storage
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

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
#define motionSensor 35

#define RST_PIN         49           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above

#define baud 115200



int currentState;
int nextState;
unsigned long startTime;
unsigned long timeElapsed;
int std_delay = 100; // delay per state in ms
bool first;

// Bluetooth setup_________________________________________________________________________________
//SoftwareSerial BTserial(38, 40); // (SERIAL_RX, SERIAL_TX) CONNECT TO (BT_TX, BT_RX) ONLY FOR ESP

// RFID setup______________________________________________________________________________________
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

uint32_t Master_upp = 145254;
uint32_t Master_low = 23197;



// WiFi setup______________________________________________________________________________________


// Sensors setup___________________________________________________________________________________
boolean motion = 0;


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
  uint32_t MAC_upp;
  uint32_t MAC_low;
  uint32_t UID_upp;
  uint32_t UID_low;
  char *Name;
}
logEvent, current;

int buttonState = 0;


// Output setup____________________________________________________________________________________



// LCD setup_______________________________________________________________________________________
uint8_t bell[8]  = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8]  = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t duck[8]  = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t check[8] = {0x0, 0x1 , 0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {  0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);



boolean debug = false; // Show debug messages

void setup() {
  // Std. setup_____________________________________________________________________________________:
  Serial.begin(baud); // Starts a serial connection
  currentState = WAIT;
  nextState = WAIT;
  startTime = millis();   // Save starting time
  first = true;           // Variable for init of states

  clearAll();

  // Bluetooth setup_____________________________________________________________________________________:
  BT_setup();
  BT_setting();


  // RFID setup_____________________________________________________________________________________:
  SPI.begin(); // Start SPI bus
  mfrc522.PCD_Init(); // Start RFID reader
  Serial.println("RFID card started");
  Serial.print("RFID reader: ");
  mfrc522.PCD_DumpVersionToSerial();

  // WiFi setup_____________________________________________________________________________________:
  //WiFi.mode(WIFI_STA);


  // Thingspeak setup_____________________________________________________________________________________:
  //ThingSpeak.begin(client);  // Initialize ThingSpeak


  // Sensors setup_____________________________________________________________________________________:
  pinMode(motionSensor, INPUT_PULLUP);



  // EDB setup_____________________________________________________________________________________:
  pinMode(ResetTable, INPUT_PULLUP);


  // Output setup_____________________________________________________________________________________:



  // LCD setup_____________________________________________________________________________________:
  LCD_setup();

  buttonState = digitalRead(ResetTable);
  if (buttonState == LOW) {
    db.create(0, TABLE_SIZE, sizeof(logEvent)); // Creates new table
    Serial.println("Table reset done!");
  } else {
    db.open(0);
  }
}


void loop() {

  motion = digitalRead(motionSensor);


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
      BT_last();
      LCD_BT();

      if (current.MAC_upp == 0 && current.MAC_low == 0) {
        if (motion) {
          nextState = NFC;
        } else {
          nextState = WAIT;
        }

      } else {
        if (RecMac() == 1) {
          nextState = WELCOME;
        } else {
          nextState = NFC_MASTER;
        }
      }

      break;
    //-----------------------------------------------------------------------------------------------
    case NFC:
      if (first) {
        // Init of state
        // Runs only one time
        Serial.println("--> STATE NFC");
        LCD_NFC();
        first = false;
      }



      // State
      if (!motion) {
        nextState = WAIT;
      } else {
        RFIDfunc();
        if (current.UID_upp == 0 && current.UID_low == 0) { //Need timing? [ms]
          nextState = BT;
        } else {
          if (RecUID() == true) {
            nextState = WELCOME;
          } else {
            nextState = WRONG;
          }

        }
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case NFC_MASTER:
      if (first) {
        // Init of state
        // Runs only one time
        Serial.println("--> STATE NFC_MASTER");
        LCD_MASTER();
        first = false;
      }
      RFIDfunc();

      if (current.UID_upp == Master_upp && current.UID_low == Master_low) {
        nextState = NFC_NEW;
      }

      // State
      if (timeElapsed > 10000) { //Need timing? [ms]
        nextState = WRONG;
      }

      break;
    //-----------------------------------------------------------------------------------------------
    case NFC_NEW:
      if (first) {
        // Init of state
        // Runs only one time
        Serial.println("--> STATE NFC_NEW");
        LCD_NEW();
        first = false;
      }
      RFIDfunc();
      if (!(current.UID_upp == Master_upp && current.UID_low == Master_low)) {
        nextState = NEW_USER;
      }
      // State
      if (timeElapsed > 10000) { //Need timing? [ms]
        nextState = WRONG;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WELCOME:
      if (first) {
        // Init of state. Runs only one time
        Serial.println("--> STATE WELCOME");
        Serial.println("WELCOME");

        Serial.print("  UID: ");
        PrintUID(current.UID_upp, current.UID_low);
        Serial.println("");
        LCD_WELCOME_NAME(logEvent.Name);
        clearAll();
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
        LCD_WAIT();
        first = false;
      }
      if (motion) {
        nextState = NFC;
        PrintData();
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WRONG:
      if (first) {
        // Init of state
        // Runs only one time
        Serial.println("--> STATE WRONG");
        LCD_WRONG();
        clearAll();
        first = false;
      }
      // State
      if (timeElapsed > 3000) { //Need timing? [ms]
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case NEW_USER:

      // Init of state
      // Runs only one time
      Serial.println("--> STATE NEW_USER");
      LCD_NEW();

      AddCurrentToDB();
      nextState = WELCOME;


      break;
    //-----------------------------------------------------------------------------------------------
    default:
      Serial.println("!!! Unknown state !!!");
      nextState = WAIT;
      break;
  }
  delay(std_delay);
}

void clearAll() {
  BT_clearMAC();
  setZero();
  current.MAC_upp = 0;
  current.MAC_low = 0;
  current.UID_upp = 0;
  current.UID_low = 0;
  current.Name = "";
  logEvent.MAC_upp = 0;
  logEvent.MAC_low = 0;
  logEvent.UID_upp = 0;
  logEvent.UID_low = 0;
  logEvent.Name = "";
}

