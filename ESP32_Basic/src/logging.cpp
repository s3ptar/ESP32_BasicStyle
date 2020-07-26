/***********************************************************************
*! \file:                   logging.cpp
*  \projekt:                FT800_ESP
*  \created on:             2020.07.07
*  \author:                 R. Gräber
*  \version:                0
*  \history:                -
*  \brief                   Logging Funktion, e.g. serial oder device
***********************************************************************/
 
/***********************************************************************
* Includes
***********************************************************************/
#include "logging.h"
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
 
/***********************************************************************
* Constant
***********************************************************************/
 
/***********************************************************************
* Local Funtions
***********************************************************************/

/***********************************************************************
*! \fn          logging::loging()
*  \brief       default class constructor
*  \param       none
*  \exception   none
*  \return      none
***********************************************************************/
logging::logging(){

    if (!current_logging_time)
        current_logging_time = _default_periodic_logging_ms_;

    #ifdef _serial_console_enable_
        //start serial console
        Serial.begin(115200);
        Serial.println("serial console enable");
        //_serial_log_enable_ = true;

    #endif

}

/***********************************************************************
*! \fn          logging::loging(uint32_t logging_ms)
*  \brief       class constructor with logging speed
*  \param       uint32_t logging_ms -> Logging speed in ms
*  \exception   none
*  \return      none
***********************************************************************/
logging::logging(uint32_t logging_ms){

    current_logging_time = _default_periodic_logging_ms_;
    logging();


}


/***********************************************************************
*! \fn          uint8_t logging::callback_periodic_logging()
*  \brief       write the logentrys to the log devices
*  \param       none
*  \exception   none
*  \return      none
***********************************************************************/
void logging::callback_logging(){

    //serial logging enable
    if (logging::_serial_log_enable_)
        Serial.println("up " + uptime_formatter::getUptime());
    

}
