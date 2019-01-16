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
SoftwareSerial BTserial(10, 11); // (SERIAL_RX, SERIAL_TX) CONNECT TO (BT_TX, BT_RX)

// RFID setup_____________________________________________________________________________________:
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance




// WiFi setup_____________________________________________________________________________________:


// Sensors setup_____________________________________________________________________________________:



// EDB setup_____________________________________________________________________________________:



// Output setup_____________________________________________________________________________________:



// LCD setup_____________________________________________________________________________________:




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



  // Output setup_____________________________________________________________________________________:



  // LCD setup_____________________________________________________________________________________:



}

char BTmac[] = "00xxx0000000"; //4E4424073BB7 //6CB4F55C9646 //5F7F9129578C
unsigned int UID[4];                // Unsigned integer array, for saving UID to an array(prevents overflow)

void loop() {
<<<<<<< HEAD
  // put your main code here, to run repeatedly:
=======
  
>>>>>>> 12287848d4ed3fe731cb524895560cf731d720af
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
