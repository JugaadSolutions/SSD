#include "app.h"


#pragma idata	APP_DATA
APP app = {0};
#pragma idata


void APP_Init(void)
{
	UINT8 i ,j;

 	app.field[0].ID = SSD_CreateField(4);
 	app.field[1].ID = SSD_CreateField(4);
 	app.field[2].ID = SSD_CreateField(4);
 	app.field[3].ID = SSD_CreateField(4);

	for(i = 0; i < 4 ; i++)
 	{
		for(j = 0; j < 4; j++)
		{
			app.field[i].buffer[j] = j + '0' ;
		}
	}
	for(i = 0; i < 4 ; i++)
 	{	
		app.field[i].UpdateStatus = SSD_UpdateField(app.field[i].ID , (app.field[i].buffer) );
	}
	
	 SSD_BlinkOn( app.field[1].ID ,10);
	 SSD_BlinkOn( app.field[3].ID ,50);

	 SSD_DotOn( app.field[0].ID , 2);


	
}
