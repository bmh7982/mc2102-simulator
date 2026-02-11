/*
 *******************************************************************************
 * @file    A96T418.h
 * @date    2023/09/12
 *******************************************************************************
 */

#include "A96T418.h" 
#include "common.h"
#include "user_function.h"
#if LED_DRV_EN == 1
#include "led_driver.h"
#endif
#if (UART_ENABLE|I2C_ENABLE)
#include "debug.h"
#endif
#include "touch_lib.h"
#include "user_timer.h"
#include "main.h"
#include "a96T418_wdt.h"
#include "a96T418_bit.h"

#include "proc.h"
#include "A96T418_io.h"

WRMODE_t wrmode;
Address_t Address;
display_t Display_stat;

bit b_stb;
bit b_rksd;
bit b_timer1;
bit key_amount, b_key_amount;
bit key_cold, b_key_cold;
bit key_room, b_key_room;
bit key_hot, b_key_hot;
bit key_pwr_saving, b_key_pwr_saving;
bit key_cock, b_key_cock;

unsigned int  key_cnt;
unsigned char DOUT[6];
unsigned char DataOUT;
unsigned char DataOUTcnt=0;
unsigned char doutcnt;
unsigned char doutcnt2;
unsigned char Data;
unsigned char command;
unsigned char GRID;
unsigned char AdderssMODE;
unsigned char ADDR[14];
unsigned char DIN[14];
unsigned int  DIMM;
unsigned char Dimming_cnt; 
unsigned char SEGMENTS;

//const int DIMMING[] = {56, 52, 48, 44, 40, 16, 8, 4};	//Dimming Pulse - 앞에서 부터 밝기 높은 것.
const int DIMMING[] = {4, 8, 16, 40, 44, 48, 52, 56};	//Dimming Pulse - 앞에서 부터 밝기 높은 것.


void Display_off(void){
	//P0
	LED_COCK3_off();		//P00
	LED_COCK2_off();		//P03
	LED_COCK1_off();		//P04
	LED_1L_off();			//P05
	
	//P1
	LED_2CUP_off();			//P14
	LED_1CUP_off();			//P15
	LED_PWR_SAVING_off();	//P16
	LED_COLD_off();			//P17

	//P2
	LED_UV_CLEAN_off();		//P20
	LED_WATER_SUPPLY_off();	//P21
	LED_HOT_LOCK_off();		//P22
	LED_HOT_off();			//P23
	LED_PURIFIDER_off();	//P24

	//P3
	LED_COCK4_off();		//P31
}

