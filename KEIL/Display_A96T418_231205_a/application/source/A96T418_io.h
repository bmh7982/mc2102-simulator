/*
 *******************************************************************************
 * @file    A96T418.h
 * @date    2023/09/12
 *******************************************************************************
 */

#include <stdio.h>
#include <string.h>

#include "..\Common\A96T418.h" 
#include "..\Common\common.h"
#include "a96T418_gpio.h"

#ifndef _A96T418_IO_PORT_H_
#define _A96T418_IO_PORT_H_

//----------------------------------------------------------
// Port 
//+----+------------------+---+-----+------------------------------------+
//|Pin |Port 		      |I/O| Val |         Functional Description     |
//|----+------------------+---+-----+------------------------------------+
//|  1 | VDD			  | + |  -  | VCC                                |
//|  2 | VSS 			  | - |  -  | GND                                |
//|----+------------------+---+-----+------------------------------------+

//+----+---+--------------+---+---+---+---+-----------------------
//|PIN |P0 | Name 	      |IO |PU |OD |VAL| Functional Description 
//+----+---+--------------+---+---+---+---+-----------------------
//| 19 |P07|KEY_HOT	      | 1 | 0 | 0 | 0 |
//| 20 |P06|KEY_PWR_SAVING| 1 | 0 | 0 | 0 |
//| 21 |P05|LED_1L  	  | 1 | 0 | 0 | 0 |
//| 22 |P04|LED_COCK1	  | 1 | 0 | 0 | 0 |
//+----+---+--------------+---+---+---+---+-----------------------
//| 23 |P03|LED_COCK2	  | 1 | 0 | 0 | 0 |
//| 24 |P02|DSCL  		  | 0 | 0 | 0 | 0 |
//| 25 |P01|DSDA    	  | 0 | 0 | 0 | 0 |
//| 26 |P00|LED_COCK3	  | 1 | 0 | 0 | 0 | 
//+----+---+--------------+---+---+---+---+-----------------------

#define  P0IO_VAL _1111_1111	//0xFF : P0 Direction Register					/ 0:input     , 1:output
#define  P0PU_VAL _0001_0000	//0x00 : P0 Pull-up Resistor Selection Register / 0:Disable   , 1:Enable
#define  P0OD_VAL _0000_0000	//0x00 : P0 Open-drain Selectrion Register		/ 0:push-pull , 1:Open-drain
#define  P0_VAL   _0011_1001	//0x00 : P0 Data Register						/ I/O Data

//-----------------------------------------------------------

#define LED_1L_on()	do{P05=0;}while(0)		//#define LED_PURIFIDER_on( ){Port_SetOutputLowpin (PORT2,PIN4);}    //
#define LED_1L_off()do{P05=1;}while(0)		//#define LED_PURIFIDER_off(){Port_SetOutputHighpin(PORT2,PIN4);}    //
#define LED_1L  	   P05

#define LED_COCK1_on() do{P04=0;}while(0)	//{Port_SetOutputLowpin(PORT0,PIN4);}
#define LED_COCK1_off()do{P04=1;}while(0)	//{Port_SetOutputHighpin (PORT0,PIN4);}
#define LED_COCK1       P04

#define LED_COCK2_on() do{P03=0;}while(0)	//{Port_SetOutputLowpin(PORT0,PIN3);}
#define LED_COCK2_off()do{P03=1;}while(0)	//{Port_SetOutputHighpin (PORT0,PIN3);}
#define LED_COCK2       P03

#define LED_COCK3_on() do{P00=0;}while(0)	//{Port_SetOutputLowpin(PORT0,PIN0);}
#define LED_COCK3_off()do{P00=1;}while(0)	//{Port_SetOutputHighpin (PORT0,PIN0);}
#define LED_COCK3       P00

//-----------------------------------------------------------
// P0FSRH (Port 0 Function Selection High Register): D3H
//-----------------------------------------------------------
// b7.6: P07 Function Select : 00: IO, 01: Reserved, 10:AN3, 11:PWM5O/T5O
// b5.4: P06 Function Select : 00: IO, 01: EC3     , 10:AN2, 11:PWM4O/T4O
// b3.2: P05 Function Select : 00: IO, 01: Reserved, 10:AN1, 11:PWM3O/T3O
// b1.0: P04 Function Select : 00: IO, 01: Reserved, 10:AN0, 11:SS0
//-----------------------------------------------------------
#define P0FSRH_VAL    _0000_0000
//-----------------------------------------------------------
// P0FSRL (Port 0 Function Selection Low Register): D2H
//-----------------------------------------------------------
// b7.6: P03 Function Select : 00: IO, 01: BUZ0, 				 10:AN7/AVREF,11:SCK0
// b5.4: P02 Function Select : 00: IO, 01: PWM3O/T3O(P02 OUTPUT),10:Reserved, 11:TXD0/MOSI0/SDA0
// b3.2: P01 Function Select : 00: IO, 01: T3Oerved, 			 10:Reserved, 11:RXD0/MISO0/SCL0
// b1.0: P00 Function Select : 00: IO, 01: Reserved,  			 10:Reserved, 11:RXD1/MOSI1
//-----------------------------------------------------------
#define P0FSRL_VAL    _0000_0000

