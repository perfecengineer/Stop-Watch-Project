/*
 * sw_components.c
 *
 *  Created on: Oct 1, 2023
 *      Author: ACS
 */
#include <avr/io.h>
#include <avr/delay.h>
#include "sw_components.h"
#include "PriviteFunctions.h"

 /************************ Functions Implementations **********/
 /*** Initial function use to setup the EXT_INT0 ***/
void initiat_INT0(void)
{
	// Configure INT0/PD2 as input pin
	DDRD  &= (~(1<<PD2));
	// Enable internal pull up resistor at INT0/PD2 pin
	PORTD |= (1<<PD2);
	// Trigger INT0 with the falling edge
	MCUCR &= ~(1<<ISC00);
	MCUCR |= (1<<ISC01);
	// Enable external interrupt pin INT0
	GICR  |= (1<<INT0);

}
/*** Initial function use to setup the EXT_INT1 ***/
void initiat_INT1(void)
{
	// Configure INT1/PD3 as input pin
	DDRD  &= (~(1<<PD3));
	// Trigger INT1 with the raising edge
	MCUCR |= (1<<ISC10);
	MCUCR |= (1<<ISC11);
	// Enable external interrupt pin INT1
	GICR  |= (1<<INT1);
}
/*** Initial function use to setup the EXT_INT2 ***/
void initiat_INT2(void)
{
	// Configure INT2/PB2 as input pin
	DDRB   &= (~(1<<PB2));
	// Enable internal pull up resistor at INT2/PB2 pin
    PORTB |= (1<<PB2);
	// Trigger INT2 with the falling edge
	MCUCSR &= !(1<<ISC2);
	// Enable external interrupt pin INT2
	GICR   |= (1<<INT2);
}
/*** Initial function use to setup the Timer 1 in CTC Mode ***/
void initiat_Timer1_CTC_Mode(void)
{
	/***In the first clear the counter register of timer 1 ***/
	TCNT1 = 0;
	/* Configure timer1 control registers
	 * 1. Non PWM mode FOC1A=1 and FOC1B=1
	 * 2. No need for OC1A & OC1B in this example so COM1A0=0 & COM1A1=0 & COM1B0=0 & COM1B1=0
	 * 3. CTC Mode and compare value in OCR1A WGM10=0 & WGM11=0 & WGM12=1 & WGM13=0
	 */
	TCCR1A = (1 << FOC1A) | (1 << FOC1B);
	/*
	 * 4. Clock = F_CPU/1024 CS10=1 CS11=0 CS12=1
	 */
	TCCR1B = (1 <<  WGM12) | (1 <<  CS10) | (1 <<  CS12);
	/*** enable compare interrupt for channel A ***/
	TIMSK = (1 << OCIE1A);
	/*** Set the the compare value ***/
	OCR1A = 976;
}
/*** This function used to reset all setting, to another time ***/
static void reset_function(void)
{
	/*** reset the counter register of timer 1 ***/
	TCNT1 = 0;
	/*** Clear all the flags & counters that used ***/
	sec = 0;
	min = 0;
	hour = 0;

}
/*** Display function on 7 segments ***/
void display(void)
{
	/* .Enable the first 7-segment used to display seconds.
	 * . For 3 mili_sec
	 */
	PORTA = (1 << PA0);
	PORTC = ((PORTC & 0XF0) | ((sec % 10) & 0X0F));
	_delay_ms(3);
	/* .Enable the second 7-segment used to display number of seconds.
	 * . For 3 mili_sec
	 */
	PORTA = (1 << PA1);
	PORTC = ((PORTC & 0XF0) | ((sec / 10) & 0X0F));
	_delay_ms(3);
	/* .Enable the third 7-segment used to display mints.
	 * . For 3 mili_sec
	 */
	PORTA = (1 << PA2);
	PORTC =  (PORTC & 0XF0) | ((min % 10) & 0X0F);
	_delay_ms(3);
	/* .Enable the fourth 7-segment used to display number of mints.
	 * . For 3 mili_sec
	 */
	PORTA = (1 << PA3);
	PORTC =  (PORTC & 0XF0) | ((min / 10) & 0X0F);
	_delay_ms(3);
	/* .Enable the fifth 7-segment used to display hours.
	 * . For 3 mili_sec
	 */
	PORTA = (1 << PA4);
	PORTC =  (PORTC & 0XF0) |((hour % 10) & 0X0F);
	_delay_ms(3);
	/* .Enable the sixth 7-segment used to display number of hours.
	 * . For 3 mili_sec
	 */
	PORTA = (1 << PA5);
	PORTC =  (PORTC & 0XF0) | ((hour / 10) & 0X0F);
	_delay_ms(3);
}
/*** This function used to start the timer clock ***/
static void TIMER_enableClock(void){
	/*
	 * Clock = F_CPU/1024 CS10=1 CS11=0 CS12=1
	 */
	TCCR1B |= (1 <<  CS10) | (1 <<  CS12);
}
/*** This function used to stop the timer clock ***/
static void TIMER_disableClock(void)
{
	/*
	 * Clock = 0, CS10=0 CS11=0 CS12=0
	 */
	TCCR1B &= 0XF8;
}
/*** This function used to seconds,mints and hours ***/
static void TIME_calculate(void)
{
	/*
	 * .increment the counter of second.
	 * . if counter == 60 second , increment the counter of mints by one,
	 * and clear the counter of second.
	 */
	sec++;
	if(sec > 59)
	{
		sec = 0;
		min++;
	}
	/*
	 * . if counter == 60 mint,increment the counter of hours by one,
	 * and clear the counter of mints.
	 */
	if(min > 59)
	{
		min = 0;
		hour++;
	}
	/*
	 * . if counter == 99 hours,reset the Watch to count from start.
	 */
	if(hour > 99)
	{
		reset_function();
	}
}
/**** This function used to setup the connection port of 7-segment and decoder ***/
void SEVEN_segmentAndDecoderSetupConnectionPorts(void)
{
	DDRA |= 0X3F;//Decoder select the 7_segmant
	DDRC |= 0X0F;//Display PORT
	/*** Enable the first 7-segment in strat ***/
	PORTA = 1;
	/*** Clear all 7-segments in start ***/
	PORTC = 0;
}
ISR(INT0_vect)
{
	/*** When Triggered EX_INT0,
	 * Restart the timer to start new counts.
	 */
	reset_function();
	TIMER_enableClock();
}
ISR(INT1_vect)
{
	/*** Disable the clock of timer 1, to stop count ***/
	TIMER_disableClock();
}
ISR(INT2_vect)
{
	/*** Enable the clock of timer 1, to start count ***/
	TIMER_enableClock();
}
ISR(TIMER1_COMPA_vect)
{
	/*** This function used to seconds,mints and hours ***/
	TIME_calculate();
}
