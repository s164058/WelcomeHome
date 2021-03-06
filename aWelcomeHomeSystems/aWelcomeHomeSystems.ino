// Includes_____________________________________________________________________________________:
#include <SPI.h>
#include <MFRC522.h>
#include <EDB.h>                // Extended Database Library
#include <EEPROM.h>             // Use the Internal Arduino EEPROM as storage
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  //I2C communication LCD display
#include <DHT.h>                //Sensor libary for DHT-22

// Definitions_____________________________________________________________________________________:
// State definitions
#define BT 101
#define NFC 102
#define NFC_MASTER 103
#define NFC_NEW 104
#define WELCOME 105
#define WAIT 106
#define WRONG 107
#define NEW_USER 108
#define WELCOME_NEW_USER 109
// PIN definitions
#define ResetTable_PIN 30
#define MotionSensor_PIN 4
#define RST_PIN         49           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above
#define DHT_PIN 26
#define Alarm_PIN 11
#define AlarmInv_PIN 12
#define Red_PIN 8
#define Green_PIN 9
#define Blue_PIN 10

// Other definitions
#define baud 115200       //Arduino communicationspeed
#define TABLE_SIZE 512 // Arduino 168 or greater, can be setted higher for MEGA
#define DHTTYPE DHT22



//variables
int currentState;
int nextState;
unsigned long startTime;
unsigned long timeElapsed;
static int std_delay = 100; // delay per state in ms
bool first;

// Bluetooth setup_________________________________________________________________________________

// RFID setup______________________________________________________________________________________
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

static uint32_t Master_upp = 145254;
static uint32_t Master_low = 23197;

// WiFi setup______________________________________________________________________________________


// Sensors setup___________________________________________________________________________________
DHT dht(DHT_PIN, DHTTYPE);
float hum;
float temp;
boolean motion;


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
  char firstName[8];
  char lastName[8];

}
logEvent, current;



// Output setup____________________________________________________________________________________



// LCD setup_______________________________________________________________________________________
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};

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

  pinMode(Red_PIN, OUTPUT);
  pinMode(Green_PIN, OUTPUT);
  pinMode(Blue_PIN, OUTPUT);
  pinMode(Alarm_PIN, OUTPUT);
  pinMode(AlarmInv_PIN, OUTPUT);


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
  pinMode(MotionSensor_PIN, INPUT_PULLUP);
  dht.begin();

  // EDB setup_____________________________________________________________________________________:
  pinMode(ResetTable_PIN, INPUT_PULLUP);


  // Output setup_____________________________________________________________________________________:



  // LCD setup_____________________________________________________________________________________:
  LCD_setup();

  if (digitalRead(ResetTable_PIN) == LOW) {
    db.create(0, TABLE_SIZE, sizeof(logEvent)); // Truncate the current databased
    Serial.println("Table reset done!");

    LED(1, 0, 0, 1); // Indicate when a table is loaded, red LED(RGB) and alarm LED
    delay(1000);
    LED(0, 0, 0, 0);  // Turn LEDs off

  } else {
    db.open(0);
    Serial.println("Table load done!");
    PrintData();

    LED(1, 0, 0, 0);  // Indicate when a table is loaded, red LED(RGB)
    delay(1000);
    LED(0, 0, 0, 0);  // Turn LEDs off
  }




}


