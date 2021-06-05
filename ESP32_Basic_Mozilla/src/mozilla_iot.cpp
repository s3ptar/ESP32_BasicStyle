/***********************************************************************
*! \file:                   mozilla_iot.c
*  \projekt:                ESP32 Basic Style
*  \created on:             04.06.2021
*  \author:                 R. Gräber
*  \version:                0
*  \history:                0
*  \brief                   handles IOT Function
***********************************************************************/
 
/***********************************************************************
* Includes
***********************************************************************/
#include "mozilla_iot.h"
#include "configuration.h"
/***********************************************************************
* Informations
***********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
/***********************************************************************
* Declarations
***********************************************************************/
#ifdef _mozilla_iot_enable_

//ThingActionObject *action_generator(DynamicJsonDocument *);

WebThingAdapter *adapter;

const char *WLanRSSI[] = {"WLan Signal Strengh", "RSSI", nullptr};
ThingDevice lamp("urn:dev:ops:my-lamp-1234", "My Lamp", WLanRSSI);

ThingProperty lampOn("on", "Whether the lamp is turned on", BOOLEAN,
                     "OnOffProperty");


bool lastOn = true;


#endif // _mozilla_iot_enable_
/***********************************************************************
* local Variable
***********************************************************************/

/***********************************************************************
* Global Variable
***********************************************************************/

/***********************************************************************
* Constant
***********************************************************************/


/***********************************************************************
*! \fn          uint8_t get_wlan_status()
*  \brief       return wlan connection status
*  \param       none
*  \exception   none
*  \return      return status of wlan
***********************************************************************/
error_type config_mozilla_iot(const char* DNSName){

//Disable code if no switch set
#ifdef _mozilla_iot_enable_
    
    char thingsID[255];
    sprintf(thingsID,"urn:dev:ops:%s", DNSName);
    //Change ThingsID
    lamp.id = thingsID;
    error_type return_code = er_no_error;
    //Set Name und IP as new Apater
    adapter = new WebThingAdapter(WiFi.getHostname(), WiFi.localIP());

    lamp.description = "A web connected lamp";


    return return_code;

#endif

}