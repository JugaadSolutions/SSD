#include "ssd.h"




typedef struct _FIELDS
{
	UINT8 ID;
	UINT8 buffer[NO_OF_DIGITS];
	UINT8 UpdateStatus;
}FIELDS;


typedef struct _APP
{
	FIELDS field[NO_OF_FIELDS];
}APP;


void APP_Init(void);
void APP_Task(void);
