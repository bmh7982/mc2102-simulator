/**
 *******************************************************************************
 * @file        main.c
 * @author      ABOV R&D Division
 * @brief       application "TEST-A96T418-GDN-FUNCTION-A"
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

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

#if (SLIDE_FUNCTION_EN | WHEEL_FUNCTION_EN)
#include "gesture.h"
#endif

#if (I2C_ENABLE == 1)
#include "A96T418_usi_i2c.h"
#include "RegisterMap.h"
#endif

#include "A96T418_io.h"

#include "proc.h"
bit g_i2c_flag = 0;

struct sys_flag g_sys_flag;

//sg추가---------------------------------------------------

unsigned char DataIN;
unsigned char DataINcnt=0;
unsigned char dincnt;

bit bit_key_oper;

uint8_t Data_out;

#define KEY_CNT	100

bit DATA_BIT;


bit b_command;
unsigned char Add;


//======================================================
// interrupt routines
//======================================================
//CLK PIN --> STB가 LOW 일 때 DIN, OUT 하는 거임
//DIN일 때는 CLK가 HIGH 일 때 하는 것이고, DOUT은 CLK가 LOW일 때 하는 거임.
void INT_Ext10() interrupt 0
{
//	int i;
	
//	DI();
	if(IS_STB() == 0){
		if(wrmode == WRITE_MODE){
			if(IS_CLK()){
				DataIN = DataIN >> 1;
				if(IS_DIO()){DataIN |= 0x80;}	//	if(IS_DIO()==0){DataIN |= 0x80;}
				
				DataINcnt++;
				if(DataINcnt >= 8){
					DataINcnt = 0;
					DIN[dincnt] = DataIN;
					dincnt++;
					DataIN = 0;
				}
			}
		}
		else{
			wrmode = WRITE_MODE; Port_SetInputpin(PORT0,PIN5, 0);
/*			if(!IS_CLK()){
				//key scan mode 되고 들어와서 1~6byte까지 전송
				if(b_rksd==1){
					b_rksd=0;
					if(doutcnt <= 5){
						if(doutcnt2 <= 7){
							if(doutcnt2==0){Data = DOUT[doutcnt];}
							if(Data & 0x10){Port_SetOutputHighpin(PORT0,PIN5);}
							else           {Port_SetOutputLowpin (PORT0,PIN5);}
							
							Data = Data<<1;
							
							doutcnt++;
							doutcnt2++;
						}
						if(doutcnt == 6){
							doutcnt=0;
							doutcnt2=0;
							
							for(i=0;i<6;i++){
								DOUT[i]=0x01;
							}
		
							wrmode = READ_MODE; Port_SetInputpin(PORT0,PIN5, 0);
						}
					}
				}
			}*/
		}	
	}
//	EI();
}

// STB PIN
void INT_Ext11() interrupt 1
{
	b_stb=1;

	DataIN = 0x00;
	DataINcnt = 0;		
	dincnt = 0;
	DataOUT = 0;
	DataOUTcnt = 0;	

}

void INT_Timer1() interrupt 14
{
	b_timer1=1;
}

void INT_Timer2() interrupt 15
{
	
	if(KEY_CNT<=key_cnt++){
		key_cnt=0;
		bit_key_oper=1;
	}	
}


