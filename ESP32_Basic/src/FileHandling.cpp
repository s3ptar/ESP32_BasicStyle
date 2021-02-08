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
/***********************************************************************
* Constant
***********************************************************************/

/***********************************************************************
*! \fn          uint8_t check_file(String filename)
*  \brief       check if the file exist
*  \param       String filename - full path
*  \exception   none
*  \return      return codes, 0 is okay
***********************************************************************/
uint8_t check_file(String filename){

    uint8_t return_code = no_error;

    if(!spiffs_flags.spiff_mounted){
        if(!SPIFFS.begin(true)){
            log_e("An Error has occurred while mounting SPIFFS");
            spiffs_flags.spiff_mounted = 0;
            return_code  = spiffs_fault;
        }else{
            spiffs_flags.spiff_mounted = 1;
            log_i("SPIFFS mounting successfully");
            File root = SPIFFS.open("/");
            File file = root.openNextFile();
            //list all files in spiffs
            while(file){
                log_i("File: %s", file.name());
                file = root.openNextFile();
            }
            file.close();
            root.close();
        }
        
    }else{
        log_i("SPIFFS already mounted");
    }

    //check if config file available
    File file = SPIFFS.open("/config.json", FILE_READ);
    if (!file) {
        log_e("There was an error opening the file for writing");
    }
    while (file.available()){
        Serial.write(file.read());
    }
    file.close();
    

    return return_code ;
}

/***********************************************************************
*! \fn          uint8_t check_file(String filename)
*  \brief       check if the file exist
*  \param       String filename - full path
*  \exception   none
*  \return      return codes, 0 is okay
***********************************************************************/
String read_json_file_as_string(const char* file_path, String Key){

    DynamicJsonDocument doc(1024);
    File file = SPIFFS.open("/config.json", FILE_READ);
    if (!file) {
        log_e("There was an error opening the file for reading");
    }
    while (file.available()){
        Serial.write(file.read());
    }
    DeserializationError error = deserializeJson(doc, file);
    if (error)
        log_e("Failed to read file, using default configuration");
    return doc["name"];

}
