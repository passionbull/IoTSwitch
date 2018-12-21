#include "LocalDB.h"

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "WebFront.h"
#include "ServoController.h"
#include "Timer.h"
//Global variables

LocalDB db;
ServoController servoController;
WebFront webFront;
Timer alarmTimer;


void checkAlarm(){
    String currentTime = alarmTimer.getCurrentTime(); // HHMMD
    db.spiffs_reading();

    alarmTimer.checkDiff(currentTime,db.mAlarm_time_0, db.mOn_angle, db.mOff_angle, db.mMiddle_angle, 0);
    alarmTimer.checkDiff(currentTime,db.mAlarm_time_1, db.mOn_angle, db.mOff_angle, db.mMiddle_angle, 1);
    alarmTimer.checkDiff(currentTime,db.mAlarm_time_2, db.mOn_angle, db.mOff_angle, db.mMiddle_angle, 2);
}

void setup() {
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("IoT Switch");
    
    //////////////////////////////////////////////////////////
    // After autoConnect, webFront server is initialized.
    webFront.setup(db, servoController);
    alarmTimer.setup(db,servoController);

    alarmTimer.setConfig(9); //seoul
    alarmTimer._ticker.attach(1.0* 60, checkAlarm);
}

void loop() {
    webFront.handle();
}
