
#ifndef SSD_H
#define SSD_H

/*
*------------------------------------------------------------------------------
* ssd.h
*
*/

#include "config.h"
#include "board.h"
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
	UINT8 	 dotIndex ;			//Values [0 - length -1, 0xFF]
}Field;


typedef struct _SSD
{
	Field    fields[MAX_FIELDS];   		// contains field information
	UINT8	 fieldCount;				// Stores field count[1 - MAX_FIELDS]
	UINT8 	 buffer[2][MAX_DIGITS];		//stores the data going to be display
	UINT8* 	 dispBuffer; // pointer to current display buffer
	UINT8 	 digitIndex ;				//to point next data in buffer
	UINT16	 blinkCount;				//counter to be used in blink mode
	UINT16	 blinkPeriod;				//blink period represented in counts	
}SSD;



typedef enum
{
	STATIC = 0,
	BLINK 
}SSD_MODE;

/*------------------------------------------------------------------------------
Public Function declarations:
*------------------------------------------------------------------------------*/

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
void  SSD_Init( void );
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

UINT8 SSD_CreateField(UINT8 digits);


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
BOOL SSD_UpdateField(UINT8 filed_ID, UINT8 *buffer);




/*------------------------------------------------------------------------------
* BOOL SSD_UpdateFieldpartial(UINT8 field_ID , UINT8 *buffer, UINT8 index , UINT8  no_of_digit);
* Function to update field content to  in display buffer.
* 
* 
* Input : 
* 	filed_ID  - ID of Field created by call to SSD_CreateField
*          buffer     -  pointer to buffer containing Data to be displayed in ASCII Format , must be non NULL.
*	index      - field index from which data to be updated.
*	no_of_digit - number of   digits to be updated.
* return value: True On Success
*                      False - On failure .
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
*  
* return value: True On Success
*                      False - On failure .
* 
*------------------------------------------------------------------------------*/
BOOL SSD_BlinkOn( UINT8 field_ID );


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
void SSD_Test(UINT8 from, UINT8 digits );


/*------------------------------------------------------------------------------
*  void SSD_Clear(void )
*
* clear the SSD  buffer
* 
* Input : none 
* return value: none.
* 
*------------------------------------------------------------------------------*/
void SSD_Clear(void);



#endif

/*
* -------------------------------
* End of SSD.H
*--------------------------------
*/