// 사용하지 않는 led 레지스터는 막아놨어요. 
// 필요하신 부분은 사용하시면 될 것 같아요.
void subDisplay(void){
	if(Display_stat==Display_OFF){Display_off(); return;}
	
	if(Dimming_cnt++ <= DIMM){
		if(Dimming_cnt==1){
			if((ADDR[0] & 0x01) == 0x01){}						else{}
			if((ADDR[0] & 0x02) == 0x02){LED_HOT_LOCK_on();}	else{LED_HOT_LOCK_off();}
			if((ADDR[0] & 0x04) == 0x04){LED_HOT_on();}			else{LED_HOT_off();}
			if((ADDR[0] & 0x08) == 0x08){LED_PURIFIDER_on();}	else{LED_PURIFIDER_off();}
			if((ADDR[0] & 0x10) == 0x10){}						else{}
			if((ADDR[0] & 0x20) == 0x20){}						else{}
			if((ADDR[0] & 0x40) == 0x40){}						else{}
			if((ADDR[0] & 0x80) == 0x80){}						else{}
	/*		if((ADDR[1] & 0x01) == 0x01){}
			if((ADDR[1] & 0x02) == 0x02){}
			if((ADDR[1] & 0x04) == 0x04){} 
			if((ADDR[1] & 0x08) == 0x08){}  
			if((ADDR[1] & 0x10) == 0x10){} 
			if((ADDR[1] & 0x20) == 0x20){} */

			if((ADDR[2] & 0x01) == 0x01){LED_COLD_on();}		else{LED_COLD_off();}
			if((ADDR[2] & 0x02) == 0x02){LED_UV_CLEAN_on();}	else{LED_UV_CLEAN_off();}
			if((ADDR[2] & 0x04) == 0x04){}						else{}
			if((ADDR[2] & 0x08) == 0x08){LED_WATER_SUPPLY_on();}else{LED_WATER_SUPPLY_off();}
			if((ADDR[2] & 0x10) == 0x10){}						else{}
			if((ADDR[2] & 0x20) == 0x20){}						else{}
			if((ADDR[2] & 0x40) == 0x40){}						else{}
			if((ADDR[2] & 0x80) == 0x80){}						else{}
			if((ADDR[3] & 0x01) == 0x01){}
/*			if((ADDR[3] & 0x02) == 0x02){}
			if((ADDR[3] & 0x04) == 0x04){} 
			if((ADDR[3] & 0x08) == 0x08){}  
			if((ADDR[3] & 0x10) == 0x10){} 
			if((ADDR[3] & 0x20) == 0x20){} */

			if((ADDR[4] & 0x01) == 0x01){LED_1L_on();}			else{LED_1L_off();}
			if((ADDR[4] & 0x02) == 0x02){LED_2CUP_on();}		else{LED_2CUP_off();}
			if((ADDR[4] & 0x04) == 0x04){LED_1CUP_on();}		else{LED_1CUP_off();}
			if((ADDR[4] & 0x08) == 0x08){LED_PWR_SAVING_on();}	else{LED_PWR_SAVING_off();}
			if((ADDR[4] & 0x10) == 0x10){}						else{}
			if((ADDR[4] & 0x20) == 0x20){}						else{}
			if((ADDR[4] & 0x40) == 0x40){}						else{}
			if((ADDR[4] & 0x80) == 0x80){}						else{}
/*			if((ADDR[5] & 0x01) == 0x01){}
			if((ADDR[5] & 0x02) == 0x02){}
			if((ADDR[5] & 0x04) == 0x04){} 
			if((ADDR[5] & 0x08) == 0x08){}  
			if((ADDR[5] & 0x10) == 0x10){} 
			if((ADDR[5] & 0x20) == 0x20){} */

			if((ADDR[6] & 0x01) == 0x01){LED_COCK1_on();}		else{LED_COCK1_off();}
			if((ADDR[6] & 0x02) == 0x02){LED_COCK2_on();}		else{LED_COCK2_off();}
			if((ADDR[6] & 0x04) == 0x04){LED_COCK3_on();}		else{LED_COCK3_off();}
			if((ADDR[6] & 0x08) == 0x08){LED_COCK4_on();}		else{LED_COCK4_off();}
			if((ADDR[6] & 0x10) == 0x10){}						else{}
			if((ADDR[6] & 0x20) == 0x20){}						else{}
			if((ADDR[6] & 0x40) == 0x40){}						else{}
			if((ADDR[6] & 0x80) == 0x80){}						else{}
/*			if((ADDR[7] & 0x01) == 0x01){}
			if((ADDR[7] & 0x02) == 0x02){}
			if((ADDR[7] & 0x04) == 0x04){} 
			if((ADDR[7] & 0x08) == 0x08){}  
			if((ADDR[7] & 0x10) == 0x10){} 
			if((ADDR[7] & 0x20) == 0x20){} 

			if((ADDR[8] & 0x01) == 0x01){}
			if((ADDR[8] & 0x02) == 0x02){}
			if((ADDR[8] & 0x04) == 0x04){}
			if((ADDR[8] & 0x08) == 0x08){}
			if((ADDR[8] & 0x10) == 0x10){}
			if((ADDR[8] & 0x20) == 0x20){}
			if((ADDR[8] & 0x40) == 0x40){}
			if((ADDR[8] & 0x80) == 0x80){}
			if((ADDR[9] & 0x01) == 0x01){}
			if((ADDR[9] & 0x02) == 0x02){}
			if((ADDR[9] & 0x04) == 0x04){} 
			if((ADDR[9] & 0x08) == 0x08){}  
			if((ADDR[9] & 0x10) == 0x10){} 
			if((ADDR[9] & 0x20) == 0x20){} 

			if((ADDR[10] & 0x01) == 0x01){}
			if((ADDR[10] & 0x02) == 0x02){}
			if((ADDR[10] & 0x04) == 0x04){}
			if((ADDR[10] & 0x08) == 0x08){}
			if((ADDR[10] & 0x10) == 0x10){}
			if((ADDR[10] & 0x20) == 0x20){}
			if((ADDR[10] & 0x40) == 0x40){}
			if((ADDR[10] & 0x80) == 0x80){}
			if((ADDR[11] & 0x01) == 0x01){}
			if((ADDR[11] & 0x02) == 0x02){}
			if((ADDR[11] & 0x04) == 0x04){} 
			if((ADDR[11] & 0x08) == 0x08){}  
			if((ADDR[11] & 0x10) == 0x10){} 
			if((ADDR[11] & 0x20) == 0x20){} 

			if((ADDR[12] & 0x01) == 0x01){}
			if((ADDR[12] & 0x02) == 0x02){}
			if((ADDR[12] & 0x04) == 0x04){}
			if((ADDR[12] & 0x08) == 0x08){}
			if((ADDR[12] & 0x10) == 0x10){}
			if((ADDR[12] & 0x20) == 0x20){}
			if((ADDR[12] & 0x40) == 0x40){}
			if((ADDR[12] & 0x80) == 0x80){}
			if((ADDR[13] & 0x01) == 0x01){}
			if((ADDR[13] & 0x02) == 0x02){}
			if((ADDR[13] & 0x04) == 0x04){} 
			if((ADDR[13] & 0x08) == 0x08){}  
			if((ADDR[13] & 0x10) == 0x10){} 
			if((ADDR[13] & 0x20) == 0x20){} */
		}		
	}
	else{
		Display_off();							//LED off
		
		if(Dimming_cnt>56){Dimming_cnt=0;}		//Dimming cnt 초기화
	}
}