//+----+---+--------------+---+---+---+---+-----------------------
//|PIN |P0 | Name  		  |IO |PU |OD |VAL| Functional Description 
//+----+---+--------------+---+---+---+---+-----------------------
//| 11 |P17|LED_COLD      | 1 | 0 | 0 | 0 | 
//| 12 |P16|LED_PWR_SAVING| 1 | 0 | 0 | 0 | 
//| 13 |P15|LED_1CUP      | 1 | 0 | 0 | 0 | 
//| 14 |P14|LED_2CUP	  | 1 | 0 | 0 | 0 |
//+----+---+--------------+---+---+---+---+-----------------------
//| 15 |P13|KEY_COCK      | 0 | 0 | 0 | 0 |
//| 16 |P12|KEY_AMOUNT	  | 1 | 0 | 0 | 0 |
//| 17 |P11|KEY_COLD	  | 1 | 0 | 0 | 0 |
//| 18 |P10|KEY_ROOM	  | 1 | 0 | 0 | 0 | 
//+----+---+--------------+---+---+---+---+-----------------------

#define  P1IO_VAL _1111_0111	//0xE8 : P0 Direction Register					/ 0:input, 1: output
#define  P1PU_VAL _0000_0000	//0x00 : P0 Pull-up Resistor Selection Register / 0:Disable   , 1:Enable
#define  P1OD_VAL _0000_0000	//0x00 : P0 Open-drain Selectrion Register		/ 0:push-pull , 1:Open-drain
#define  P1_VAL   _1111_0000	//0x00 : P0 Data Register						/ I/O Data

//-----------------------------------------------------------
#define IS_COCK()   ((P1 & 0x08) ? 1:0)			//참이면 1, 거짓이면 0


#define LED_COLD_on() do{P17=0;}while(0)		//#define LED_PURIFIDER_on(){Port_SetOutputLowpin(PORT1,PIN7);}		//
#define LED_COLD_off()do{P17=1;}while(0)		//#define LED_PURIFIDER_off(){Port_SetOutputHighpin (PORT1,PIN7);}	//
#define LED_COLD		 P17

#define LED_PWR_SAVING_on() do{P16=0;}while(0)	//{Port_SetOutputLowpin(PORT1,PIN6);}
#define LED_PWR_SAVING_off()do{P16=1;}while(0)	//{Port_SetOutputHighpin(PORT1,PIN6);}
#define LED_PWR_SAVING       P16

#define LED_1CUP_on() do{P15=0;}while(0)		//{Port_SetOutputLowpin(PORT1,PIN5);}
#define LED_1CUP_off()do{P15=1;}while(0)		//{Port_SetOutputHighpin(PORT1,PIN5);}
#define LED_1CUP       P15

#define LED_2CUP_on() do{P14=0;}while(0)		//{Port_SetOutputLowpin(PORT1,PIN4);}
#define LED_2CUP_off()do{P14=1;}while(0)		//{Port_SetOutputHighpin (PORT1,PIN4);}
#define LED_2CUP       P14

#define LED_COCK_on() do{P13=0;}while(0)		//{Port_SetOutputLowpin(PORT1,PIN3);}
#define LED_COCK_off()do{P13=1;}while(0)		//{Port_SetOutputHighpin (PORT1,PIN3);}
#define LED_COCK       P13

