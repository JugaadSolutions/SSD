#include "app.h"


#pragma idata APP_DATA
APP app = {0};
#pragma idata


void APP_Init(void)
{
	UINT8 i;
	
	for(i = 0; i < MAX_FIELDS ; i++)
	{
		app.field[i].ID = SSD_CreateField(4);
	}
	for(i = 0; i < 4 ; i++)
	{
		app.field[0].buffer[i] = i;
		app.field[1].buffer[i] = (i+6);	
	}	

	app.field[0].UpdateStatus = SSD_UpdateField(app.field[0].ID,app.field[0].buffer);
	app.field[1].UpdateStatus = SSD_UpdateField(app.field[1].ID,app.field[1].buffer);
	
//	SSD_Refresh();
	
}
