#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include "WebFront.h"

WebFront webFront;

//String on_angle;
//String off_angle;
//String alarm_time;

char on_angle[4];
char off_angle[4];
char alarm_time[6];


void spiff_reading(){

    if (SPIFFS.begin()) 
    {
        Serial.println("reading file system");
        if (SPIFFS.exists("/config.json")) 
        {
            //file exists, reading and loading
            Serial.println("reading config file");
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile) {
                Serial.println("opened config file");
                size_t size = configFile.size();
                // Allocate a buffer to store contents of the file.
                std::unique_ptr<char[]> buf(new char[size]);

                configFile.readBytes(buf.get(), size);
                DynamicJsonBuffer jsonBuffer;
                JsonObject& json = jsonBuffer.parseObject(buf.get());
                json.printTo(Serial);
                
                if (json.success()) 
                {
                    Serial.println("\nparsed json");
                    strcpy(on_angle, json["on_angle"]);
                    strcpy(off_angle, json["off_angle"]);
                    strcpy(alarm_time, json["alarm_time"]);
                } 
                else {
                    Serial.println("failed to load json config");
                }
                configFile.close();
            }
        }

    }
}

void spiff_writing() 
{
    if (SPIFFS.begin()) 
    {
        
        StaticJsonBuffer<100> jsonBuffer;
        JsonObject& json = jsonBuffer.createObject();
        json["on_angle"] = "120";
        json["off_angle"] = "30";
        json["alarm_time"] = "o1234";

        File configFile = SPIFFS.open("/config.json", "w");
        if (!configFile) {
            Serial.println("failed to open config file for writing");
        }
        Serial.println("writing file system");
        json.printTo(Serial);
        json.printTo(configFile);
        configFile.close();

    }

}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    WiFiManager wifiManager;
    wifiManager.autoConnect("SmartSwitch");
    //////////////////////////////////////////////////////////
    // After autoConnect, setup again..
    webFront.setup();
    //spiff_writing();
    spiff_reading();

}

void loop() {
    webFront.handle();
}
