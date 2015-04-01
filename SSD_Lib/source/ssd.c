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

static UINT8 validate( UINT8 value );
/*
*------------------------------------------------------------------------------
* Public Functions
*------------------------------------------------------------------------------
*/





/*------------------------------------------------------------------------------
* void  SSD_Init( UINT8* digitPort_1,UINT8* digitPort_2,UINT8* digitPort_3,UINT8* digitPort_4,UINT8* dataPort,UINT8 noOfDigits, UINT8 noOfFields)
*
* Function to initialize the ssd fields. All variables in the field will be 
* initialize to zero, except blink index.
* 
* Input :none
* return value: none.
* 
*------------------------------------------------------------------------------*/
void  SSD_Init( UINT8* digitPort_1,UINT8* digitPort_2,UINT8* digitPort_3,UINT8* digitPort_4,UINT8* dataPort,
				UINT8 noOfDigits, UINT8 noOfFields,UINT8 commonCathode)
{
	UINT8 i;
	ssd.noOfDigits		= noOfDigits;
	ssd.noOfFields	 	= noOfFields;
	ssd.digitPort[0]	= digitPort_1;
	ssd.digitPort[1]	= digitPort_2;
	ssd.digitPort[2]	= digitPort_3;
	ssd.digitPort[3]	= digitPort_4;
	ssd.dataPort		= dataPort;
	ssd.fieldCount		= 0;
	ssd.digitIndex 		= 0;
	ssd.commonCathode 	= commonCathode;

	for( i = 0; i < ssd.noOfFields; i++ )
	{
		ssd.fields[i]. ID			 = 0;
		ssd.fields[i]. bufferIndex	 = 0;
		ssd.fields[i]. digits		 = 0;
		ssd.fields[i]. blink 		 = STATIC;
		ssd.fields[i].blinkPeriod	 = 0;
		ssd.fields[i].blinkCount	 = 0;
		ssd.fields[i]. dotIndex 	 = 0xFF;
	}





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
	UINT8 i;  

	// Check for max fields											
	if(ssd.fieldCount > ssd.noOfFields )
		return 0xFF;

	// Setting buffer index based on previous field digits
	if( ssd.fieldCount > 0)
	{

		for(i = ssd.fieldCount ; i > 0; i--)
		{
			ssd.fields[ssd.fieldCount].bufferIndex += ssd.fields[i-1].digits;	//caculation to get the buffer index of SSD buffer
		}
	}
	else
		ssd.fields[ssd.fieldCount].bufferIndex = 0;


	//Check for bufferIndex is greater than MAX_DIGITS (noOfDigits)
	if(ssd.fields[ssd.fieldCount].bufferIndex >= ssd.noOfDigits )
	{
		ssd.fields[ssd.fieldCount].bufferIndex = 0;
		return 0xFF;	
	}

	ssd.fields[ssd.fieldCount].ID 		= ssd.fieldCount;						//field number
	ssd.fields[ssd.fieldCount].digits 	= digits;								//no of digits of that field
	ssd.fields[ssd.fieldCount].blink	=  STATIC ;								//field digit status
	ssd.fields[ssd.fieldCount].dotIndex = 0xFF;									//field dot status		

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
			ssd.buffer[ssd.fields[field_ID].bufferIndex + i] = SEVENSEGMENT[10];
		}
		else
		{
			ssd.buffer[ssd.fields[field_ID].bufferIndex + i] = SEVENSEGMENT[buffer[i] - '0'];
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
			ssd.buffer[ssd.fields[field_ID].bufferIndex + (index + i)] = SEVENSEGMENT[10];
		}
		else
		{
			ssd.buffer[ssd.fields[field_ID].bufferIndex + (index + i)] = SEVENSEGMENT[buffer[index + i] - '0'];
		}
	}
	return SUCCESS;

}



