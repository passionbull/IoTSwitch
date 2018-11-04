#ifndef ServoController_h
#define ServoController_h

#include <Servo.h>

class ServoController{

public:
    ServoController();
    ~ServoController();


    void setup();
    void enableMotor(bool v1);
    void moveToAngle(int angle);
    void moveToAngle(int goal_angle, int middle_angle);


    Servo mServo;
    int mAngle;
    bool mEnable;

};



#endif