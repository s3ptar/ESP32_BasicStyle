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
    return "";
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

    //############ local Variablen #################################

    uint8_t Wlan_Connection_Fails = 10;

    //############ Monting Filesystem #################################
    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println();
    Serial.println("Booting Device...");
    //get unique mac adddr
    WiFi.macAddress().toCharArray(glb_MAC_address,24);
    //build device name
    sprintf(glb_device_name, "%s_%s" ,PROJECT,glb_MAC_address);
    Serial.println(glb_MAC_address);
    Serial.println(glb_device_name);

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
    JSONConfigFile.close();

    //check if no SSID and Passphrase insert, switch to Stand AnloneStation Mode
    if ((strlen(ssid) > 0) & (strlen(password) > 0)) {

        //############ Try to connect to WLan #################################
        WiFi.mode(WIFI_STA); //Connectto your wifi
    
        while ((WiFi.status() != WL_CONNECTED && (Wlan_Connection_Fails > 0) )) {
            WiFi.begin(ssid, password);
            delay(1000);
            Serial.println("Connecting to WiFi..");
            Wlan_Connection_Fails--;
        }
        if(WiFi.status() == WL_CONNECTED){
            Serial.println("Connected to the WiFi network");
            WiFi.localIP().toString().toCharArray(glb_IPv4_address,24);
        }
    }

    //if no connection here, start AP Mode
    if (WiFi.status() != WL_CONNECTED) {

        WiFi.mode(WIFI_AP); //Connectto your wifi
        if(!WiFi.softAPConfig(IPAddress(192, 168, 5, 1), IPAddress(192, 168, 5, 1), IPAddress(255, 255, 255, 0))){
            Serial.println("AP Config Failed");
        }    
        if(WiFi.softAP(glb_device_name,"password")){
            Serial.println("");
            Serial.println("Network " + String(glb_device_name) + " running");
            Serial.print("AP IP address: ");
            WiFi.softAPIP().toString().toCharArray(glb_IPv4_address,24);
        } else {
            Serial.println("Starting AP failed.");
        }

    }
    //get current ip address
    Serial.println(glb_IPv4_address);

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/info.html", String(), false, processor);
    });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/favicon.png", "image/png");
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