#include <Arduino.h>
#include "settings.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>
#include <Thing.h>
#include <WebThingAdapter.h>

#include "configuration.h"
#include "stdint.h"
#include "heltec.h"
#include <analogWrite.h>
/***********************************************************************
* Informations
***********************************************************************/
//https://www.dyclassroom.com/c/c-pointers-and-two-dimensional-array
//https://resource.heltec.cn/download/WiFi_Kit_32/WIFI_Kit_32_Schematic_diagram_V2.pdf
//https://iot.mozilla.org/framework/
/***********************************************************************
* Declarations
***********************************************************************/
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");
HardwareSerial SerialCom1(1);
/***********************************************************************
* Global Variable
***********************************************************************/
//Enter your SSID and PASSWORD
const char* ssid = "chilihotdog";
const char* password = "bxJHckMMkGqEPfY3Jf3nZnAn5FtGYwKZSkzVvbzFHNbpUZfv79GXm8afDuNu";

/***********************************************************************
* Constant
***********************************************************************/
time_t now;
char strftime_buf[64];
struct tm timeinfo;
char msgBuffer[1024];


#if defined(LED_BUILTIN)
const int lampPin = LED_BUILTIN;
#else
const int lampPin = 25; // manually configure LED pin
#endif

ThingActionObject *action_generator(DynamicJsonDocument *);

WebThingAdapter *adapter;

const char *lampTypes[] = {"OnOffSwitch", "Light", nullptr};
ThingDevice lamp("urn:dev:ops:my-lamp-1234", "My Lamp", lampTypes);

ThingProperty lampOn("on", "Whether the lamp is turned on", BOOLEAN,
                     "OnOffProperty");
ThingProperty lampLevel("brightness", "The level of light from 0-100", INTEGER,
                        "BrightnessProperty");

StaticJsonDocument<256> fadeInput;
JsonObject fadeInputObj = fadeInput.to<JsonObject>();
ThingAction fade("fade", "Fade", "Fade the lamp to a given level",
                 "FadeAction", &fadeInputObj, action_generator);
ThingEvent overheated("overheated",
                      "The lamp has exceeded its safe operating temperature",
                      NUMBER, "OverheatedEvent");

bool lastOn = true;
/***********************************************************************
* Local Funtions
***********************************************************************/



/***********************************************************************
*! \fn          void execption_handling()
*  \brief       handle the execption
*  \param       uint32_t error_code - error code
*  \exception   none
*  \return      none
***********************************************************************/


/***********************************************************************
*! \fn          void setup()
*  \brief       Arduino Setup - Routine
*  \param       none
*  \exception   none
*  \return      none
***********************************************************************/
void setup() {

    //############ local Variablen #################################
    pinMode(lampPin, OUTPUT);
  digitalWrite(lampPin, HIGH);
  Serial.begin(115200);
  Serial.println("");
  Serial.print("Connecting to \"");
  Serial.print(ssid);
  Serial.println("\"");

    //AddLogEntry(id_intern_serial, id_empty_source ,id_open_serial , id_no_error );
#ifdef _Heltec_Board_
    log_d("OLED start");
    pinMode(25, OUTPUT);
    digitalWrite(25,HIGH);
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, false/*Serial Enable*/);
    
#endif
    WiFi.begin(ssid, password);
    Serial.println("");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  adapter = new WebThingAdapter("led-lamp", WiFi.localIP());

  lamp.description = "A web connected lamp";

  lampOn.title = "On/Off";
  lamp.addProperty(&lampOn);

  lampLevel.title = "Brightness";
  lampLevel.minimum = 0;
  lampLevel.maximum = 100;
  lampLevel.unit = "percent";
  lamp.addProperty(&lampLevel);

  fadeInputObj["type"] = "object";
  JsonObject fadeInputProperties =
      fadeInputObj.createNestedObject("properties");
  JsonObject brightnessInput =
      fadeInputProperties.createNestedObject("brightness");
  brightnessInput["type"] = "integer";
  brightnessInput["minimum"] = 0;
  brightnessInput["maximum"] = 100;
  brightnessInput["unit"] = "percent";
  JsonObject durationInput =
      fadeInputProperties.createNestedObject("duration");
  durationInput["type"] = "integer";
  durationInput["minimum"] = 1;
  durationInput["unit"] = "milliseconds";
  lamp.addAction(&fade);

  overheated.unit = "degree celsius";
  lamp.addEvent(&overheated);

  adapter->addDevice(&lamp);
  adapter->begin();

  Serial.println("HTTP server started");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.print("/things/");
  Serial.println(lamp.id);

#ifdef analogWriteRange
  analogWriteRange(255);
#endif

  // set initial values
  ThingPropertyValue initialOn = {.boolean = true};
  lampOn.setValue(initialOn);
  (void)lampOn.changedValueOrNull();

  ThingPropertyValue initialLevel = {.integer = 50};
  lampLevel.setValue(initialLevel);
  (void)lampLevel.changedValueOrNull();

  analogWrite(lampPin, 128);

  randomSeed(analogRead(0));

    //Declatation
    //set time zone
    Serial.println("Set Time Zone");
    setenv("TZ", "UTC", 1);
    tzset();

    
    


}

/***********************************************************************
*! \fn          void loop()
*  \brief       construct host command and send to graphics controller
*  \param       uint32_t HostCommand
*  \exception   none
*  \return      none
***********************************************************************/
void loop(void) {
  adapter->update();
  bool on = lampOn.getValue().boolean;
  if (on) {
    int level = map(lampLevel.getValue().number, 0, 100, 255, 0);
    analogWrite(lampPin, level);
  } else {
    analogWrite(lampPin, 255);
  }

  if (lastOn != on) {
    lastOn = on;
  }
}


void do_fade(const JsonVariant &input) {
  JsonObject inputObj = input.as<JsonObject>();
  long long int duration = inputObj["duration"];
  long long int brightness = inputObj["brightness"];

  delay(duration);

  ThingDataValue value = {.integer = brightness};
  lampLevel.setValue(value);
  int level = map(brightness, 0, 100, 255, 0);
  analogWrite(lampPin, level);

  ThingDataValue val;
  val.number = 102;
  ThingEventObject *ev = new ThingEventObject("overheated", NUMBER, val);
  lamp.queueEventObject(ev);
}

ThingActionObject *action_generator(DynamicJsonDocument *input) {
  return new ThingActionObject("fade", input, do_fade, nullptr);
}