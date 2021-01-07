/***********************************************************************
*! \file:                   error_codes.h
*  \projekt:                error_codes
*  \created on:             26.07.2020
*  \author:                 R. Gräber
*  \version:                0
*  \history:                -
*  \brief
***********************************************************************/
 
#ifndef _error_codes_H_
#define _error_codes_H_
 
/***********************************************************************
* Includes
**********************************************************************/
#include "logging.h"
#include "user_config.h"
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
enum ErrorID{
    Okay = 0,
    Error_Mounting_SPIFFS = 1

};

enum SourceID{
    id_intern_serial = 0
};

enum EventID{
    id_intern_serial = 0
};

#ifndef _logging_compact_

    static const char * const LogMessages_SourceID_Ger[] = {"mon", 
        "tue", 
        "wed", 
        "thur",
        "fri", 
        "sat", 
        "sun"
    };

    static const char * const LogMessages_EventID_Ger[] = {"mon", 
        "tue", 
        "wed", 
        "thur",
        "fri", 
        "sat", 
        "sun"
    };

    static const char * const LogMessages_ErrorID_Ger[] = {"mon", 
        "tue", 
        "wed", 
        "thur",
        "fri", 
        "sat", 
        "sun"
    };

#endif //_logging_compact_

/***********************************************************************
 * Constant
 **********************************************************************/
 
/***********************************************************************
 * Macros
 **********************************************************************/
 
/***********************************************************************
 * Funtions
 **********************************************************************/
 
 
 
 
#endif /* _error_codes_H_ */
