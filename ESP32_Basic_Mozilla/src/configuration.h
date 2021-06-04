/***********************************************************************
*! \file:                   configuration.h
*  \projekt:                FT800_ESP
*  \created on:             25.07.2020
*  \author:                 R. Gräber
*  \version:                0
*  \history:                -
*  \brief                   Definitionsfile for global variables
***********************************************************************/
 
#ifndef _configuration_h_
#define _configuration_h_
 
/***********************************************************************
 * Includes
 **********************************************************************/
 #include "stdint.h"
 #include "error_codes.h"
 #include <ArduinoJson.h>
 #include <Arduino.h>
 #include "settings.h"
/***********************************************************************
 * Informations
 **********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
 
/***********************************************************************
 * Declarations
 **********************************************************************/
 #define glb_device_name_length  64

 enum wlan_status_tags{
    wlan_disable = 0,
    wlan_ap_modus,
    wlan_client_modus,
    wlan_default_ap_modus
};

/***********************************************************************
 * Global Variable
 **********************************************************************/

/***********************************************************************
 * Constant
 **********************************************************************/
 
/***********************************************************************
 * Macros
 **********************************************************************/
 
/***********************************************************************
 * Funtions 
 **********************************************************************/
error_type restore_configuration();
error_type connect_wlan();
uint8_t get_wlan_status();

#endif //_filehandling_h_