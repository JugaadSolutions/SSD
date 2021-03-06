#ifndef CONFIG_H
#define CONFIG_H

/*
*------------------------------------------------------------------------------
* config.h
*
*/


#define DEVICE_ADDRESS			0xFA

/*----------------------------------------
*	BOARD MOULE CONFIG
*----------------------------------------*/


#define MHz_32					(32000000UL)	// Hz
#define MHz_16					(16000000UL)	// Hz
#define MHz_8					(8000000UL)	// Hz

#define PORT_A			0xF80
#define PORT_B			0xF81
#define PORT_C			0xF82
#define PORT_D			0xF83
#define PORT_E			0xF84
#define PORT_F			0xF85
#define PORT_H			0xF87
#define PORT_J			0xF88

/*----------------------------------------
*	OSCILLATOR CONFIG
*----------------------------------------*/

#define SYSTEM_CLOCK			(MHz_32)	


/*----------------------------------------
*	TIMER CONFIG
*----------------------------------------*/
#define FULLSCALE_16BIT				(65535)
#define TIMER0_TIMEOUT_DURATION 	(1000UL)			//1ms
#define TIMESTAMP_DURATION 			(200)


/*----------------------------------------
*	USART Configuration
*----------------------------------------*/
#define ACTIVE_USARTS		2
//#define UART2_ACTIVE
#define UART1_BAUD			19200
#define UART2_BAUD			19200
//#define PASS_THROUGH
#define UART_TEST

/*----------------------------------------
*	COM module configuration
*----------------------------------------*/

//#define __NO_CHECKSUM__
#define __BCC_XOR__
#define __RESPONSE_ENABLED__
//#define __LOOP_BACK__
#define BROADCAST_ADDRESS		0xFF
#define CMD_SOP	0xAA
#define CMD_EOP 0xBB
#define RESP_SOP	0xCC
#define RESP_EOP	0xDD


enum
{
	CMD_PACKET_SIZE = 30,
	RESP_PACKET_SIZE = 30
};

#define 	RX_PACKET_SIZE		(60)	
#define 	TX_PACKET_SIZE		(60)


/*----------------------------------------
*	Keypad Configurations
*----------------------------------------*/

//#define __FACTORY_CONFIGURATION__
//#define __SIMULATION__

//RTC CONFIGURATION
//#define TIME_DEBUG

//#define RTC_DS1307
#define RTC_DS3232

//#define __SET_RTC__


//APPLICATION CONFIGURATION
#define MSG_MAX_CHARS 60
#define MAX_TRANSITIONS 20

//#define __ERROR_DEBUG__
/*----------------------------------------
*	SSD module configuration
*----------------------------------------*/

#define COMMON_CATHODE 1
//#define SSD_TEST
#define NO_OF_DIGITS 16
#define NO_OF_FIELDS 4

/*----------------------------------------
*	APP CONFIGURATION
*----------------------------------------*/




/*
*------------------------------------------------------------------------------
* Public Data Types
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Variables (extern)
*------------------------------------------------------------------------------
*/

/*
*------------------------------------------------------------------------------
* Public Constants (extern)
*------------------------------------------------------------------------------
*/


/*
*------------------------------------------------------------------------------
* Public Function Prototypes (extern)
*------------------------------------------------------------------------------
*/

#endif
/*
*  End of config.h
*/



