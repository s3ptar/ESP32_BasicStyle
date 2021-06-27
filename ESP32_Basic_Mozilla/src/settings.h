/***********************************************************************
*! \file:                   settings.h
*  \projekt:                globale Variablen
*  \created on:             07.03.2019
*  \author:                 R. Gräber
*  \version:                0
*  \history:                -
*  \brief                   abgeleitet von tasmota sonoff
***********************************************************************/
 
#ifndef _settings_H_
#define _settings_H_
 
/***********************************************************************
* Includes
**********************************************************************/
#include "stdio.h"
#include "stdint.h"
#include "config.h"
#include <ESPAsyncWebServer.h>
#ifdef _mozilla_iot_enable_
    #define ARDUINOJSON_USE_LONG_LONG 1
    #include <Thing.h>
    #include <WebThingAdapter.h>
#endif
/***********************************************************************
* Informations
**********************************************************************/
//https://download.bastelgarage.ch/Datasheet/ESP8266_Heltec_Wifi_Kit_Schema.png
 
/***********************************************************************
* Declarations
**********************************************************************/



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


#define config_file_full_path "/config.json"
#ifndef DeviceClassID
    #define DeviceClassID "ESP"
#else
    #if DeviceClassID == HELTEC
        #define DeviceName "Heltec"
        #define _Heltec_Board_ 
    #else
        #define DeviceName "ESP"
        #define _ESP_Board_ 
    #endif
#endif

#define wlan_reconnects 10

#define _mozilla_iot_enable_

#endif /* _settings_H_ */
