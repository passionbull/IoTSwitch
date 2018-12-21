#ifndef LocalDB_h
#define LocalDB_h

#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson


class LocalDB{

public:
    LocalDB();
    ~LocalDB();
    void spiffs_reading();
    void spiffs_init();
    void spiffs_writing(String id, String val);

    char mMiddle_angle[4];
    char mOn_angle[4];
    char mOff_angle[4];
    char mAlarm_time_0[13]; // HHMMDDDDDDDX
    char mAlarm_time_1[13]; // HHMMDDDDDDDX
    char mAlarm_time_2[13]; // HHMMDDDDDDDX

};

#endif