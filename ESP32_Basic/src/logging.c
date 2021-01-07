/***********************************************************************
*! \file:                   logging.c
*  \projekt:                logging
*  \created on:             26.07.2020
*  \author:                 R. Gräber
*  \version:                0
*  \history:                -
*  \brief                   handle error codes and deivice id´s
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
*! \fn          void AddLogEntry(uint8_t source_id, uint16_t task_id, uint16_t error_id)
*  \brief       write messages to log deives
*  \param       uint8_t source_id - id of source
*  \param       uint16_t task_id
*  \param       uint16_t error_id
*  \exception   none
*  \return      length of frame buffer
***********************************************************************/
void AddLogEntry(uint8_t source_id, uint16_t task_id, uint16_t error_id){

#ifdef _logging_level_enable_

#ifdef _logging_level_1_ 

    hwdrv_write_serial(1);

#endif //_logging_level_1_  

#endif //_logging_level_enable


}