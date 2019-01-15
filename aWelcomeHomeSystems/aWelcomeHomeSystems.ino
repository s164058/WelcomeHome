// Std. setup:



// Bluetooth setup:



// RFID setup:
/*
 *
 * Uses MIFARE RFID card using RFID-RC522 reader
 * Uses MFRC522 - Library
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 *
 *
 * NodeMCU
 * // SDA/SS -> D2(GPIO 4)
 * // SCK -> D5(GPIO 14)
 * // MOSI -> D7(GPIO 13)
 * // MISO/SCL -> D6(GPIO 12)
 * // IRQ -> NOT CONNECTED
 * // GND -> GND
 * // RST -> D1(GPIO 5)
 * // VCC -> 3.3V
*/

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

byte readCard[4];   // Stores scanned ID read from RFID Module
byte UID;

// WiFi setup:
/*#include <ESP8266WiFi.h>

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;


// Thingspeak setup:
#include "ThingSpeak.h"
#include "secrets.h"

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
*/

// Sensors setup:



// EDB setup:



// Output setup:



// LCD setup:




void setup() {
  // Std. setup:
  Serial.begin(9600); // Starts a serial connection


  // Bluetooth setup:



  // RFID setup:
  SPI.begin(); // Start SPI bus
  mfrc522.PCD_Init(); // Start RFID reader

  // WiFi setup:
  //WiFi.mode(WIFI_STA);


  // Thingspeak setup:
  //ThingSpeak.begin(client);  // Initialize ThingSpeak


  // Sensors setup:



  // EDB setup:



  // Output setup:



  // LCD setup:



}

void loop() {
  // put your main code here, to run repeatedly:
UID = rfidfunc(mfrc522, 1);
Serial.println(UID);
}