/*------------------------------------------------------------------------------
*  UINT8 SSD_Test(UINT8 from, UINT8 digits )
*
* Pre-Condition - SSD module must be initialized successfully with a call to SSD_Init
*
* Input : 
*           from - starting index of digits to be tested.
*           digits - No. of digits to be tested must be < MAX_DIGITS
*
* return value: True  	- On Success
*                      False - On failure .
* 
* 
*------------------------------------------------------------------------------*/
UINT8 SSD_Test(UINT8 from, UINT8 digits )
{
	UINT8 i,j,k;

	if( digits > ssd.noOfDigits )	//check limits 
		return FAILURE;


	for(j = from; j < digits ; j++)
	{

		for( i = 0; i < 11 ; i++)
		{
			for(k = 0; k < ssd.noOfDigits; k++)
			{
				ssd.dataBuffer[k] = SEVENSEGMENT[10] ;
				ssd.dataBuffer[j] = SEVENSEGMENT[i] ;

				SSD_Refresh();
				if( j == (ssd.digitIndex - 1))
					DelayMs(200);

			}


		}
		

	}

	return SUCCESS;
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
	UINT8 i = 0 ;
	UINT8 multiplier = 0;
	if(ssd.commonCathode == TRUE)
	{
		while(ssd.digitPort[i] != 0)
		{
			*ssd.digitPort[i] = 0xFF;
			i++;
		}

	
		*ssd.dataPort = ~ssd.dataBuffer[ssd.digitIndex];
	
		multiplier = ssd.digitIndex >> 3;

		*ssd.digitPort[multiplier] = ~(shift<< (ssd.digitIndex -(multiplier << 3)) );

	}
	else
	{

		for( i = 0; i < MAX_DIGITPORT ; i++)
		{
			*ssd.digitPort[i] = ~(0xFF);
		}
	
		Delay10us(1);
	
		*ssd.dataPort = ssd.dataBuffer[ssd.digitIndex];

		multiplier = ssd.digitIndex >> 3;

		*ssd.digitPort[i] = (shift -(multiplier << 3));
	}
		ssd.digitIndex++;
	
		if(ssd.digitIndex > ssd.noOfDigits)
		{
			ssd.digitIndex = 0;
		}
		Delay10us(1);

	

}



/*------------------------------------------------------------------------------
*  void SSD_Task(void )
*
* Function to handle Field configurations 
* 
* Input : none 
* return value: none.
* 
*------------------------------------------------------------------------------*/
void SSD_Task(void)
{
UINT8 i , j ;
UINT8 data;

	for(i = 0 ; i < ssd.noOfFields ; i++ )
	{
		switch(ssd.fields[i].blink)
		{
			case STATIC :
				for( j = 0 ; j < ssd.fields[i].digits; j++ )
				{
					ssd.dataBuffer[ssd.fields[i].bufferIndex + j] = ssd.buffer[ssd.fields[i].bufferIndex + j];
				}
			break;
	
			case BLINK:
	
				ssd.fields[i].blinkCount++;
	
				if( ssd.fields[i].blinkCount >= ssd.fields[i].blinkPeriod )
				{
	
					for( j = 0 ; j < ssd.fields[i].digits; j++ )
					{
						if (ssd.dataBuffer[ssd.fields[i].bufferIndex + j] == ssd.buffer[ssd.fields[i].bufferIndex + j] )
								ssd.dataBuffer[ssd.fields[i].bufferIndex + j] = 0x00;
		
						else
								ssd.dataBuffer[ssd.fields[i].bufferIndex + j] = ssd.buffer[ssd.fields[i].bufferIndex + j];
					}
					ssd.fields[i].blinkCount = 0;
				}

			break;
	
			default:
			break;
		}


			if(ssd.fields[i].dotIndex != 0xFF)
			{
				//data = ssd.buffer[ssd.fields[i].bufferIndex + ssd.fields[i].dotIndex ] ;
				ssd.buffer[ssd.fields[i].bufferIndex + ssd.fields[i].dotIndex ]  |= 0X80;
			}

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
	ssd.fields[field_ID].blinkPeriod = blinkPeriod / DISPLAY_REFRESH_PERIOD;	//convert period in milliseconds to period in count
	ssd.fields[field_ID].blinkCount = 0;										//reset counter
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
	
//	ssd.dispBuffer = ssd.buffer[STATIC]; //set current display buffer to data buffer
	ssd.fields[field_ID].blink = STATIC;							   //set static mode

	result = TRUE;
	return result;
}


/*------------------------------------------------------------------------------
* BOOL SSD_DotOn( UINT8 field_ID , UINT8 index)
*
* Function to turn on dot in the field.
* 
* 
* Input :          filed_ID   - ID of Field created by call to SSD_CreateField
*	           dot index. - must be  0xFF to turn off  all dots of the  field
*			      0  to field Length - 1 , as per application
* return value: True On Success
*                      False  On failure .
*------------------------------------------------------------------------------*/
BOOL SSD_DotOn( UINT8 field_ID , UINT8 index)
{
	UINT8 result = FALSE;
	
	if ( (index > ssd.fields[field_ID].digits)  )
		return result;
	
	ssd.fields[field_ID].dotIndex = index;				

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


