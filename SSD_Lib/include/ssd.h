
#ifndef SSD_H
#define SSD_H

/*
*------------------------------------------------------------------------------
* ssd.h
*
*/

#include "config.h"
#include "utilities.h"
#include "typedefs.h"

	
/*
*------------------------------------------------------------------------------
* SSD - the Seven Segement Display structure. 
*------------------------------------------------------------------------------
*/

typedef struct _Field 
{

	UINT8	 ID;				// To Identify the field
	UINT8	 bufferIndex;		//Index of digit display buffer, corresponding to field data
	UINT8    digits;			// No. of digits in the field
	BOOL 	 blink;				// Blink Flag
	UINT16	 blinkCount;		//counter to be used in blink mode
	UINT16	 blinkPeriod;		//blink period represented in counts
	UINT8 	 dotIndex ;			//Values [0 - length -1, 0xFF]
}Field;


typedef struct _SSD
{
	Field    	fields[MAX_FIELDS];   		// contains field information
	UINT8	 	fieldCount;				// Stores field count[1 - MAX_FIELDS]
	UINT8 	 	buffer		[MAX_DIGITS];		//stores the data of the fields
	UINT8	 	dataBuffer[MAX_DIGITS];	//stores the data going to be display
	UINT8 	 	digitIndex ;				//to point next data in buffer
	UINT8	 	noOfDigits;
	UINT8	 	noOfFields;
	far UINT8*  digitPort[MAX_DIGITPORT];			
	far UINT8*  dataPort;
	UINT8       commonCathode;
}SSD;



typedef enum
{
	STATIC = 0,
	BLINK 
}SSD_MODE;

#define DISPLAY_REFRESH_PERIOD	2

/*------------------------------------------------------------------------------
Public Function declarations:
*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
* void  SSD_Init( UINT8* digitPort_1, UINT8* digitPort_2, UINT8* digitPort_3, UINT8* digitPort_4,
				  UINT8* dataPort, UINT8 noOfDigits, UINT8 noOfFields, UINT8 commonCathode)
*
* Function to initialize the ssd fields. All variables in the field will be 
* initialize to zero, except blink index.
* 
* Input : 	digitPort_1 - port for control digit 
			digitPort_2 - port for control digit 
			digitPort_3 - port for control digit 
			digitPort_4 -  port for control digit 
			dataPort    - port for seven segment data
			noOfDigits	- max_number of digit used by application
			noOfFields 	- max_number of fields used by application 
			commonCathode	 - 1 -  common cathode display
   							   0 -  common anode display
* return value: none.
* 
*------------------------------------------------------------------------------*/
void  SSD_Init( UINT8* digitPort_1,UINT8* digitPort_2,UINT8* digitPort_3,UINT8* digitPort_4,UINT8* dataPort,
				UINT8 noOfDigits, UINT8 noOfFields , UINT8 commonCathode);

/*------------------------------------------------------------------------------
* UINT8 SSD_CreateField(UINT8 digits )

*
* Function to initialize the individual fields
* 
* Initializes field length to the value as per parameter  passed.	 
* Input : digits - Digits must be  < MAX_DIGITS and non zero value.
* return value: FIeld ID   - On Success
*                      0xFF	   - On failure .
* 
*------------------------------------------------------------------------------*/

UINT8 SSD_CreateField(UINT8 digits);


/*------------------------------------------------------------------------------
*BOOL SSD_UpdateField(UINT8 field_ID, UINT8 *buffer);
*
* Function to update field content to in display buffer.
* 
* 
* Input : field_ID - ID of Field of which data to be updated.
*         buffer - pointer to buffer containing Data to be displayed in ASCII Format , must be non *               NULL.
*
* return value: True  - On Success
*               False - On failure .
* 
*------------------------------------------------------------------------------*/
BOOL SSD_UpdateField(UINT8 filed_ID, UINT8 *buffer);




/*------------------------------------------------------------------------------
* BOOL SSD_UpdateFieldpartial(UINT8 field_ID , UINT8 *buffer, UINT8 index , UINT8  digits);
* Function to update field content in display buffer.
* 
* 
* Input : field_ID  - ID of Field of which data to be updated.
*         buffer    -  pointer to buffer containing Data to be displayed in ASCII Format , must be non *               	     NULL.
*		  index      - field index from which data to be updated.
*		  no_of_digit - number of   digits to be updated.
* return value: True On Success
*               False - On failure .
* 
*------------------------------------------------------------------------------*/
BOOL SSD_UpdateFieldpartial(UINT8 field_ID,UINT8 *buffer, UINT8 index , UINT8 no_of_digit);


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
BOOL SSD_DotOn( UINT8 field_ID , UINT8 index);


/*------------------------------------------------------------------------------
*  BOOL SSD_BlinkOn( UINT8 field_ID )
*
* Function to turn ON blinking feature
* 
* 
* Input :    filed_ID   - ID of Field created by call to SSD_CreateField
			 blinkPeroid -  the blinking time of that field
*  
* return value: True On Success
*                      False - On failure .
* 
*------------------------------------------------------------------------------*/
BOOL SSD_BlinkOn( UINT8 field_ID,UINT16 blinkPeriod );



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
BOOL SSD_BlinkOff( UINT8 field_ID );


/*------------------------------------------------------------------------------
*  void SSD_Task(void )
*
* Function to handle Field configurations 
* 
* Input : none 
* return value: none.
* 
*------------------------------------------------------------------------------*/
void SSD_Task(void);


/*------------------------------------------------------------------------------
*  void SSD_Refresh(void )
*
* ISR to refresh Display
* 
* Input : none 
* return value: none.
* 
*------------------------------------------------------------------------------*/
void SSD_Refresh(void);


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
UINT8 SSD_Test(UINT8 from, UINT8 digits );


/*------------------------------------------------------------------------------
*  UINT8 SSD_Clear(UINT8 field_ID )
*
* clear the SSD  buffer
* 
* Input : field_ID - Field ID of which data to be cleared. 
* return value: True - on success
* 		False - on failure
*------------------------------------------------------------------------------*/
UINT8 SSD_Clear(UINT8 field_ID);


#endif

/*
* -------------------------------
* End of SSD.H
*--------------------------------
*/
