#include "ssd.h"




typedef struct _FIELDS
{
	UINT8 ID;
	UINT8 buffer[MAX_DIGITS];
	UINT8 UpdateStatus;
}FIELDS;


typedef struct _APP
{
	FIELDS field[MAX_FIELDS];
}APP;


void APP_Init(void);
void APP_Task(void);
