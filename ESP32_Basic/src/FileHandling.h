/***********************************************************************
*! \file:                   global_var.h
*  \projekt:                FT800_ESP
*  \created on:             25.07.2020
*  \author:                 R. Gräber
*  \version:                0
*  \history:                -
*  \brief                   Definitionsfile for global variables
***********************************************************************/
 
#ifndef _filehandling_h_
#define _filehandling_h_
 
/***********************************************************************
 * Includes
 **********************************************************************/
 #include "stdint.h"
 #include "SPIFFS.h"
 #include "global_var.h"
 #include <ArduinoJson.h>
/***********************************************************************
 * Informations
 **********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
 
/***********************************************************************
 * Declarations
 **********************************************************************/
 
/***********************************************************************
 * Global Variable
 **********************************************************************/
enum file_handling_error_codes{
    no_error = 0,
    spiffs_fault = 1,
    no_config_file = 2
};

enum bool_struct_parameter{
    wlan_ap_modus_parameter = 0,
    wlan_enable_parameter
};

enum char_struct_parameter{
    wlan_ssid_parameter = 0,
    wlan_passphrase_parameter
};
/***********************************************************************
 * Constant
 **********************************************************************/
 
/***********************************************************************
 * Macros
 **********************************************************************/
 
/***********************************************************************
 * Funtions definded in main.c
 **********************************************************************/
uint8_t load_config();
bool get_bool_parameter(uint8_t parameter);
const char* get_char_parameter(uint8_t parameter);

#endif //_filehandling_h_