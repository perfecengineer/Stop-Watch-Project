/*
 * sw_components.h
 *
 *  Created on: Oct 1, 2023
 *      Author: ACS
 */

#ifndef APP_SW_COMPONENTS_H_
#define APP_SW_COMPONENTS_H_
#include <avr/interrupt.h>
/************************ Functions Prototypes **********/
/*** Initial function use to setup the EXT_INT0 ***/
void initiat_INT0(void);
/*** Initial function use to setup the EXT_INT1 ***/
void initiat_INT1(void);
/*** Initial function use to setup the EXT_INT2 ***/
void initiat_INT2(void);
/*** Initial function use to setup the Timer 1 in CTC Mode ***/
void initiat_Timer1_CTC_Mode(void);
/*** Display function on 7 segments ***/
void display(void);
/**** This function used to setup the connection port of 7-segment and decoder ***/
void SEVEN_segmentAndDecoderSetupConnectionPorts(void);


#endif /* APP_SW_COMPONENTS_H_ */
