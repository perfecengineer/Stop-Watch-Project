#include "sw_components.h"
int main(void)
{
	/*** Enable the global interrupt ***/
	SREG |= (1 << 7);
	/**** Setup the connection port of 7-segment and decoder ***/
	SEVEN_segmentAndDecoderSetupConnectionPorts();
	/*** setup the setting of EXT_INT0 ***/
	initiat_INT0();
	/*** setup the setting of EXT_INT1 ***/
	initiat_INT1();
	/*** setup the setting of EXT_INT2 ***/
	initiat_INT2();
	/*** setup the setting of Timer 1 in CTC mode ***/
	initiat_Timer1_CTC_Mode();

	while(1)
	{
		/*** Display the data on the all 7-segments ***/
		display();
	}

	return 0;
}
