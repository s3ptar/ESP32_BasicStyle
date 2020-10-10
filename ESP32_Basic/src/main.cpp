#include <Arduino.h>
#include "settings.h"
#include "global_var.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <error_codes.h>
#include <ArduinoJson.h>

/***********************************************************************
* Informations
***********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
/***********************************************************************
* Declarations
***********************************************************************/
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");
/***********************************************************************
* Global Variable
***********************************************************************/
//Enter your SSID and PASSWORD
const char* ssid = "";
const char* password = "";
/***********************************************************************
* Constant
***********************************************************************/
 
/***********************************************************************
* Local Funtions
***********************************************************************/


// Replaces placeholder with LED state value
String processor(const String& var){
    //Serial.println(var); 
}

/***********************************************************************
*! \fn          void execption_handling(uint32_t error_code)
*  \brief       handle the execption
*  \param       uint32_t error_code - error code
*  \exception   none
*  \return      none
***********************************************************************/
void execption_handling(uint32_t error_code){

    while(1){

    }
}

/***********************************************************************
*! \fn          void setup()
*  \brief       Arduino Setup - Routine
*  \param       none
*  \exception   none
*  \return      none
***********************************************************************/
void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println();
    Serial.println("Booting Device...");
    //ead unique mac adddr
    WiFi.macAddress().toCharArray(glb_MAC_address,24);
    //build device name
    Serial.println(glb_MAC_address);

    //############ Monting Filesystem #################################

    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        execption_handling(Error_Mounting_SPIFFS);
        return;
    }
    //list files in root
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while(file){
        Serial.print("FILE: ");
        Serial.println(file.name());
 
        file = root.openNextFile();
    }

    //############ Get Configuration #################################
    File JSONConfigFile = SPIFFS.open("/config.json", "r");
    if (!JSONConfigFile) {
        Serial.println("Failed to open Configuration File for reading");
        return;
    }
    DynamicJsonDocument ConfigDoc(256);
    auto error = deserializeJson(ConfigDoc, JSONConfigFile);
    if (error) {
        Serial.print(F("deserializeJson() failed with code "));
        Serial.println(error.c_str());
        return;
    } else {
        //JsonArray array = doc.to<JsonArray>();
        // array.remove(0);
        //serializeJson(array, Serial);
    }
    JsonObject ConfigObj = ConfigDoc.as<JsonObject>(); 
    //JsonObject obj = doc[0];
    ssid = ConfigObj["wlan"]["ssid"];
    password = ConfigObj["wlan"]["pass"];

    //############ Try WLan #################################
    WiFi.mode(WIFI_STA); //Connectto your wifi
    
    while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    JSONConfigFile.close();

    //get current ip address
    WiFi.localIP().toString().toCharArray(glb_IPv4_address,24);
    Serial.println(glb_IPv4_address);

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/info.html", String(), false, processor);
    });

    // Start server
    server.begin();

}

/***********************************************************************
*! \fn          void loop(){
*  \brief       construct host command and send to graphics controller
*  \param       uint32_t HostCommand
*  \exception   none
*  \return      none
***********************************************************************/
void loop() {
    // put your main code here, to run repeatedly:
    delay(1);

}