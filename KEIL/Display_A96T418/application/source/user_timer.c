/**
 *******************************************************************************
 * @file        user_timer.c
 * @author      ABOV R&D Division
 * @brief       Timer count 1 user code
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
#include "user_timer.h"

uint32_t g_systick;

static uint16_t ut_set_flag;
static uint16_t ut_expire_flag;
static uint32_t ut_init_delay_timer; // UT_INIT_DELAY
static uint32_t ut_reverse_timer; // UT_REVERSE
static uint32_t ut_base_update_timer; // UT_BASE_UPDATE
static uint32_t ut_hold_key_timer; // UT_HOLD_KEY_RELEASE
static uint32_t ut_slide_event_hold_timer;
static uint32_t ut_wheel_event_hold_timer;
#if (0)
static uint32_t ut_timer_7;
static uint32_t ut_timer_8;
#endif

struct ut_param ut;

void UT_Run_Timer(void)
{
    ut_init_delay_timer = 0;
    ut_reverse_timer = 0;
    ut_base_update_timer = 0;
    ut_hold_key_timer = 0;
    ut_slide_event_hold_timer = 0;
    ut_wheel_event_hold_timer = 0;
#if (0) 
    ut_timer_7 = 0;
    ut_timer_8 = 0;
#endif  
    ut_set_flag = 0;
    ut_expire_flag = 0;

    /* ********************************************************
    T0CR = (0<<7)   |   // 1: T0 Enable 
           (0<<4)   |   // 0: Timer/Counter
           (4<<1)   |   // 0: fx/2
                        // 1: fx/4
                        // 2: fx/8
                        // 3: fx/32
                        // 4: fx/128
                        // 5: fx/512
                        // 6: fx/2048
                        // 7: EC0
           (0<<0);      // 1: clear counter and start
    *********************************************************/

    T0CR = 0x08;
    T0DR = 124; 
    #if (0)
    if (ut.flag.clock_src == FX_16MHZ)
    {
        T0CR = 0x08;
        T0DR = 124;
    }
    else if (ut.flag.clock_src == FX_8MHZ)
    {
        T0CR = 0x06;
        T0DR = 249;
    }
    else if (ut.flag.clock_src == FX_4MHZ)
    {
        T0CR = 0x06;
        T0DR = 124;
    }
    else if (ut.flag.clock_src == FX_1MHZ)
    {
        T0CR = 0x04;
        T0DR = 124;
    }
    else
    {
        T0CR = 0x08;
        T0DR = 124;
    }
    #endif

    IE2 |= BIT(1);  
    T0CR |= BIT(7);
}

static void Timer1_ISR(void) interrupt 13 
{
    EA = 1;
    g_systick++;
}
#if (0)
/** *******************************************************************
 * @brief       Initialize user-timer variables
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
void ut_InitParam(void)
{
#if (0)     
    ut_timer_1 = 0;
#endif  
    ut_timer_2 = 0;
    ut_timer_3 = 0;
    #if (0)
    ut_timer_4 = 0;
    ut_timer_5 = 0;
    ut_timer_6 = 0;
    ut_timer_7 = 0;
    ut_timer_8 = 0;
    #endif
    ut_set_flag = 0;
    ut_expire_flag = 0;
}
#endif
/** *******************************************************************
 * @brief       set user-timer
 * @param[in]   utid : user-timer id
                timeout : timeout in milli second.
 * @return      void
 *
 *********************************************************************/
void UT_Set_Timer(uint16_t utid, uint32_t timeout)
{
    uint32_t ticks;

    ticks = g_systick;
    
    switch (utid)
    {   
        case UT_INIT_DELAY : 
            ut_init_delay_timer = ticks + timeout;
            break;   
        case UT_REVERSE : 
            ut_reverse_timer = ticks + timeout;
            break;
        case UT_BASE_UPDATE: 
            ut_base_update_timer = ticks + timeout;
            break;  
        case UT_HOLD_KEY_RELEASE: 
            ut_hold_key_timer = ticks + timeout;
            break;
        case UT_SLIDE_EVENT_HOLD: 
            ut_slide_event_hold_timer = ticks + timeout;
            break;
        case UT_WHEEL_EVENT_HOLD: 
            ut_wheel_event_hold_timer = ticks + timeout;
            break;
#if (0)
        case UT_7: 
            ut_timer_7 = ticks + timeout;
            break;
        case UT_8: 
            ut_timer_8 = ticks + timeout;
            break;
        default: 
            break;
#endif
    }
    /* set timer-set flag and clear time-out flag */
    if(utid)
    {
        ut_set_flag |= utid;
        ut_expire_flag &= ~utid;
    }
}
#if (0)
/** *******************************************************************
 * @brief       get elapsed time
 * @param[in]   utid : user-timer id
 * @return      elap_ms : elapsed time
 *
 *********************************************************************/
