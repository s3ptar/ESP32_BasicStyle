/***********************************************************************
*! \file:                   global_var.h
*  \projekt:                FT800_ESP
*  \created on:             25.07.2020
*  \author:                 R. Gräber
*  \version:                0
*  \history:                -
*  \brief                   Definitionsfile for global variables
***********************************************************************/
 
#ifndef _global_var_H_
#define _global_var_H_
 
/***********************************************************************
 * Includes
 **********************************************************************/
 #include "stdint.h"
 #include "Arduino.h"
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

extern char glb_IPv4_address[24];

extern IPAddress ip;

struct spiffs_flags_tag{
   uint8_t spiff_mounted : 1;
   uint8_t spiff_config_file_found : 1;
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


#endif //_global_var_h_