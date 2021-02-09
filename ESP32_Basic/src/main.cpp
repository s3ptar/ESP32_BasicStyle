#include <Arduino.h>
#include "settings.h"
#include "global_var.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include "global_var.h"
#include "stdint.h"
#include "FileHandling.h"
#include "heltec.h"
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
HardwareSerial SerialCom1(1);
/***********************************************************************
* Global Variable
***********************************************************************/
//Enter your SSID and PASSWORD
const char* ssid = "";
const char* password = "";
spiffs_flags_tag spiffs_flags;

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
void hwdrv_serial();

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
    //uint8_t Wlan_Connection_Fails = 10;

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
    ESP_LOGV - verbose (highest
    */
    log_i("booting");
    //AddLogEntry(id_intern_serial, id_empty_source ,id_open_serial , id_no_error );
#ifdef _Heltec_Board_
    log_v("OLED start");
    pinMode(25, OUTPUT);
    digitalWrite(25,HIGH);
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false/*Serial Enable*/);
    Heltec.display->clear();
    Heltec.display->drawString(0, 0, "Hello World!");
    // write the buffer to the display
    Heltec.display->display();
#endif


    //###################################################################################
    //try to mount file system
    spiffs_flags.spiff_config_file_found = load_config();
    
    WiFi.macAddress(glb_MAC_address);
    log_i("MAC %02x:%02x:%02x:%02x:%02x:%02x", glb_MAC_address[0],glb_MAC_address[1],glb_MAC_address[2],glb_MAC_address[3],glb_MAC_address[4],glb_MAC_address[5]);
    //set default name
    sprintf(glb_device_name, "%s_%02x%02x%02x", DeviceName,glb_MAC_address[3],glb_MAC_address[4],glb_MAC_address[5]);
    log_d("SSID %s", glb_device_name);
    //start wifi
    if (spiffs_flags.spiff_config_file_found){
        //no config file, start default ap mode
        //try to read default ap name
        WiFi.softAP(glb_device_name);
    }else{
        WiFi.softAP(glb_device_name);
    }

    

    //try to read ssid and password from file and Modus
    

    //###################################################################################

    //Declatation
    //set time zone
    Serial.println("Set Time Zone");
    setenv("TZ", "UTC", 1);
    tzset();

    
    


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
    delay(10000);


}

