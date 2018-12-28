#include "LocalDB.h" //this needs to be first, or it all crashes and burns... because of FS.h

#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "WebFront.h"
#include "ServoController.h"
#include "Timer.h"
//Global variables

LocalDB* db;
ServoController* servoController;
WebFront webFront;
Timer alarmTimer;


void checkAlarm(){
    String currentTime = alarmTimer.getCurrentTime(); // HHMMD
    db->spiffs_reading();
    for(int i =0; i<3; i++)
        alarmTimer.checkDiff(currentTime,i);
}

void setup() {

    // connect automoatically wifi
    Serial.begin(115200);
    WiFi.hostname("IoTSwitch");
    WiFiManager wifiManager;
    wifiManager.autoConnect("IoT Switch");

    // init db and servoController
    db = new LocalDB();
    db->spiffs_reading();
    servoController = new ServoController();
    servoController->setup();
    
    
    // After autoConnect, webFront server is initialized.
    // call by reference, connect db and controller to webFront, alarmTimer
    webFront.setup(db, servoController);
    alarmTimer.setup(db, servoController);

    alarmTimer.setConfig(9); //seoul
    alarmTimer._ticker.attach(1.0* 60, checkAlarm);
	

    // TODO : added mac address to setting page, or give mac address to phone and find esp8266 using mac address on phone.
    Serial.print("Host Name: ");
    Serial.println(WiFi.hostname());

    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
}

void loop() {
    webFront.handle();
}
