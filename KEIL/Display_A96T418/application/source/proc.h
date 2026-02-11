/*
 *******************************************************************************
 * @file    A96T418.h
 * @date    2023/09/12
 *******************************************************************************
 */
 
#ifndef _PROC_H_
#define _PROC_H_

#include "typedef.h"

#define KEY_PWR_SAVING	0x01
#define KEY_HOT 		0x02
#define KEY_ROOM  		0x04
#define KEY_COLD  		0x08
#define KEY_AMOUNT		0x10

#define KEY_ALL			0x1F

#define FADDR 1
#define IAADHBW 0

extern bit b_stb;
extern bit b_rksd;
extern bit b_timer1;
extern unsigned int key_cnt;
extern unsigned char Data;
extern unsigned char DataOUT;
extern unsigned char DOUT[6];

extern unsigned char GRID;
extern unsigned char command;
extern unsigned char doutcnt;
extern unsigned char doutcnt2;
extern unsigned char SEGMENTS;
extern unsigned char DataOUTcnt;
extern unsigned char AdderssMODE;
extern unsigned char ADDR[14];
extern unsigned char DIN[14];
extern unsigned int  DIMM;
extern const int DIMMING[];	//Dimming Pulse -  ?   
extern unsigned char Dimming_cnt; 

typedef enum {
	Display_OFF = 0,
	Display_ON = 1,
} display_t;
extern display_t Display_stat;

typedef enum {
	WRITE_MODE = 0,
	READ_MODE  = 1,
} WRMODE_t;
extern WRMODE_t wrmode;

typedef enum {
	ADDRESS0 = 0,
	ADDRESS1 = 1,
	ADDRESS2 = 2,
	ADDRESS3 = 3,
	ADDRESS4 = 4,
	ADDRESS5 = 5,
	ADDRESS6 = 6,
	ADDRESS7 = 7,
	ADDRESS8 = 8,
	ADDRESS9 = 9,
	ADDRESSA = 10,
	ADDRESSB = 11,
	ADDRESSC = 12,
	ADDRESSD = 13,
} Address_t;
extern Address_t Address;

void proc(void);

#endif /* _PROC_H_ */