uint16_t ut_GetElaps(uint16_t utid)
{
    uint16_t elap_ms;
    uint32_t capture_ms;
    uint32_t ticks;

    ticks = g_systick;
    
    switch (utid)
    {   
        case UT_1 : 
            capture_ms = s32_Capture_1;
            break;
        case UT_REVERSE : 
            capture_ms = s32_Capture_2;
            break;
        case UT_BASE_HOLD: 
            capture_ms = s32_Capture_3;
            break;              
        case UT_4: 
            capture_ms = s32_Capture_4;
            break;
        case UT_5: 
            capture_ms = s32_Capture_5;
            break;
        case UT_6: 
            capture_ms = s32_Capture_6;
            break;
        case UT_7: 
            capture_ms = s32_Capture_7;
            break;
        case UT_1: 
            capture_ms = s32_Capture_8;
            break;
        case UT_9: 
            capture_ms = s32_Capture_9;
            break;
        default: 
            break;
    }
    
    if (ticks > capture_ms)
    {
        if (ticks - capture_ms > 65535)
        {
            elap_ms = 0xffff;
        }
        else
        {
            elap_ms = (uint16_t)(ticks - capture_ms);
        }
    }
    else
    {
        if (capture_ms - ticks > 65535)
        {
            elap_ms = 0xffff;
        }
        else
        {
            elap_ms = (uint16_t)(capture_ms - ticks);
        }
    }

    return elap_ms;
}
#endif
#if (1)
/** *******************************************************************
 * @brief       get user-timer set infomation
 * @param[in]   none
 * @return      ut_set_flag
 *
 *********************************************************************/
uint16_t UT_Get_Status(void)
{
    return ut_set_flag;
}
#endif
/** *******************************************************************
 * @brief       clear user-timer set information & count
 * @param[in]   utid
 * @return      void
 *
 *********************************************************************/
void UT_Clear_Timer(uint16_t utid)
{
    /* clear user-timer */
    switch (utid)
    {   
        case UT_INIT_DELAY : 
            ut_init_delay_timer = 0;
            break;   
        case UT_REVERSE : 
            ut_reverse_timer = 0;
            break;      
        case UT_BASE_UPDATE : 
            ut_base_update_timer = 0;
            break;      
        case UT_HOLD_KEY_RELEASE : 
            ut_hold_key_timer = 0;
            break;
        case UT_SLIDE_EVENT_HOLD : 
            ut_slide_event_hold_timer = 0;
            break;  
        case UT_WHEEL_EVENT_HOLD : 
            ut_wheel_event_hold_timer = 0;
            break;      
#if (0)
        case UT_7 : 
            ut_timer_7 = 0;
            break;             
        case UT_8 : 
            ut_timer_8 = 0;
            break;
        default: 
            break;
#endif
    }
    
    /* clear timer-set flag and time-out flag */
    if (utid)
    {
        ut_set_flag &= ~utid;
        ut_expire_flag &= ~utid;
    }
}
/** *******************************************************************
 * @brief       update user-timer expiration flag
 * @param[in]   none
 * @return      void
 *
 *********************************************************************/
