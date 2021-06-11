#include <Arduino.h>
#include "settings.h"
#include "configuration.h"
#include "stdint.h"
#include "heltec.h"
#include "mozilla_iot.h"
/***********************************************************************
* Informations
***********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
/***********************************************************************
* Declarations
***********************************************************************/
const int lampPin = 25; // manually configure LED pin
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");
HardwareSerial SerialCom1(1);
/***********************************************************************
* Global Variable
***********************************************************************/
//Enter your SSID and PASSWORD
const char* ssid = "";
const char* password = "";
/***********************************************************************
* Constant
***********************************************************************/
time_t now;
char strftime_buf[64];
struct tm timeinfo;
char msgBuffer[1024];
/***********************************************************************
* Local Funtions
***********************************************************************/

// Replaces placeholder with LED state value
String processor(const String& var){
    //Serial.println(var); 
    return "";
}

/***********************************************************************
*! \fn          void execption_handling()
*  \brief       handle the execption
*  \param       uint32_t error_code - error code
*  \exception   none
*  \return      none
***********************************************************************/
void execption_handling(){

    while(1){
        vTaskDelay(1000);
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

    //start debug on serial
    Serial.begin(115200);
    //enable Debugging
    Serial.setDebugOutput(true);

    //build flags in ini - file
    /*esp_log_level_set("*", ESP_LOG_VERBOSE);
    ESP_LOGD("EXAMPLE", "This doesn't show");

    ESP_LOGE - error (lowest)
    ESP_LOGW - warning
    ESP_LOGI - info
    ESP_LOGD - debug
    ESP_LOGV - verbose (highest)
    */
    log_i("booting");

    //AddLogEntry(id_intern_serial, id_empty_source ,id_open_serial , id_no_error );
#ifdef _Heltec_Board_
    log_d("OLED start");
    //pinMode(25, OUTPUT);
    //digitalWrite(25,HIGH);
    //Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false/*Serial Enable*/);  
#endif
    //###################################################################################
    //start Configuration Modus
    restore_configuration();
    //###################################################################################
    //connect wlan
    vTaskDelay(2000); 
    connect_wlan();
    vTaskDelay(2000);    
    //###################################################################################
    //Setup IOT
    config_mozilla_iot();

    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/plain", "Hello World");
    });
 
    server.begin();                  //Start server

}



/***********************************************************************
*! \fn          void loop()
*  \brief       construct host command and send to graphics controller
*  \param       uint32_t HostCommand
*  \exception   none
*  \return      none
***********************************************************************/
void loop() {

    //time(&now);
    // Set timezone to China Standard Time
    //localtime_r(&now, &timeinfo);
    //strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    // put your main code here, to run repeatedly:
    //Serial.println(now);
    update_iot();
    vTaskDelay(2000); 


}

