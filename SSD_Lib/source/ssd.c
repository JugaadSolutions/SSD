
/*
*------------------------------------------------------------------------------
* ssd.c
*
* Seven Segment Display module supporting 7 segment digit displays.
* Refreshing scheme is used to provide a stationary display.
* Data to be displayed is either a digit(0-9) or space(' ') in ascii
* Space represents clear i.e all segments of the 7 segment display
* turned off.
* The data for each particular digit is put on DISPLAY_PORT, which
* is common to all the digits.
* 
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* INCLUDES
*------------------------------------------------------------------------------
*/

#include "ssd.h"

/*
*------------------------------------------------------------------------------
* Private Variables (static) 
*------------------------------------------------------------------------------
*/

static const UINT8 SEVENSEGMENT[] ={0x3f,0x06,0x5b,0x4f,0x66,
							  0x6d,0x7d,0x07,0x7f,0x6f,0x00};

#pragma idata	SSD_DATA
SSD ssd = {0};
#pragma idata


/*
*------------------------------------------------------------------------------
* Private Function Prototypes (static)
*------------------------------------------------------------------------------
*/

static void writeToSSDPort( UINT8, UINT8 );
static UINT8 validate( UINT8 value );
/*
*------------------------------------------------------------------------------
* Public Functions
*------------------------------------------------------------------------------
*/





/*------------------------------------------------------------------------------
* void  SSD_Init( void )
*
* Function to initialize the ssd fields. All variables in the field will be 
* initialize to zero, except blink index.
* 
* Input :none
* return value: none.
* 
*------------------------------------------------------------------------------*/
void  SSD_Init( void )
{
	UINT8 i;

	for( i = 0; i < MAX_FIELDS; i++ )
	{

	}

#if defined (SSH_TEST)

#endif
}