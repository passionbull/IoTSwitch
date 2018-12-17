#include "LocalDB.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "WebFront.h"
#include "ServoController.h"

//Global variables

LocalDB db;
ServoController servoController;
WebFront webFront;


void setup() {
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("IoTSwitcher");
    
    //////////////////////////////////////////////////////////
    // After autoConnect, webFront server is initialized.
    webFront.setup(db, servoController);
}

void loop() {
    webFront.handle();
}
