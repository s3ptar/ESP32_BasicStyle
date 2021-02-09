/***********************************************************************
*! \file:                   global_var.c
*  \projekt:                global_var
*  \created on:             26.07.2020
*  \author:                 R. Gräber
*  \version:                0
*  \history:                0
*  \brief                   handles dictionary
***********************************************************************/
 
/***********************************************************************
* Includes
***********************************************************************/
#include "FileHandling.h"
/***********************************************************************
* Informations
***********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
/***********************************************************************
* Declarations
***********************************************************************/
 
/***********************************************************************
* Global Variable
***********************************************************************/
extern spiffs_flags_tag spiffs_flags;
wlan_properties_tags wlan_properties;
/***********************************************************************
* Constant
***********************************************************************/

/***********************************************************************
*! \fn          uint8_t check_file(String filename)
*  \brief       check if the file exist
*               https://gist.github.com/anoochit/01cafc8c040cea8845934404da8ee014
*  \param       String filename - full path
*  \exception   none
*  \return      return codes, 0 is okay
***********************************************************************/
uint8_t load_config(){

    uint8_t return_code = no_error;
    DynamicJsonDocument ConfigJSON(512);

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
                wlan_properties.ssid = ConfigJSON["wlan_data"]["ssid"];
                wlan_properties.passwd = ConfigJSON["wlan_data"]["pass"];
                wlan_properties.wlan_enabled = ConfigJSON["wlan_enable"];
                wlan_properties.wlan_ap_modus = ConfigJSON["wlan_ap"];
                configFile.close();
            }
        }
    } else {
        Serial.println("failed to mount FS");
    }
    return return_code ;
}