//-----------------------------------------------------------
// P1FSRH (Port 1 Function Selection High Register): D5H
//-----------------------------------------------------------
// b7.6: P17 Function Select : 00: IO, 01: Reserved, 10:Reserved, 11:TXD1/MOSI1
// b5.4: P16 Function Select : 00: IO, 01: Reserved, 10:Reserved, 11:RXD1/MISO1
// b3.2: P15 Function Select : 00: IO, 01: Reserved, 10:Reserved, 11:SCK1
// b1.0: P14 Function Select : 00: IO, 01: Reserved, 10:Reserved, 11:SS1
//-----------------------------------------------------------
#define P1FSRH_VAL    _0000_0000
//-----------------------------------------------------------
// P1FSRL (Port 1 Function Selection Low Register): D4H
//-----------------------------------------------------------
// b7.6: P13 Function Select : 00: IO, 01: Reserved, 10:Reserved, 11:Reserved
// b5.4: P12 Function Select : 00: IO, 01: Reserved, 10:AN6,	  11:T20/PWM20
// b3.2: P11 Function Select : 00: IO, 01: T3Oerved, 10:AN5, 	  11:TXD0/MOSI0/SDA0
// b1.0: P10 Function Select : 00: IO, 01: Reserved, 10:AN4,	  11:RXD0/MISO0/SCL0
//-----------------------------------------------------------
#define P1FSRL_VAL    _0000_0000

//+----+---+-----------------+---+---+---+---+--------------------------------------
//|PIN |P0 | Name            |IO |PU |OD |VAL| Functional Description 
//+----+---+-----------------+---+---+---+---+--------------------------------------
//| 03 |P27|DIO              | 1 | 0 | 0 | 0 | 
//| 04 |P26|CLK              | 0 | 0 | 0 | 0 | 
//| 05 |P25|STB              | 0 | 0 | 0 | 0 | 
//| 06 |P24|LED_PURIFIER     | 1 | 0 | 0 | 0 | 
//+----+---+-----------------+---+---+---+---+--------------------------------------
//| 07 |P23|LED_HOT          | 1 | 0 | 0 | 0 | 
//| 08 |P22|LED_HOT_LOCK     | 1 | 0 | 0 | 0 | 
//| 09 |P21|LED_WATER_SUPPLY | 1 | 0 | 0 | 0 |
//| 10 |P20|LED_UV_CLEAN     | 1 | 0 | 0 | 0 | 
//+----+---+-----------------+---+---+---+---+--------------------------------------

#define  P2IO_VAL _0001_1111	//0x1F : P0 Direction Register					/ 0:input, 1: output
#define  P2PU_VAL _0000_0000	//0x00 : P0 Pull-up Resistor Selection Register / 0: 
#define  P2OD_VAL _0000_0000	//0x00 : P0 Open-drain Selectrion Register		/ 0:
#define  P2_VAL   _0001_1111	//0x1F : P0 Data Register						/ I/O Data

//-----------------------------------------------------------
#define IS_STB()   (P25)              //참이면 1, 거짓이면 0//#define IS_STB()   ((P2 & 0x20) ? 1:0)            //참이면 1, 거짓이면 0//
#define IS_CLK()   (P26)              //참이면 1, 거짓이면 0//#define IS_CLK()   ((P2 & 0x40) ? 1:0)            //참이면 1, 거짓이면 0//
#define IS_DIO()   (P27)              //참이면 1, 거짓이면 0//#define IS_DIO()   ((P2 & 0x80) ? 1:0)           //참이면 1, 거짓이면 0//

#define LED_PURIFIDER_on() do{P24=0;}while(0)		//#define LED_PURIFIDER_on(){Port_SetOutputLowpin(PORT2,PIN4);}		//
#define LED_PURIFIDER_off()do{P24=1;}while(0)		//#define LED_PURIFIDER_off(){Port_SetOutputHighpin (PORT2,PIN4);}	//
#define LED_PURIFIDER		 P24

#define LED_HOT_on() do{P23=0;}while(0)				//{Port_SetOutputLowpin(PORT2,PIN3);}
#define LED_HOT_off()do{P23=1;}while(0)				//{Port_SetOutputHighpin(PORT2,PIN3);}
#define LED_HOT       P23

#define LED_HOT_LOCK_on() do{P22=0;}while(0)		//{Port_SetOutputLowpin(PORT2,PIN2);}
#define LED_HOT_LOCK_off()do{P22=1;}while(0)		//{Port_SetOutputHighpin(PORT2,PIN2);}
#define LED_HOT_LOCK       P22

#define LED_WATER_SUPPLY_on() do{P21=0;}while(0)	//{Port_SetOutputLowpin(PORT2,PIN1);}
#define LED_WATER_SUPPLY_off()do{P21=1;}while(0)	//{Port_SetOutputHighpin (PORT2,PIN1);}
#define LED_WATER_SUPPLY       P21

