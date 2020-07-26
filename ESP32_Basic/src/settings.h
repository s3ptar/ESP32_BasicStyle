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
/***********************************************************************
* Informations
**********************************************************************/
//https://download.bastelgarage.ch/Datasheet/ESP8266_Heltec_Wifi_Kit_Schema.png
 
/***********************************************************************
* Declarations
**********************************************************************/

/*********************************************************************************************\
 * This file consists of TWO sections.
 *
 * SECTION 1:
 * The first section contains PARAMETERS overriding flash settings if define CFG_HOLDER is CHANGED.
 * All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
 *   Corresponding MQTT/Serial/Console commands are shown in [brackets]
 *
 * SECTION 2:
 * The second section contains Enabled and Disabled FEATURES allowing different program size.
 *   Changes in this section do NOT need a change of define CFG_HOLDER.
 *
 * ATTENTION:
 * Users are advised to use the user_config_override.h file for most changes.
\*********************************************************************************************/

//#define USE_CONFIG_OVERRIDE                      // Uncomment to use user_config_override.h file. See README.md

/*********************************************************************************************\
 * SECTION 1
 * - After initial load any change here only take effect if CFG_HOLDER is changed too
\*********************************************************************************************/

// -- Master parameter control --------------------
#define CFG_HOLDER             4617              // [Reset 1] Change this value (max 32000) to load SECTION1 configuration parameters to flash

// -- Project -------------------------------------
#define PROJECT                "ESP32_Basic"         // PROJECT is used as the default topic delimiter

// If not selected the default will be SONOFF_BASIC
//#define MODULE                 SONOFF_BASIC      // [Module] Select default model from tasmota_template.h

#define SAVE_DATA              1                 // [SaveData] Save changed parameters to Flash (0 = disable, 1 - 3600 seconds)
#define SAVE_STATE             true              // [SetOption0] Save changed power state to Flash (false = disable, true = enable)
#define BOOT_LOOP_OFFSET       1                 // [SetOption36] Number of boot loops before starting restoring defaults (0 = disable, 1..200 = boot loops offset)

// -- Wifi ----------------------------------------
#define WIFI_IP_ADDRESS        "0.0.0.0"         // [IpAddress1] Set to 0.0.0.0 for using DHCP or enter a static IP address
#define WIFI_GATEWAY           "192.168.1.1"     // [IpAddress2] If not using DHCP set Gateway IP address
#define WIFI_SUBNETMASK        "255.255.255.0"   // [IpAddress3] If not using DHCP set Network mask
#define WIFI_DNS               "192.168.1.1"     // [IpAddress4] If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)

#define STA_SSID1              "chilihotdog"                // [Ssid1] Wifi SSID
#define STA_PASS1              "bxJHckMMkGqEPfY3Jf3nZnAn5FtGYwKZSkzVvbzFHNbpUZfv79GXm8afDuNu"                // [Password1] Wifi password
#define STA_SSID2              ""                // [Ssid2] Optional alternate AP Wifi SSID
#define STA_PASS2              ""                // [Password2] Optional alternate AP Wifi password
#define WIFI_AP_PASSPHRASE     ""                // AccessPoint passphrase. For WPA2 min 8 char, for open use "" (max 63 char).
#define WIFI_CONFIG_TOOL       WIFI_RETRY        // [WifiConfig] Default tool if wifi fails to connect (default option: 4 - WIFI_RETRY)
                                                 // (WIFI_RESTART, WIFI_MANAGER, WIFI_RETRY, WIFI_WAIT, WIFI_SERIAL, WIFI_MANAGER_RESET_ONLY)
                                                 // The configuration can be changed after first setup using WifiConfig 0, 2, 4, 5, 6 and 7.
#define WIFI_ARP_INTERVAL      0                 // [SetOption41] Send gratuitous ARP interval
#define WIFI_SCAN_AT_RESTART   false             // [SetOption56] Scan wifi network at restart for configured AP's
#define WIFI_SCAN_REGULARLY    false             // [SetOption57] Scan wifi network every 44 minutes for configured AP's

#define MQTT_USE               true              // [SetOption3] Select default MQTT use (false = Off, true = On)

#define MQTT_HOST              "192.168.0.222"                // [MqttHost]
#define MQTT_FINGERPRINT1      "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"  // [MqttFingerprint1]
#define MQTT_FINGERPRINT2      "A5 02 FF 13 99 9F 8B 39 8E F1 83 4F 11 23 65 0B 32 36 FC 07"  // [MqttFingerprint2]
#define MQTT_PORT              1883              // [MqttPort] MQTT port (10123 on CloudMQTT)
#define MQTT_USER              ""       // [MqttUser] MQTT user
#define MQTT_PASS              ""       // [MqttPassword] MQTT password
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


#endif /* _settings_H_ */
