#ifndef Timer_h
#define Timer_h


#include "LocalDB.h"
#include "ServoController.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Ticker.h>
#include <time.h>


class Timer{
    public:
        Timer();
        ~Timer();
        Ticker _ticker;
        void setup(LocalDB& db, ServoController& servoController);
        void setConfig(int gmt_timezone);
        String getCurrentTime();

        void checkDiff(String currentTime, String alarmTime, String onAngle, String offAngle, String midAngle, int i);
        int once[3];
        LocalDB mDB;
        ServoController mServoController;

    private:
        String intToString(int number);
};
#endif