#include "Timer.h"

Timer::Timer()
{
    for(int i =0;i<3;i++)
        once[i] = 0;
}

Timer::~Timer()
{

}

void Timer::setup(LocalDB* db, ServoController* servo)
{
    mDB = db;
    mServoController = servo;
}


void Timer::setConfig(int gmt_timezone)
{
    configTime(gmt_timezone * 3600, 0, "pool.ntp.org", "time.nist.gov");
}

String Timer::getCurrentTime()
{
    time_t now = time(nullptr);
    struct tm * timeinfo;
    timeinfo = localtime(&now);
    String text = intToString(timeinfo->tm_hour)+intToString(timeinfo->tm_min)+String(timeinfo->tm_wday);
    // Serial.println(text);
    return text; // HHMMD
}


void Timer::checkDiff(String currentTime, int i)
{
    String alarmTime = "";
    switch(i)
    {
        case 0:
            alarmTime = mDB->mAlarm_time_0;
        break;
        case 1:
            alarmTime = mDB->mAlarm_time_1;
        break;
        case 2:
            alarmTime = mDB->mAlarm_time_2;
        break;
    }
    String onAngle = mDB->mOn_angle;
    String offAngle = mDB->mOff_angle;
    String midAngle = mDB->mMiddle_angle;

    // HHMMD
    int hourCurrent = currentTime.substring(0,2).toInt();
    int minuteCurrent = currentTime.substring(2,4).toInt();
    String dayCurrent = currentTime.substring(4,5); //N

    // HHMMDDDDDDDX
    int hourAlarm = alarmTime.substring(0,2).toInt();
    int minuteAlarm = alarmTime.substring(2,4).toInt();
    String dayAlarm = alarmTime.substring(4+dayCurrent.toInt(),5+dayCurrent.toInt());
    int turnONOFF = alarmTime.substring(11,12).toInt();



    Serial.println("********************");
    Serial.println(i);
    Serial.println(alarmTime);
    Serial.println(hourAlarm);
    Serial.println(minuteAlarm);
    Serial.println(dayAlarm);



    if( abs(hourAlarm - hourCurrent) > 0)
        once[i] = 0;

    if(dayAlarm == "1") // alarm set ON
    {
        int sumCurrent = hourCurrent*60 + minuteCurrent;
        int sumAlarm = hourAlarm*60 + minuteAlarm;
        int diff = sumCurrent - sumAlarm;
        if(diff > 0 && diff <3 && once[i] == 0)
        {
            Serial.print("Do alarm_");
            Serial.println(i);
            once[i] = 1;

            if(turnONOFF == 1){
                Serial.println("TURN ON");
                mServoController->enableMotor(true);  
                int angle = onAngle.toInt();
                mServoController->moveToAngle(angle, midAngle.toInt());
            }
            else{
                Serial.println("TURN OFF");
                mServoController->enableMotor(true);  
                int angle = offAngle.toInt();
                mServoController->moveToAngle(angle,midAngle.toInt());
            }
        }
    }
}

void Timer::checkDiff(String currentTime, String alarmTime, String onAngle, String offAngle, String midAngle, int i)
{
    // HHMMD
    int hourCurrent = currentTime.substring(0,2).toInt();
    int minuteCurrent = currentTime.substring(2,4).toInt();
    String dayCurrent = currentTime.substring(4,5); //N

    // HHMMDDDDDDDX
    int hourAlarm = alarmTime.substring(0,2).toInt();
    int minuteAlarm = alarmTime.substring(2,4).toInt();
    String dayAlarm = alarmTime.substring(4+dayCurrent.toInt(),5+dayCurrent.toInt());
    int turnONOFF = alarmTime.substring(11,12).toInt();



    Serial.println("********************");
    Serial.println(hourAlarm);
    Serial.println(minuteAlarm);
    Serial.println(dayAlarm);



    if( abs(hourAlarm - hourCurrent) > 0)
        once[i] = 0;

    if(dayAlarm == "1") // alarm set ON
    {
        int sumCurrent = hourCurrent*60 + minuteCurrent;
        int sumAlarm = hourAlarm*60 + minuteAlarm;
        int diff = sumCurrent - sumAlarm;
        if(diff > 0 && diff <3 && once[i] == 0)
        {
            Serial.print("Do alarm_");
            Serial.println(i);
            once[i] = 1;

            if(turnONOFF == 1){
                Serial.println("TURN ON");
                mServoController->enableMotor(true);  
                int angle = onAngle.toInt();
                mServoController->moveToAngle(angle, midAngle.toInt());
            }
            else{
                Serial.println("TURN OFF");
                mServoController->enableMotor(true);  
                int angle = offAngle.toInt();
                mServoController->moveToAngle(angle,midAngle.toInt());
            }
        }
    }
}

String Timer::intToString(int number){
    char buffer[3];
    snprintf(buffer,sizeof(buffer),"%02d",number);
    return buffer;
}