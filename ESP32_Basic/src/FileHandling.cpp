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
wlan_properties_tags wlan_properties;
/***********************************************************************
* Global Variable
***********************************************************************/
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


    
}

/***********************************************************************
*! \fn          bool get_bool_parameter(uint8_t parameter)
*  \brief       return requestet boolean parameter
*  \param       uint8_t parameter
*  \exception   none
*  \return      boolean
***********************************************************************/
bool get_bool_parameter(uint8_t parameter){
    switch(parameter){
        case wlan_ap_modus_parameter : {
            return wlan_properties.wlan_ap_modus;
            break;
        } 
        case wlan_enable_parameter : {
            return wlan_properties.wlan_enabled;
            break;
        } 
        default: {
            return 0;
        }
    }
}

/***********************************************************************
*! \fn          char* get_bool_parameter(uint8_t parameter)
*  \brief       return requestet boolean parameter
*  \param       uint8_t parameter
*  \exception   none
*  \return      char pointer
***********************************************************************/
const char* get_char_parameter(uint8_t parameter){
    switch(parameter){
        case wlan_ssid_parameter : {
            return wlan_properties.ptr_ssid;
            break;
        } 
        case wlan_passphrase_parameter : {
            return wlan_properties.ptr_passphrase;
            break;
        } 
        default: {
            return 0;
        }
    }
}