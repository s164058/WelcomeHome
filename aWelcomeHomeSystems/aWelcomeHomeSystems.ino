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

// Bluetooth setup_________________________________________________________________________________
SoftwareSerial BTserial(10, 11); // (SERIAL_RX, SERIAL_TX) CONNECT TO (BT_TX, BT_RX)

// RFID setup______________________________________________________________________________________
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance




// WiFi setup______________________________________________________________________________________


// Sensors setup___________________________________________________________________________________



// EDB setup_______________________________________________________________________________________



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



  // Output setup_____________________________________________________________________________________:



  // LCD setup_____________________________________________________________________________________:



}

char BTmac[] = "000000000000"; //4E4424073BB7 //6CB4F55C9646 //5F7F9129578C
unsigned int UID = {0,0,0,0};                // Unsigned integer array, for saving UID to an array(prevents overflow)

void loop() {
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
