
/*
*------------------------------------------------------------------------------
* device.c
*
* Board specipic drivers module(BSP)
*
* (C)2009 Sam's Logic.
*
* The copyright notice above does not evidence any
* actual or intended publication of such source code.
*
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* File				: device.c
* Created by		: Sam
* Last changed by	: Sam
* Last changed		: 11/12/2010 
*------------------------------------------------------------------------------
* Revision 1.3 11/12/2010  Sam
* Demo Release
* Revision 1.2 15/11/2010  Sam
* Updated according to the current project requirement
* Revision 1.1 07/07/2010 Sam
* First Release
* Revision 1.0 14/07/2009 Sam
* Initial revision
*
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Include Files
*------------------------------------------------------------------------------
*/


#include "board.h"
#include "config.h"
#include "typedefs.h"




/*
*------------------------------------------------------------------------------
* Private Defines
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Macros
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Data Types
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Variables
*------------------------------------------------------------------------------
*/
UINT16 tickPeriod = 0;
/*
*------------------------------------------------------------------------------
* Private Variables (static)
*------------------------------------------------------------------------------
*/

static BOOL ledState;

/*
*------------------------------------------------------------------------------
* Public Constants
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Constants (static)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Private Function Prototypes (static)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Functions
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* void InitializeBoard(void)

* Summary	: This function configures all i/o pin directions
*
* Input		: None
*
* Output	: None
*
*------------------------------------------------------------------------------
*/
void BRD_init(unsigned long systemFreauency )
{



	unsigned long temp;


	switch(systemFreauency)
	{
		case MHz_32:
		default:
				OSCCON = 0X70; 		//internal oscillator 8MHz
				OSCTUNEbits.PLLEN = 1;	//PLL Enable
		break;

		case MHz_16:
				OSCCON = 0X60; 		//internal oscillator 4MHz
				OSCTUNEbits.PLLEN = 1;	//PLL Enable
		break;
		
		case MHz_8:
				OSCCON = 0X50; 		//internal oscillator 2MHz
				OSCTUNEbits.PLLEN = 1;	//PLL Enable
		break;
	}
	DelayMs(5);

	//calculating tick period for timer-0
	temp = systemFreauency >> 2;	
	temp *= (TIMER0_TIMEOUT_DURATION/1000);
	temp /= 1000;		

	tickPeriod = (FULLSCALE_16BIT - (UINT16)temp);


	// set all anolog channels as Digital I/O
	ADCON0 = 0x00;
	ADCON1 = 0x0F;
	ADCON2 = 0xB5;

	MEMCON = 0x80;

	// Configure heart beat LED output
	HEART_BEAT_DIR 	= PORT_OUT;
	HEART_BEAT 		= SWITCH_OFF;
/*
	PORT_A_DIR		= PORT_OUT
	PORT_B_DIR		= PORT_OUT
	PORT_C_DIR		= PORT_OUT
	PORT_D_DIR		= PORT_OUT
	PORT_E_DIR		= PORT_OUT
	PORT_F_DIR		= PORT_OUT
	PORT_H_DIR		= PORT_OUT
	PORT_J_DIR		= PORT_OUT
*/
	TRISA	= PORT_OUT;
	TRISB	= PORT_OUT;
	TRISC	= PORT_OUT;
	TRISD	= PORT_OUT;
	TRISE	= PORT_OUT;
	TRISF	= PORT_OUT;
	TRISH	= PORT_OUT;
	TRISJ	= PORT_OUT;
	DelayMs(100);

}

	



/*
*------------------------------------------------------------------------------
* Private Functions
*------------------------------------------------------------------------------
*/

/*
*  End of device.c
*/
