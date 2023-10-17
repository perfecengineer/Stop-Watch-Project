/*
 * PriviteFunctions.h
 *
 *  Created on: Oct 1, 2023
 *      Author: ACS
 */

#ifndef PRIVITEFUNCTIONS_H_
#define PRIVITEFUNCTIONS_H_
/*** This function used to reset all setting, to another time ***/
static void reset_function(void);
/*** This function used to start the timer clock ***/
static void TIMER_enableClock(void);
/*** This function used to stop the timer clock ***/
static void TIMER_disableClock(void);
/*** This function used to seconds,mints and hours ***/
static void TIME_calculate(void);
/*** This variable used for store the number of seconds ****/
 static volatile unsigned char sec = 0;
 /*** This variable used for store the number of mints ****/
 static volatile unsigned char min = 0;
 /*** This variable used for store the number of hours ****/
 static volatile unsigned char hour = 0;
#endif /* PRIVITEFUNCTIONS_H_ */