//이 프로그램에서는 command 1의 GRID랑 SEGMENTS는 설저하는 것이 의미가 없다.
void command1(void){
	 if((command & 0x3C) != 0x00){return;}
	 
	 GRID     = (command & 0x03) + 4;
	 SEGMENTS = (command & 0x03) + 7;
}

//Command2는 read, write 상태가 변경될 때 DIO PIN 설정을 변경해 줘야됨.
void command2(void){
	if((command & 0x38) != 0x00){return;}
				
	if((command & 0x04) == 0x04){AdderssMODE = FADDR;}
	else                        {AdderssMODE = IAADHBW;}
		
	if     ((command & 0x03) == 0x00){
		wrmode = WRITE_MODE; 
		Port_SetInputpin(PORT0,PIN5, 0);
	}
	else if((command & 0x03) == 0x02){
		wrmode = READ_MODE; 
		Port_SetOutputpin(PORT0,PIN5, 0);
	}
}

//만약 Addr를 설정하고 Data를 전송한다면 ADDR[0]에 Address를 넣어주면 돼요.
void command3(void){
	if((command & 0x30) == 0x00){
		Address = (command & 0x0F);
		
		memcpy(&ADDR[0], &DIN[1], 13);
	}
}

//Dimming 설정이랑 Display ON/OFF 설정
//Dimming은 초기에 10/16로 설정되어 있음
void command4(void){
	if((command & 0x08) == 0x08){
		Display_stat=Display_ON;
		DIMM = DIMMING[(command & 0x07)];
		Dimming_cnt=0;
	}
	else{
		Display_stat=Display_OFF;
	}
}

int proc_key(void){
	u32	detect_key_chk;
	
	if((key_amount==1)||(key_cold==1)||(key_room==1)||(key_hot==1)||(key_pwr_saving==1)||(key_cock==1)){return 0;}
	
	detect_key_chk = ts.detect_key & KEY_ALL;
	
	if(detect_key_chk == KEY_AMOUNT)	{key_amount=1;}
	if(detect_key_chk == KEY_COLD)		{key_cold=1;}
	if(detect_key_chk == KEY_ROOM)		{key_room=1;}
	if(detect_key_chk == KEY_HOT)		{key_hot=1;}
	if(detect_key_chk == KEY_PWR_SAVING){key_pwr_saving=1;}
	
	if(!(IS_COCK())){key_cock=1;}

//	if(detect_key_chk == 0x00){b_key_amount=0; b_key_cold=0; b_key_room=0; b_key_hot=0; b_key_pwr_saving=0; b_key_cock=0;}

	return 0;
}

void proc(void){
	//key 동작 
	if(bit_key_oper ==1){
		bit_key_oper=0;
		
		proc_key();
		
		//중복 key 사용하실 거면 else if에서 if로 변경하시면 됩니당.
			 if(key_amount)		{key_amount=0;		DOUT[0] |= 0x80; b_rksd=1;}
		else if(key_hot)		{key_hot=0;			DOUT[0] |= 0x40; b_rksd=1;}
		else if(key_cold)		{key_cold=0;		DOUT[1] |= 0x80; b_rksd=1;}
		else if(key_pwr_saving)	{key_pwr_saving=0;	DOUT[1] |= 0x40; b_rksd=1;}
		else if(key_room)		{key_room=0;		DOUT[2] |= 0x80; b_rksd=1;}
		else if(key_cock)		{key_cock=0;		DOUT[2] |= 0x40; b_rksd=1;}
		
	}

	
	if(b_stb==1){
		b_stb=0;
		command = DIN[0];
		switch(command & 0xC0){
			case 0x00: command1(); break;
			case 0x40: command2(); break;
			case 0xc0: command3(); break;
			case 0x80: command4(); break;
		}
	}
	
	//Display 동작 
	if(b_timer1==1){
		b_timer1=0; 
		subDisplay();
	}
}

//##########################################################################