static void UT_Check_Expire(void)
{
    uint16_t flag = 0;
    uint32_t systick;

    systick = g_systick;

    /* if setted-user-timer is exist */
    if (ut_set_flag)
    {
        /* if general-user-timer is setted */
        if (ut_set_flag & UT_INIT_DELAY)
        {
            if((ut_init_delay_timer <= systick) && ((systick-ut_init_delay_timer) < 0x80000000))
            {
                ut_init_delay_timer = 0;
                flag |= UT_INIT_DELAY;
            }
        }   
        /* if data-user-timer is setted */
        if (ut_set_flag & UT_REVERSE)
        {
            if((ut_reverse_timer <= systick) && ((systick-ut_reverse_timer) < 0x80000000))
            {
                ut_reverse_timer = 0;
                flag |= UT_REVERSE;
            }
        }
        /* if led-user-timer is setted */
        if (ut_set_flag & UT_BASE_UPDATE)
        {
            if((ut_base_update_timer <= systick) && ((systick-ut_base_update_timer) < 0x80000000))
            {
                ut_base_update_timer = 0;
                flag |= UT_BASE_UPDATE;
            }
        }
        /* if holdoff-user-timer is setted */
        if (ut_set_flag & UT_HOLD_KEY_RELEASE)
        {
            if((ut_hold_key_timer <= systick) && ((systick-ut_hold_key_timer) < 0x80000000))
            {
                ut_hold_key_timer = 0;
                flag |= UT_HOLD_KEY_RELEASE;
            }
        }
        /* if general-user-timer is setted */
        if (ut_set_flag & UT_SLIDE_EVENT_HOLD)
        {
            if((ut_slide_event_hold_timer <= systick) && ((systick-ut_slide_event_hold_timer) < 0x80000000))
            {
                ut_slide_event_hold_timer = 0;
                flag |= UT_SLIDE_EVENT_HOLD;
            }
        }
        /* if data-user-timer is setted */
        if (ut_set_flag & UT_WHEEL_EVENT_HOLD)
        {
            if((ut_wheel_event_hold_timer <= systick) && ((systick-ut_wheel_event_hold_timer) < 0x80000000))
            {
                ut_wheel_event_hold_timer = 0;
                flag |= UT_WHEEL_EVENT_HOLD;
            }
        }
#if (0)
        /* if led-user-timer is setted */
        if (ut_set_flag & UT_7)
        {
            if((ut_timer_7 <= systick) && ((systick-ut_timer_7) < 0x80000000))
            {
                ut_timer_7 = 0;
                flag |= UT_7;
            }
        }
        /* if holdoff-user-timer is setted */
        if (ut_set_flag & UT_8)
        {
            if((ut_timer_8 <= systick) && ((systick-ut_timer_8) < 0x80000000))
            {
                ut_timer_8 = 0;
                flag |= UT_8;
            }
        }
        #endif
        /* user-timer-out-flag set */
        if (flag)
        {
            ut_expire_flag |= flag;
        }
    }

}
/** *******************************************************************
 * @brief       update user-timer expiration information
 * @param[in]   utid : user-timer id
 * @return      rtn : if a user-timer is expired, return 1
                      else, return 0
 *
 *********************************************************************/
uint8_t UT_Is_Expired(uint16_t utid)
{
    uint8_t rtn;

    UT_Check_Expire();

    rtn = 0;
    /* if time-out flag is setted */
    if (ut_expire_flag)
    {
        if (utid)
        {
            if ((ut_expire_flag & utid) == utid)
            {
                rtn = 1;
                ut_expire_flag &= ~utid;    
                ut_set_flag &= ~utid;
                UT_Clear_Timer(utid);           
            }
        }
    }
    
    return(rtn);
}
#if (0)
/** *******************************************************************
 * @brief       
 * @param[in]   
 * @return  
 *
 *********************************************************************/
void ut_SW_Start(uint16_t ut_id)    // SW: STOP WATCH
{
    uint32_t ticks;

    ticks = g_systick;
    
    switch (ut_id)
    {   
        case UT_1 : 
            ut_timer_1 = ticks;
            break;
        case UT_REVERSE : 
            ut_timer_2 = ticks;
            break;
        case UT_BASE_HOLD: 
            ut_timer_3 = ticks;
            break;              
        case UT_4: 
            ut_timer_4 = ticks;
            break;
        case UT_5: 
            ut_timer_5 = ticks;
            break;
        case UT_6: 
            ut_timer_6 = ticks;
            break;
        case UT_7: 
            ut_timer_7 = ticks;
            break;
        case UT_8: 
            ut_timer_8 = ticks;
            break;
        case UT_9: 
            s32_timer_9 = ticks;
            break;
        default: 
            break;
    }
    /* set timer-set flag and clear time-out flag */
    if(ut_id)
    {
        ut_set_flag |= ut_id;
        ut_expire_flag &= ~ut_id;
    }
}
/** *******************************************************************
 * @brief       
 * @param[in]   
 * @return  
 *
 *********************************************************************/
void ut_SW_GetLap(uint16_t ut_id)
{
    uint32_t ticks;

    ticks = g_systick;
    
    switch (ut_id)
    {   
        case UT_1 : 
            ut_timer_1 = ticks;
            
            break;
        case UT_REVERSE : 
            ut_timer_2 = ticks;
            break;
        case UT_BASE_HOLD: 
            ut_timer_3 = ticks;
            break;              
        case UT_4: 
            ut_timer_4 = ticks;
            break;
        case UT_5: 
            ut_timer_5 = ticks;
            break;
        case UT_6: 
            ut_timer_6 = ticks;
            break;
        case UT_7: 
            ut_timer_7 = ticks;
            break;
        case UT_8: 
            ut_timer_8 = ticks;
            break;
        case UT_9: 
            s32_timer_9 = ticks;
            break;
        default: 
            break;
    }
    /* set timer-set flag and clear time-out flag */
    if(ut_id)
    {
        ut_set_flag |= ut_id;
        ut_expire_flag &= ~ut_id;
    }
}
#endif

