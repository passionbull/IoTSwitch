#include "WebFront.h"


WebFront::WebFront(){
}



WebFront::~WebFront(){
    delete mClientServer;

}

void WebFront::setup(LocalDB& db, ServoController& servo){
    mDB= db;
    mDB.spiffs_reading();
    mServoController = servo;
    int angle = atoi(mDB.mMiddle_angle);
    mServoController.moveToAngle(angle);

    mClientServer = new ESP8266WebServer(80);
    mSwitchText = "ON";
    mClientServer->on("/", std::bind(&WebFront::handleRoot, this));
    mClientServer->on("/init", std::bind(&WebFront::handleInit, this));
    mClientServer->on("/set", std::bind(&WebFront::handleSet, this));
    mClientServer->on("/get", std::bind(&WebFront::handleGet, this));
    mClientServer->begin();

    if (!MDNS.begin("SmartSwitcher")) {
        Serial.println("Error setting up MDNS responder!");
        while (1) {
            delay(1000);
        }
    }
    MDNS.addService("http", "tcp", 80);
    Serial.println("Setup is ok");
}

void WebFront::handle() {
    mClientServer->handleClient();
}

String WebFront::getPage() {
    String page = "<html><head><meta/>";
    page += "<title>Smart Switcher</title>";
    page += "<style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }</style>";
    page += "</head><body><h1>Switch ON/OFF</h1>";
    page += "<p><h3>Switch status : </h3>";
    page += mSwitchText;
    page +="</p>";
    page +="<form action='/' method='POST'>";
    page +="<p>Choose a Switch action: </p>";
    page +="<button name='Switch' type='submit' value='1'>TURN ON</button>";
    page +="                                           ";
    page +="<button name='Switch' type='submit' value='0'>TURN OFF</button>";
    page +="</form>";
    page += "</body></html>";
    return page;
}

void WebFront::printArgument(){
    String message = "";
    for (int i = 0; i < mClientServer->args(); i++) 
    {
        message += mClientServer->argName(i) + ":^^ ";     //Get the name of the parameter
        message += mClientServer->arg(i) + "**\n";              //Get the value of the parameter
    } 
    Serial.println(message);
}

void WebFront::handleInit(){
    mDB.spiffs_init();
    mClientServer->send ( 200, "text/html", getPage() );
}

void WebFront::handleSet(){
    printArgument();
    if ( mClientServer->hasArg("on_angle") )
    {
        mDB.spiffs_writing("on_angle", mClientServer->arg("on_angle"));
        strcpy(mDB.mOn_angle,mClientServer->arg("on_angle").c_str());
    }
    if ( mClientServer->hasArg("off_angle") )
    {
        mDB.spiffs_writing("off_angle", mClientServer->arg("off_angle"));
        strcpy(mDB.mOff_angle,mClientServer->arg("off_angle").c_str());
    }
    if ( mClientServer->hasArg("middle_angle") )
    {
        mDB.spiffs_writing("middle_angle", mClientServer->arg("middle_angle"));
        strcpy(mDB.mMiddle_angle,mClientServer->arg("middle_angle").c_str());
    }


    mClientServer->send ( 200, "text/html", getPage() );
}

void WebFront::handleGet(){
    printArgument();
    mDB.spiffs_reading();
    if ( mClientServer->hasArg("on_angle") )
    {
        Serial.println(mDB.mOn_angle);
    }
    if ( mClientServer->hasArg("off_angle") )
    {
        Serial.println(mDB.mOff_angle);
    }
    if ( mClientServer->hasArg("middle_angle") )
    {
        Serial.println(mDB.mMiddle_angle);
    }
        mClientServer->send ( 200, "text/html", getPage() );

}

void WebFront::handleRoot(){ 
    if ( mClientServer->hasArg("Switch") ) {
        handleSubmit();
    } else {
        mClientServer->send ( 200, "text/html", getPage() );
    }
}

void WebFront::handleSubmit() {
  // Actualise le GPIO / Update GPIO 
  String SwitchValue;
  SwitchValue = mClientServer->arg("Switch");
  Serial.print("Set Switch to:"); Serial.println(SwitchValue);
  if ( SwitchValue == "1" ) 
  {
    int angle = atoi(mDB.mOn_angle);
    mServoController.moveToAngle(angle, atoi(mDB.mMiddle_angle));
    mSwitchText = "On";
    mClientServer->send ( 200, "text/html", getPage() );
  } 
  else if ( SwitchValue == "0" ) 
  {
    int angle = atoi(mDB.mOff_angle);
    mServoController.moveToAngle(angle,atoi(mDB.mMiddle_angle));
    mSwitchText = "Off";
    mClientServer->send ( 200, "text/html", getPage() );
  } 
  else 
  {
    Serial.println("Error Switch Value");
  }
}