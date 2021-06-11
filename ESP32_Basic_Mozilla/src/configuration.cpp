/***********************************************************************
*! \file:                   configuration.c
*  \projekt:                ESP32 Basic Style
*  \created on:             26.07.2020
*  \author:                 R. Gräber
*  \version:                0
*  \history:                0
*  \brief                   handles dictionary
***********************************************************************/
 
/***********************************************************************
* Includes
***********************************************************************/
#include "configuration.h"
#include "mozilla_iot.h"
/***********************************************************************
* Informations
***********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
//https://iot.mozilla.org/wot/#id-member
/***********************************************************************
* Declarations
***********************************************************************/

struct wlan_properties_tags{
   uint8_t wlan_enabled : 1;
   uint8_t wlan_ap_modus : 1;
   uint8_t wlan_OTA : 1;
   uint8_t wlan_status;
   char ssid[32];
   char passphrase[64];
   const char*  ptr_ssid = &ssid[0];
   const char*  ptr_passphrase = &passphrase[0];
};


struct spiffs_flags_tag{
   uint8_t spiff_mounted : 1;
   uint8_t spiff_config_file_found : 1;
};
/***********************************************************************
* local Variable
***********************************************************************/
bool mozilla_iot_enable = 0;
spiffs_flags_tag spiffs_flags;
IPAddress ip;
uint8_t glb_MAC_address[6];
char glb_device_name[glb_device_name_length];
wlan_properties_tags wlan_properties;
/***********************************************************************
* Global Variable
***********************************************************************/

/***********************************************************************
* Constant
***********************************************************************/

/***********************************************************************
*! \fn          void restore_config()
*  \brief       read configuration from SSPIFs, config.json files
*  \param       none
*  \exception   none
*  \return      error_type return error codes
***********************************************************************/
error_type restore_configuration(){

    //****************  localFunction Variables ***********************
    uint8_t return_code = er_no_error;
    DynamicJsonDocument ConfigJSON(512);

    //set dynamic (Chip propertys)
    WiFi.macAddress(glb_MAC_address);
    log_i("MAC %02x:%02x:%02x:%02x:%02x:%02x", glb_MAC_address[0],glb_MAC_address[1],glb_MAC_address[2],glb_MAC_address[3],glb_MAC_address[4],glb_MAC_address[5]);
    //set default name
    sprintf(glb_device_name, "%s%02x%02x%02x", DeviceName,glb_MAC_address[3],glb_MAC_address[4],glb_MAC_address[5]);

    //Try to open SPIFFS
    if (SPIFFS.begin()) {
        log_i("SPIFFS mounting successfully");
        if (SPIFFS.exists("/config.json")) {
            //file exists, reading and loading
            log_i("reading config file");
            File configFile = SPIFFS.open("/config.json");
            if (configFile) {
                log_i("opened config file");
                // Allocate a buffer to store contents of the file.
                deserializeJson(ConfigJSON, configFile);  
                strlcpy(wlan_properties.ssid,        // <- destination
                    ConfigJSON["wlan_data"]["ssid"], // <- source
                    sizeof(wlan_properties.ssid)     // <- destination's capacity
                );  
                strlcpy(wlan_properties.passphrase,        // <- destination
                    ConfigJSON["wlan_data"]["pass"], // <- source
                    sizeof(wlan_properties.passphrase)     // <- destination's capacity
                );
                wlan_properties.wlan_enabled = ConfigJSON["wlan_enable"];
                wlan_properties.wlan_OTA = ConfigJSON["wlan_ota"];
                wlan_properties.wlan_ap_modus = ConfigJSON["wlan_ap"];
                mozilla_iot_enable = ConfigJSON["MozillaIOT_Enablep"];
                configFile.close();
            }
        }else{
            return_code = er_no_config_file;
        }
    } else {
        log_e("failed to mount FS");
        return_code = er_spiffs_fault;
    }
    return return_code ;
    

}

/***********************************************************************
*! \fn          error_type
*  \brief       return requestet boolean parameter
*  \param       uint8_t parameter
*  \exception   none
*  \return      error_type return error codes
***********************************************************************/
error_type connect_wlan(){

    error_type return_code = er_wlan_disable;
    uint8_t wlan_connection_fail_cnt = wlan_reconnects;

    //WiFi.disconnect(true,true);
    if(wlan_properties.wlan_enabled){
        log_v("WLan On");
        //+++++++++++++ check modus 0 = WLan Client, 1 = AccessPoint Modus Modus ++++++
        if(wlan_properties.wlan_ap_modus){
            //AP Modus
            WiFi.mode(WIFI_MODE_AP);
            return_code = er_wlan_ap_mode;
            log_v("WLan AP Modus");
            WiFi.softAP(wlan_properties.ssid, wlan_properties.passphrase);
        }else{
            //Client Modus
            return_code = er_wlan_client_mode;
            WiFi.mode(WIFI_MODE_STA);
            log_v("WLan Station Modus");
            WiFi.setHostname(glb_device_name);
            log_v("DNS %s", glb_device_name);
            WiFi.begin(wlan_properties.ssid, wlan_properties.passphrase); 
            log_v("wait for conntect");
            vTaskDelay(2000); 
            while (!WiFi.isConnected()) {
                vTaskDelay(2000);
                log_v("Connection Trys %d", wlan_connection_fail_cnt);
                wlan_connection_fail_cnt--;
                if(!wlan_connection_fail_cnt){
                    //Switch to default WLAN AP Modus if no connect to SSID
                    return_code = er_wlan_default_ap;
                    WiFi.mode(WIFI_MODE_AP);
                    log_v("WLan Default AP Modus");
                    WiFi.softAP(glb_device_name, "1234567890");
                    //ESP.restart();
                }
            }
            log_v("conntecd!");
            ip = WiFi.localIP();

        }
        Serial.println(WiFi.localIP());
    }
    return return_code ;
}


/***********************************************************************
*! \fn          uint8_t get_wlan_status()
*  \brief       return wlan connection status
*  \param       none
*  \exception   none
*  \return      return status of wlan
***********************************************************************/
