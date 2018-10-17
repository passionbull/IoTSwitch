#include "LocalDB.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "WebFront.h"

//Global variables

LocalDB db;
WebFront webFront(db);


void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("SmartSwitcher");
    //////////////////////////////////////////////////////////
    // After autoConnect, setup again..
    webFront.setup();
}

void loop() {
    webFront.handle();
}
