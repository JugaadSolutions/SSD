#include <ssd.h>






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

//static void writeToSSDPort( UINT8);
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
void  SSD_Init( UINT8* digitPort_1,UINT8* digitPort_2,UINT8* digitPort_3,UINT8* digitPort_4,UINT8* dataPort)
{
	UINT8 i;

	ssd.digitPort_1 = digitPort_1;
	ssd.digitPort_2 = digitPort_2;
	ssd.digitPort_3 = digitPort_3;
	ssd.digitPort_4 = digitPort_4;
	ssd.dataPort	= dataPort;


	for( i = 0; i < MAX_FIELDS; i++ )
	{
		ssd.fields[i]. ID			 = 0;
		ssd.fields[i]. bufferIndex	 = 0;
		ssd.fields[i]. digits		 = 0;
		ssd.fields[i]. blink 		 = STATIC;
		ssd.fields[i]. dotIndex 	 = 0xFF;
	}

	ssd.fieldCount = 0;
	ssd.digitIndex = 0;
	ssd.blinkPeriod = 0;
	ssd.dispBuffer = ssd.buffer[STATIC];
#if defined (SSD_TEST)
		SSD_Test( 0 , MAX_DIGITS );
#endif

}


/*------------------------------------------------------------------------------
* UINT8 SSD_CreateField(UINT8 digits )

*
* Function to initialize the individual fields
* 
* Initializes field length to the value as per parameter  passed.	 
* Input : digits - Digits must be  < MAX_DIGITS and non zero value.
* return value: FIeld ID.
* 
*------------------------------------------------------------------------------*/

UINT8 SSD_CreateField(UINT8 digits)
{
	UINT8 i;  											//for calculation buffer index

	ssd.fields[ssd.fieldCount].ID 		= ssd.fieldCount;						//field number
	ssd.fields[ssd.fieldCount].digits 	= digits;								//no of digits of that field
	ssd.fields[ssd.fieldCount].blink	=  STATIC ;								//field digit status
	ssd.fields[ssd.fieldCount].dotIndex = 0xFF;									//field dot status
	

	if( ssd.fieldCount > 0)
	{

		for(i = ssd.fieldCount ; i > 0; i--)
		{
			ssd.fields[ssd.fieldCount].bufferIndex += ssd.fields[i-1].digits;	//caculation to get the buffer index of SSD buffer
		}
	}
	else
		ssd.fields[ssd.fieldCount].bufferIndex = 0;
		

	ssd.fieldCount++;

	return ssd.fields[ssd.fieldCount-1].ID;										//return the field number
}


/*------------------------------------------------------------------------------
*BOOL SSD_UpdateField(UINT8 field_ID, UINT8 *buffer);
*
* Function to update field content to in display buffer.
* 
* 
* Input : 
*              filed_ID   - ID of Field created by call to SSD_CreateField
*              buffer - pointer to buffer containing Data to be displayed in ASCII Format , must be non NULL.
*
* return value: True  - On Success
*                      False - On failure .
* 
*------------------------------------------------------------------------------*/
BOOL SSD_UpdateField(UINT8 field_ID, UINT8 *buffer)
{

	UINT8 i = 0 ;
	for ( i = 0 ; i < ssd.fields[field_ID].digits ; i++)
	{

		if ( validate(buffer[i]) == FAILURE )
			return FAILURE;
	}
	for ( i = 0 ; i < ssd.fields[field_ID].digits ; i++)
	{
		if( buffer[i] == ' ')
		{
			ssd.buffer[STATIC][ssd.fields[field_ID].bufferIndex + i] = SEVENSEGMENT[10];
		}
		else
		{
			ssd.buffer[STATIC][ssd.fields[field_ID].bufferIndex + i] = SEVENSEGMENT[buffer[i] - '0'];
		}
	}
	return SUCCESS;

}




/*------------------------------------------------------------------------------
* BOOL SSD_UpdateFieldpartial(UINT8 field_ID , UINT8 *buffer, UINT8 index , UINT8  no_of_digit);
* Function to update field content to  in display buffer.
* 
* 
* Input : 
* 	filed_ID  - ID of Field created by call to SSD_CreateField
*          buffer     -  pointer to buffer containing Data to be displayed in ASCII Format , must be non  NULL.
*		   index      - field index from which data to be updated.
*			no_of_digit - number of   digits to be updated.
* return value: True On Success
*               False - On failure .
* 
*------------------------------------------------------------------------------*/
BOOL SSD_UpdateFieldpartial(UINT8 field_ID , UINT8 *buffer, UINT8 index , UINT8 no_of_digit)
{
	UINT8 i = 0 ;
	for ( i = 0 ; i < no_of_digit ; i++)
	{

		if ( validate(buffer[index + i]) == FAILURE )
			return FAILURE;
	}
	for ( i = 0 ; i < no_of_digit ; i++)
	{
		if( buffer[index + i] == ' ')
		{
			ssd.buffer[STATIC][ssd.fields[field_ID].bufferIndex + (index + i)] = SEVENSEGMENT[10];
		}
		else
		{
			ssd.buffer[STATIC][ssd.fields[field_ID].bufferIndex + (index + i)] = SEVENSEGMENT[buffer[index + i] - '0'];
		}
	}
	return SUCCESS;

}



