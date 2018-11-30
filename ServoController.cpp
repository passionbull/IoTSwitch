    #include "ServoController.h"
    
    ServoController::ServoController()
    {
    }

    ServoController::~ServoController()
    {

    }

    void ServoController::setup(){
        mAngle = 0;
        mEnable = true;
        mServo.attach(14);
    }


    void ServoController::enableMotor(bool v1)
    {
        mEnable = v1;
        if(v1 == true)
            mServo.attach(14);
        else
            mServo.detach();
    }
    
    void ServoController::moveToAngle(int goal_angle, int middle_angle)
    {
        if(mEnable == false)
            return;
        moveToAngle(goal_angle);
        moveToAngle(middle_angle);
        enableMotor(false);
    }

       void ServoController::moveToAngle(int goal_angle)
    {
        if(mEnable == false)
            return;
        int size = 0;
        int added = 1;
        if(goal_angle - mAngle > 0)
            size = goal_angle - mAngle;
        else{
            size = mAngle - goal_angle;
            added *=-1;
        }

        for(int i =0; i<size; i++)
        {
            mAngle += added;
            mServo.write(mAngle);
            delay(5);
        }
        // mServo.write(goal_angle);
        Serial.println("Goal_angle");
        Serial.println(goal_angle);
        Serial.println("mAngle");
        Serial.println(mAngle);

    }