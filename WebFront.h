#ifndef WebFront_h
#define WebFront_h


#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

class WebFront{
    public:
        ~WebFront();
        WebFront();
        void setup();
        void handle();
        void handleRoot();
        void handleSubmit();
        void handleSet();
        void handleGet();

        String getPage();
        void printArgument();
        



    private:
      ESP8266WebServer* mClientServer;
      String  mSwitchText;
};
#endif