/** *******************************************************************
 * @brief       Set the GPIO (as output low)
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void Init_GPIO(void)
{
	P0IO   = P0IO_VAL;    
	P0PU   = P0PU_VAL;
	P0OD   = P0PU_VAL;
	P0DB   = P0DB_VAL;
	P0     = P0_VAL; 
 
	P1IO   = P1IO_VAL;
	P1PU   = P1PU_VAL;
	P1OD   = P1OD_VAL;
	P123DB = P123DB_VAL;
	P1     = P1_VAL; 

	P2IO   = P2IO_VAL;
	P2PU   = P2PU_VAL;
	P2OD   = P2OD_VAL;
	P2     = P2_VAL; 

	P3IO   = P3IO_VAL;
	P3PU   = P3PU_VAL;
	P3     = P3_VAL;

	// Set port functions
	P0FSRH = P0FSRH_VAL;
	P0FSRL = P0FSRL_VAL;
	P1FSRH = P1FSRH_VAL;
	P1FSRL = P1FSRL_VAL;
	P2FSRH = P2FSRH_VAL;
	P2FSRL = P2FSRL_VAL;
	P3FSR  = P3FSR_VAL;
}

void Init_Touch (void)
{
    ts.state                    = TS_STATE_INIT;
    ts.flag.touch_freq_sel_mode = TOUCH_FREQ_SEL_EN;

    Library_Data_Assign();
    Touch_Config_Set();

    g_sys_flag.calib_ok = 0;
    g_sys_flag.led_io = 0;
    g_sys_flag.time_div = TS_LED_TIME_DIV;

    UT_Run_Timer();  
}
//Display Dimming
void Timer1_init()
{
	// initialize Timer
	// 16bit timer, period = 0.010000mS
	T1CRH = 0x00;   	// timer setting High
	T1CRL = 0xC0;   	// timer setting Low
	T1ADRH = 0x00;  	// period count High
	T1ADRL = 0x9F;  	// period count Low
	IE2 |= 0x04;    	// Enable Timer1 interrupt
	T1CRH |= 0x80;  	// enable counter
}

void Timer2_init()
{
	// initialize Timer
	// 16bit timer, period = 1.000000mS
	T2CRH = 0x00;   	// timer setting High
	T2CRL = 0xC0;   	// timer setting Low
	T2ADRH = 0x3E;  	// period count High
	T2ADRL = 0x7F;  	// period count Low
	IE2 |= 0x08;    	// Enable Timer2 interrupt
	T2CRH |= 0x80;  	// enable counter
}

void ExINT_init()
{
	//CLK
	Port_EnableInterrupt(EXTINT_CH10);
	Port_ConfigureInterrupt(EXTINT_CH10, BOTH_EDGE);
	
	//STB
	Port_EnableInterrupt(EXTINT_CH11);
	Port_ConfigureInterrupt(EXTINT_CH11, RISING_EDGE);
}

/** *******************************************************************
 * @brief       Specifies the variable location for library use.
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void Init_User_Function(void)
{
    
#if (TOUCH_FREQ_SEL_EN == 1)
    func_p_Touch_Freq_Sel       = Touch_Freq_Sel;
#endif

#if (FIRST_KEY_PRIORITY == 1)
    user.priority_ch_idx = PRIORITY_CH_BIT;
#endif

#if (HOLD_KEY_RELEASE == 1)
    user.hold_key_release_time = TIMER_HOLD_KEY_RELEASE;
#endif

#if (MULTI_KEY_RESET == 1)
    user.multi_key_check  = 0;
    user.multi_ch_bit = MULTI_CH_BIT;
    user.multi_key_limit = MAX_MULTY_KEY_NUM;
    if(user.multi_key_limit < 1)    
    {
        user.multi_key_limit = 1;
    }
#endif

#if LED_DRV_EN == 1 
    led.flag.seg_current = LED_CURRENT;       
    led.flag.mode = 2;  //200729?
    led.com_sel = (uint8_t)COMSEL_00_07;
    led.seg_sel = (uint16_t)((SEGSEL_08_15<<8)+SEGSEL_00_07);
    led.p0_seg = P0_SEG_IO;
    led.p1_seg = P1_SEG_IO;
    led.p2_seg = P2_SEG_IO;
    led.p3_seg = P3_SEG_IO;

    LED_Set_Actv_Time(LED_USE_COM_NUM,TIME_LED_OPTERATING);    
#if TS_LED_TIME_DIV == 1
    Touch_Set_Actv_Time(TIMER_TOUCH_OPTERATING);
#endif

#else   // 200720+
    P2 |= COMSEL_00_07;
    P2IO |= COMSEL_00_07;
#endif  

#if (SLIDE_FUNCTION_EN == 1)
    Slide_ch_set();
#endif
    
#if (WHEEL_FUNCTION_EN == 1)
    Wheel_ch_set();
#endif
        

//SG 추가 =================================

	Timer1_init();
	Timer2_init();
	ExINT_init();


}

/** *******************************************************************
 * @brief       main function
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void main(void)
{   
    e_task task;    
    
    DI();
    
    // system clock 16Mhax
    SCCR = Internal_16MHz_OSC;
    OSCCR = Divider_16MHz;
    
    Init_GPIO(); 
    
    Init_Touch(); 
    
    Init_User_Function();

    EI();

    task = TASK_LED;

    while (1)
    {
        switch (task)
        {           
            case TASK_LED : break;          
            case TASK_TOUCH :
                Touch_Do_Task();
#if ((HOLD_KEY_RELEASE | MULTI_KEY_RESET | FIRST_KEY_PRIORITY) == 1)
                if (ts.flag.touch_sensing_end == 1)
                {
                    Touch_Key_Scenario();
                    ts.flag.touch_sensing_end = 0;
                }
#endif
            case TASK_GESTURE :
#if (SLIDE_FUNCTION_EN | WHEEL_FUNCTION_EN)
                GESTURE_Do_Task(&diff_data[0]);
#endif
                break;
            case TASK_DEBUG :break;
            case TASK_USER  : proc(); break;
            default :
                break;
        }

        task++;
        if (task == TASK_MAX)
        {
            task = TASK_LED;
        }
#if (WDT_ENABLE == 1)
        WDT_ClearCountData();
#endif
    }
}

//##########################################################################
//##########################################################################
