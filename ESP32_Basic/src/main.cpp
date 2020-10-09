#include <Arduino.h>
#include "settings.h"
#include "global_var.h"
#include "ThreadController.h"
#include "uptime_formatter.h"
#include "dictionary.h"

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
hw_timer_t * timer = NULL;

// ThreadController that will controll all threads
ThreadController controll = ThreadController();
//My Thread
Thread StatusThread = Thread();

/***********************************************************************
*! \fn          void timerCallback()
*  \brief       This is the callback for the Timer
*  \param       none
*  \exception   none
*  \return      none
***********************************************************************/
void timerCallback(){
    controll.run();
}

/***********************************************************************
*! \fn          void setup()
*  \brief       Arduino Setup - Routine
*  \param       none
*  \exception   none
*  \return      none
***********************************************************************/
void print_status_to_concole(){



}


/***********************************************************************
*! \fn          void setup()
*  \brief       Arduino Setup - Routine
*  \param       none
*  \exception   none
*  \return      none
***********************************************************************/
void setup() {
    // put your setup code here, to run once:
  
    /******************* Configure Threads *************************/
    StatusThread.onRun(print_status_to_concole);
	StatusThread.setInterval(30000);
    controll.add(&StatusThread);
    /******************* Configure Threadcontroller *************************/
    /* Use 1st timer of 4 */
    /* 1 tick take 1/(80MHZ/80) = 1us so we set divider 80 and count up */
    timer = timerBegin(0, 80, true);
    /* Attach ThreadController function to timer */
    timerAttachInterrupt(timer, timerCallback, true);
    /* Set alarm to call onTimer function every second 1 tick is 1us
    => 1 second is 1000000us */
    /* Repeat the alarm (third parameter) */
    timerAlarmWrite(timer, 1000000, true);
    /* Start an alarm */
    timerAlarmEnable(timer);

    Serial.begin(115200);
}

/***********************************************************************
*! \fn          void loop(){
*  \brief       construct host command and send to graphics controller
*  \param       uint32_t HostCommand
*  \exception   none
*  \return      none
***********************************************************************/
void loop() {
  // put your main code here, to run repeatedly:

    controll.run();

}