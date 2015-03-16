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


