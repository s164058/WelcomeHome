// Std. setup:



// Bluetooth setup:



// RFID setup:



// WiFi setup:
#include <ESP8266WiFi.h>

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;


// Thingspeak setup:
#include "ThingSpeak.h"
#include "secrets.h"

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;


// Sensors setup:



// EDB setup:



// Output setup:



// LCD setup:




void setup() {
  // Std. setup:
  Serial.begin(9600); // Starts a serial connection


  // Bluetooth setup:



  // RFID setup:



  // WiFi setup:
  WiFi.mode(WIFI_STA);


  // Thingspeak setup:
  ThingSpeak.begin(client);  // Initialize ThingSpeak


  // Sensors setup:



  // EDB setup:



  // Output setup:



  // LCD setup:



}

void loop() {
  // put your main code here, to run repeatedly:

}
