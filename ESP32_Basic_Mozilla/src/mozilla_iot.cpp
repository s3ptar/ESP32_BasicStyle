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
//https://iot.mozilla.org/gateway/
//https://iot.mozilla.org/wot/
//https://discourse.mozilla.org/t/webthing-arduino-thingproperty-unit/43918/9
//https://discourse.mozilla.org/t/multilevelsensor-and-onoffswitch/55939/3
/***********************************************************************
* Declarations
***********************************************************************/
#ifdef _mozilla_iot_enable_

//ThingActionObject *action_generator(DynamicJsonDocument *);

WebThingAdapter *adapter;

const char *deviceTypes[] = {"MultiLevelSensor", nullptr};
ThingDevice IoTDev("RSSI Sensor", "RSSISensor", deviceTypes);
ThingProperty SignalStrength("id_rssi", "SignalStrength of WLan signal", INTEGER,
                    "LevelProperty");


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
error_type config_mozilla_iot(){

//Disable code if no switch set
#ifdef _mozilla_iot_enable_
    
    char thingsID[255];
    sprintf(thingsID,"urn:dev:ops:%s", WiFi.getHostname());
    //Change ThingsID
    IoTDev.id = thingsID;
    error_type return_code = er_no_error;
    //Set Name und IP as new Apater
    log_d("Start WebThingAdapter");
    adapter = new WebThingAdapter(WiFi.getHostname(), WiFi.localIP());

    log_d("Config Propertys");
    IoTDev.description = "Basic ESP, sending RSSI";

    SignalStrength.title = "deviceTypes";
    SignalStrength.unit = "dB";
    SignalStrength.maximum = 100;
    SignalStrength.minimum = 0;
    IoTDev.addProperty(&SignalStrength);

    adapter->addDevice(&IoTDev);
    adapter->begin();

    // set initial values
    ThingPropertyValue initialRSSI = {.integer = WiFi.RSSI()};
    SignalStrength.setValue(initialRSSI);
    (void)SignalStrength.changedValueOrNull();


    return return_code;

#endif

}

/***********************************************************************
*! \fn          uint8_t get_wlan_status()
*  \brief       return wlan connection status
*  \param       none
*  \exception   none
*  \return      return status of wlan
***********************************************************************/
void update_iot(){


    ThingPropertyValue MVal;
    MVal.integer = WiFi.RSSI();
    SignalStrength.setValue(MVal);
    adapter->update();

}