/*------------------------------------------------------------------------------
*  void SSD_Test(UINT8 from, UINT8 digits )
*
* Pre-Condition - SSD module must be initialized successfully with a call to SSD_Init
*
* Input : 
*           from - starting index of digits to be tested.
*           digits - No. of digits to be tested must be < MAX_DIGITS
* return value: none.
* 
*------------------------------------------------------------------------------*/
void SSD_Test(UINT8 from, UINT8 digits )
{
	UINT8 i,j,k;
/*
	if( digits > MAX_DIGITS )	//check limits 
		return FAILURE;

*/
	for( i = from; i < digits; i++)
	{
		ssd.buffer[BLINK][i] = SEVENSEGMENT[10];		//clear buffer to be used  during blink  mode
	}
	ssd.dispBuffer = ssd.buffer[STATIC];	//set initial display buffer to data(i.e. buffer[0])


	for(j = from; j < digits ; j++)
	{
		for( i = 0; i < 11 ; i++)
		{

			ssd.buffer[STATIC][ssd.digitIndex] = SEVENSEGMENT[i] ;
			SSD_Refresh();
			DelayMs(200);
		}
		
		ssd.digitIndex++;
	}
	
	ssd.digitIndex = 0;

}

/*------------------------------------------------------------------------------
*  void SSD_Refresh(void )
*
* ISR to refresh Display
* 
* Input : none 
* return value: none.
* 
*------------------------------------------------------------------------------*/
void SSD_Refresh(void)
{
	UINT8 shift = 0x01;
	
	*ssd.digitPort_1 = 0xFF;
	*ssd.digitPort_2 = 0xFF;
	*ssd.digitPort_3 = 0xFF;
	*ssd.digitPort_4 = 0xFF;

	*ssd.dataPort = ~ssd.buffer[STATIC][ssd.digitIndex];

	if(ssd.digitIndex < 8)
	{
		shift <<= ssd.digitIndex;
		*ssd.digitPort_1 = ~shift;
	}
//#if APP_MAX_DIGITS > 8
	else if ( ( ssd.digitIndex  >= 8 ) && ( ssd.digitIndex < 16) )
	{
		shift <<= ssd.digitIndex - 8;
		*ssd.digitPort_2 = ~shift;
	}
//#endif

//#if APP_MAX_DIGITS > 16
	else if ( ( ssd.digitIndex >= 16 ) && ( ssd.digitIndex < 24) )
	{
		shift <<= ssd.digitIndex - 16;
		*ssd.digitPort_3 = ~shift;
	}
//#endif
#ifndef SSD_TEST
	ssd.digitIndex++;
#endif
	if(ssd.digitIndex > MAX_DIGITS)
	{
		ssd.digitIndex = 0;
	}

}

/*------------------------------------------------------------------------------
*  BOOL SSD_BlinkOn( UINT8 field_ID )
*
* Function to turn ON blinking feature
* 
* 
* Input :    filed_ID   - ID of Field created by call to SSD_CreateField
*  
* return value: True On Success
*                      False - On failure .
* 
*------------------------------------------------------------------------------*/
BOOL SSD_BlinkOn( UINT8 field_ID ,UINT16 blinkPeriod)
{
	UINT8 result = FALSE;
	ssd.blinkPeriod = blinkPeriod / DISPLAY_REFRESH_PERIOD;	//convert period in milliseconds to period in count
	ssd.blinkCount = 0;										//reset counter
	ssd.fields[field_ID].blink = BLINK;											//set blink mode
	
	result = TRUE;
	return result;
}	




/*------------------------------------------------------------------------------
*  BOOL  SSD_BlinkOff( UINT8 field_ID )
*
* Function to turn OFF blinking feature of the field 
* 
* 
* Input :    filed_ID   - ID of Field created by call to SSD_CreateField

* return value: True On Success
*                      False - On failure .
* 
*------------------------------------------------------------------------------*/
BOOL SSD_BlinkOff( UINT8 field_ID )
{
	UINT8 result = FALSE;
	
	ssd.dispBuffer = ssd.buffer[STATIC]; //set current display buffer to data buffer
	ssd.fields[field_ID].blink = STATIC;							   //set static mode

	result = TRUE;
	return result;
}



/*------------------------------------------------------------------------------
*  static BOOL validate( UINT8 value)
*
* check the data fill to buffer is valide or not
* 
* Input : field buffer data
* return value: SUCCESS  On Success
*               FAILURE  On failure .
* 
*------------------------------------------------------------------------------*/

static BOOL validate( UINT8 value)
{
	BOOL result = FAILURE;
	if( value == ' ' )
	{
		result = SUCCESS;
	}
	else if( value >= '0' && value <= '9'  )
	{
		result = SUCCESS;
	}
	return result;
}

