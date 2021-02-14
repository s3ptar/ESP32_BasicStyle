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
    uint8_t wlan_connection_fail_cnt = 10;

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
    
#endif


    //###################################################################################
    //try to mount file system
    
    WiFi.macAddress(glb_MAC_address);
    log_i("MAC %02x:%02x:%02x:%02x:%02x:%02x", glb_MAC_address[0],glb_MAC_address[1],glb_MAC_address[2],glb_MAC_address[3],glb_MAC_address[4],glb_MAC_address[5]);
    //set default name
    sprintf(glb_device_name, "%s%02x%02x%02x", DeviceName,glb_MAC_address[3],glb_MAC_address[4],glb_MAC_address[5]);
    //###################################################################################
    //start wifi
    WiFi.disconnect(true,true);
    if (load_config()){
        //no config file, start default ap mode
        log_v("wlan default ap");
        WiFi.softAP(glb_device_name);
    }else{
        //config found, ceck if wlan sould be enable
        if(get_bool_parameter(wlan_enable_parameter)){
            log_v("WLan On");
            //check modus 0 = WLan Client, 1 = AccessPoint Modus Modus
            if(get_bool_parameter(wlan_ap_modus_parameter)){
                //AP Modus
                WiFi.softAP(get_char_parameter(wlan_ssid_parameter), get_char_parameter(wlan_passphrase_parameter));
            }else{
                //Client Modus
                log_v("Start Station");
                WiFi.setHostname(glb_device_name);
                //log_v("DNS %s", glb_device_name);
                WiFi.begin(get_char_parameter(wlan_ssid_parameter), get_char_parameter(wlan_passphrase_parameter));      
                while (!WiFi.isConnected()) {
                    vTaskDelay(2000);
                    log_v("wait for conntect");
                    wlan_connection_fail_cnt--;
                    if(!wlan_connection_fail_cnt)
                        ESP.restart();
                }
                log_v("conntecd!");
                ip = WiFi.localIP();
                #ifdef _Heltec_Board_
                    Heltec.display->clear();
                    sprintf(msgBuffer, "IP %u.%u.%u.%u", ip[0],ip[1],ip[2],ip[3]);
                    Heltec.display->drawString(0, 0, msgBuffer);
                    sprintf(msgBuffer, "DNS %s", glb_device_name);
                    Heltec.display->drawString(0, 10, msgBuffer);
                    // write the buffer to the display
                    Heltec.display->display();
                #endif

            }
        }
        
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