void loop() {
  //Sensor update
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  motion = digitalRead(MotionSensor_PIN);

  //Has state change since last loop?
  if (nextState != currentState) {
    startTime = millis();
    currentState = nextState;
    first = true;
  }
  timeElapsed = millis() - startTime;

  // State Logic (What should we do next?)
  switch (currentState) {
    /*-----------------------------------------------------------------------------------------------
      case EXAMPLE:
      if (first) {
        Initialization of state.
        Runs only one time
        first = false;
      }
      State code.
      What should happen in this state?
      This code is run as often as possible.
      Dont include delays here.
      if (timeElapsed > T) {
        Go to next state after T ms.
        This functionality can be used for timeouts
        nextState = NEXT_EXAMPLE;
      }
      break;
      -----------------------------------------------------------------------------------------------
    */
    case BT:
      Serial.println("--> STATE BT");
      BT_last();
      LCD_BT();
      LED(0, 0, 1, 0); // Blue LED(RGB) for bluetooth state

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
      LED(0, 1, 0, 0); // Green LED(RGB) for NFC state
      if (first) {
        Serial.println("--> STATE NFC");
        LCD_NFC();
        first = false;
      }
      if (!motion) {
        nextState = WAIT;
      } else {
        lcd.backlight(); // Turn on backlight, when waking from wait
        lcd.display();  // Turn on display, when waking from wait
        RFIDfunc();
        if (current.UID_upp == 0 && current.UID_low == 0) {
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
      LED(0, 0, 0, 0); // Turn LEDs off
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
      LED(0, 0, 0, 0); // Turn LEDs off
      if (first) {
        Serial.println("--> STATE NFC_NEW");
        LCD_NEW();
        first = false;
      }
      RFIDfunc();
      LCD_NEW();
      if (!(current.UID_upp == Master_upp && current.UID_low == Master_low)) {

        if (RecUID() == false) {
          nextState = NEW_USER;
        }
        else {
          LCD_NFC_NOT_UNIQUE();
          current.UID_upp = Master_upp;
          current.UID_low = Master_low;

        }
      }
      // State
      if (timeElapsed > 10000) {
        nextState = WRONG;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WELCOME:
      LED(0, 1, 1, 0); // Turn blue and green LED(RGB) on
      if (first) {
        Serial.println("--> STATE WELCOME");
        //PrintUID(current.UID_upp, current.UID_low);
        Serial.println("");
        first = false;
      }
      if (timeElapsed < 2500) {
        LCD_WELCOME_NAME();
      }
      else {
        LCD_WELCOME_DATA();
      }

      // State
      if (timeElapsed > 5000) {
        nextState = WAIT;
        clearAll();
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WAIT:
      LED(0, 0, 0, 0);  // Turn LEDs off
      if (first) {
        Serial.println("--> STATE WAIT");
        LCD_WAIT();
        first = false;
      }
      if (motion) {
        nextState = NFC;
      }
      else{
        lcd.noBacklight(); // Turn off backlight
        lcd.noDisplay();   // Turn off backlight
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case WRONG:
      LED(0, 0, 0, 1);  // Set Alarm LED high
      if (first) {
        Serial.println("--> STATE WRONG");
        LCD_WRONG();
        clearAll();
        first = false;
      }
      // State
      if (timeElapsed > 3000) {
        nextState = WAIT;
      }
      break;
    //-----------------------------------------------------------------------------------------------
    case NEW_USER:
      LED(0, 0, 0, 0);  // Turn LEDs off
      Serial.println("--> STATE NEW_USER");
      LCD_NEW();

      AddCurrentToDB();
      nextState = WELCOME_NEW_USER;
      break;

    //-----------------------------------------------------------------------------------------------
    case WELCOME_NEW_USER:
      LED(0, 0, 0, 0);  // Turn LEDs off
      if (first) {
        Serial.println("--> STATE WELCOME_NEW_USER");
        LCD_WELCOME_NEW_CREATED();
        first = false;
      }
      if (timeElapsed > 2000) {
        LCD_WELCOME_NEW_NAME();
      }
      if (timeElapsed > 5000) {
        PrintData();
        clearAll();
        nextState = WAIT;
      }
      break;


    //-----------------------------------------------------------------------------------------------
    default:
      LED(0, 0, 0, 0);  // Turn LEDs off
      Serial.println("!!! Unknown state !!!");
      nextState = WAIT;
      break;
  }
  delay(std_delay);
}
