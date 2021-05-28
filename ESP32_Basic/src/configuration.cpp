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
#include "WiFi.h"
#include "settings.h"
#include "error_codes.h"
/***********************************************************************
* Informations
***********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
/***********************************************************************
* Declarations
***********************************************************************/
struct wlan_properties_tags{
   uint8_t wlan_enabled : 1;
   uint8_t wlan_ap_modus : 1;
   char ssid[32];
   char passphrase[64];
   const char*  ptr_ssid = &ssid[0];
   const char*  ptr_passphrase = &passphrase[0];
};
/***********************************************************************
* local Variable
***********************************************************************/

/***********************************************************************
* Global Variable
***********************************************************************/

uint8_t glb_MAC_address[6];
char glb_device_name[glb_device_name_length];

/***********************************************************************
* Constant
***********************************************************************/

/***********************************************************************
*! \fn          void restore_config()
*  \brief       read configuration from SSPIFs, config.json
*  \param       none
*  \exception   none
*  \return      none
***********************************************************************/
void restore_configuration(){

    //Function Variables
    uint8_t return_code = no_error;
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
                wlan_properties.wlan_ap_modus = ConfigJSON["wlan_ap"];
                configFile.close();
            }
        }else{
            return_code = no_config_file;
        }
    } else {
        Serial.println("failed to mount FS");
        return_code = spiffs_fault;
    }
    return return_code ;
    

}

/***********************************************************************
*! \fn          bool get_bool_parameter(uint8_t parameter)
*  \brief       return requestet boolean parameter
*  \param       uint8_t parameter
*  \exception   none
*  \return      boolean
***********************************************************************/


/***********************************************************************
*! \fn          char* get_bool_parameter(uint8_t parameter)
*  \brief       return requestet boolean parameter
*  \param       uint8_t parameter
*  \exception   none
*  \return      char pointer
***********************************************************************/