#define LED_UV_CLEAN_on() do{P20=0;}while(0)		//{Port_SetOutputLowpin(PORT2,PIN0);}
#define LED_UV_CLEAN_off()do{P20=1;}while(0)		//{Port_SetOutputHighpin (PORT2,PIN0);}
#define LED_UV_CLEAN       P20

//-----------------------------------------------------------
// P2FSRH (Port 2 Function Selection High Register): D7H
//-----------------------------------------------------------
// b7.6: P27 Function Select : 00: IO, 01: SXIN, 	 10:T0O/PWM0O, 11:Reserved
// b5.4: P26 Function Select : 00: IO, 01: XOUT, 	 10:Reserved,  11:Reserved
// b3.2: P25 Function Select : 00: IO, 01: EC0, 	 10:Reserved,  11:Reserved
// b1.0: P24 Function Select : 00: IO, 01: Reserved, 10:Reserved,  11:Reserved
//-----------------------------------------------------------
#define P2FSRH_VAL    _0000_0000
//-----------------------------------------------------------
// P2FSRL (Port 2 Function Selection Low Register): D6H
//-----------------------------------------------------------
// b7.6: P23 Function Select : 00: IO, 01: EC1,      10:Reserved, 11:Reserved
// b5.4: P22 Function Select : 00: IO, 01: Reserved, 10:Reserved, 11:Reserved
// b3.2: P21 Function Select : 00: IO, 01: Reserved, 10:Reserved, 11:Reserved
// b1.0: P20 Function Select : 00: IO, 01: Reserved, 10:Reserved, 11:Reserved
//-----------------------------------------------------------
#define P2FSRL_VAL    _0000_0000

//+----+---+---------+---+---+---+--------------------------------------
//|PIN |P0 | Name    |IO |PU |VAL| Functional Description 
//+----+---+---------+---+---+---+--------------------------------------
//| 27 |P31|LED_COCK4| 1 | 0 | 0 | 
//| 28 |P30|         | 1 | 0 | 0 | 
//+----+---+---------+---+---+---+--------------------------------------

#define  P3IO_VAL _1111_1111	//0xFF : P0 Direction Register					/ 0:input,   1:output
#define  P3PU_VAL _0000_0000	//0x00 : P0 Pull-up Resistor Selection Register / 0:Disable, 1:Enable 
#define  P3_VAL   _0000_0010	//0x00 : P0 Data Register						/ I/O Data

//-----------------------------------------------------------

#define LED_COCK4_on() do{P31=0;}while(0)	//{Port_SetOutputLowpin(PORT3,PIN1);}
#define LED_COCK4_off()do{P31=1;}while(0)	//{Port_SetOutputHighpin(PORT3,PIN1);}
#define LED_COCK4       P31

//-----------------------------------------------------------
// P3FSR (Port 3 Function Selection Register): EEH
//-----------------------------------------------------------
// b3.2: P31 Function Select : 00: IO, 01: Reserved, 10:Reserved,  11:RXD1/MISO1
// b1.0: P30 Function Select : 00: IO, 01: Reserved, 10:Reserved,  11:Reserved
//-----------------------------------------------------------
#define P3FSR_VAL    _0000_0000

//--------------------------------------------------------------------------------
// P0DB (P0 De-bounce Enable Register): DEH
//--------------------------------------------------------------------------------
// b7.6: De-bounce Clock  : 00: fx/1, 01: fx/4, 10:fx/4096, 11:LSI(128KHz)
// b5  : -
// b4  : De-bounce of P07 :  0: Disable, 1: Enable
// b3  : De-bounce of P06 :  0: Disable, 1: Enable
// b2  : De-bounce of P05 :  0: Disable, 1: Enable
// b1  : De-bounce of P04 :  0: Disable, 1: Enable
// b0  : De-bounce of P03 :  0: Disable, 1: Enable
//--------------------------------------------------------------------------------
#define P0DB_VAL  _0000_0000    // 0x00 : debounce Enable

//--------------------------------------------------------------------------------
// P123DB (P1/P2/P3 De-bounce Enable Register): DFH
//--------------------------------------------------------------------------------
// b4  : De-bounce of P31 :  0: Disable, 01: Enable
// b3  : De-bounce of P26 :  0: Disable, 01: Enable
// b2  : De-bounce of P25 :  0: Disable, 01: Enable
// b1  : De-bounce of P12 :  0: Disable, 01: Enable
// b0  : De-bounce of P11 :  0: Disable, 01: Enable
//--------------------------------------------------------------------------------
#define P123DB_VAL  _0000_0000    // 0x00 : debounce Enable

#endif  //_A96T418_IO_PORT_H_
