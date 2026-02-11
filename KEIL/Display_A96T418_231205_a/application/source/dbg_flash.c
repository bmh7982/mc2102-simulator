/**
 *******************************************************************************
 * @file        dbg_flash.c
 * @author      ABOV R&D Division
 * @brief       A96T418 debug data write in flash
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#include <intrins.h>
#include <stdio.h>
#include "A96T418.h" 
#include "common.h"
#include "touch_lib.h"
#include "touch_process.h"
#include "debug.h"
#include "flash.h"
#include "user.h"

#if (DBG_FLASH_SAVE == 1)

uint8_t page_unit[FLASH_PAGE_SIZE];
uint8_t fla_idx;
uint16_t fla_addr_w; 
uint16_t fla_addr_r;
/*************************************************************
 - FUNCTION & CLASS NAME
    : void eraseFlash(uint16_t addr)
    
 - DESCRIPTION
    : 
    
 - PARAMETER & RETURN
    : 
    
*************************************************************/
void Flash_Erase_Page(uint16_t addr)
{
    rSecurity_Call = call_id;
    rSecurity_Write = write_id;
    Flash_Erase(addr);
    Erase_Security_ID();
}
/*************************************************************
 - FUNCTION & CLASS NAME
    : void writeFlash(uint16_t addr, uint8_t* pDat)
    
 - DESCRIPTION
    : 
    
 - PARAMETER & RETURN
    : 
    
*************************************************************/
void Flash_Write_Page(uint16_t addr, uint8_t* pDat)
{
    rSecurity_Call = call_id;
    rSecurity_Write = write_id;
    Flash_Write(addr, pDat);
    Erase_Security_ID();    
}
/*************************************************************
 - FUNCTION & CLASS NAME
    : void Flash_Send_Data(void)
    
 - DESCRIPTION
    : 
    
 - PARAMETER & RETURN
    : 
    
*************************************************************/
void Flash_Send_Data(void)
{
    uint8_t i;
    uint8_t len;        /* Keil:Optimization - Level 7이상에서 i 와 충돌 */
    uint8_t shift_bit;
    uint8_t mask_cnt;

    if (fla_addr_r > FLASH_LAST_ADDR)
    {
        return;
    }

    uart.tx_write_idx = 0;
    uart.tx_read_idx = 0;
    uart.tx_checksum = 0;
    uart.tx_queue[uart.tx_write_idx++] = DBG_SMARTKEY_GET_STX; /* header[1] */

    /* Length Calc */                   
    mask_cnt = 0;
    shift_bit = 0x01;
    for (i=0; i<8; i++)
    {
        if(dbg.mask & shift_bit)
        {
            mask_cnt++;
        }
        shift_bit<<=1;
    }

    len = 4 + dbg.ch_cnt * mask_cnt * 2;
    len = (len/2)|0x80;     
    Make_Packet_Byte(len);                      /* length[1] */
    Make_Packet_Byte(0x00);                     /* mode[2] */
    Make_Packet_Byte(0x10);
    Make_Packet_Byte(ts.detect_key);                /* key[1] */
    Make_Packet_Byte(0x00);                     /* cyle[1] */

    for (i = dbg.start_idx; i < dbg.start_idx+dbg.ch_cnt; i++)  
    {   
        if (dbg.mask & DBG_DATA0)                
        {
            Make_Packet_Byte(coderom[fla_addr_r++]);
            Make_Packet_Byte(coderom[fla_addr_r++]);
        }
        if (dbg.mask & DBG_DATA1)                
        {               
            Make_Packet_Byte(coderom[fla_addr_r++]);
            Make_Packet_Byte(coderom[fla_addr_r++]);
        }
        if (dbg.mask & DBG_DATA2)           
        {
            Make_Packet_Byte(coderom[fla_addr_r++]);
            Make_Packet_Byte(coderom[fla_addr_r++]);
        }
        if (dbg.mask & DBG_DATA3)              
        {
            Make_Packet_Byte(coderom[fla_addr_r++]);
            Make_Packet_Byte(coderom[fla_addr_r++]);
        }
        if (dbg.mask & DBG_DATA4)            
        {           
            Make_Packet_Byte(coderom[fla_addr_r++]);
            Make_Packet_Byte(coderom[fla_addr_r++]);
        }
        if (dbg.mask & DBG_DATA5)
        {   
            Make_Packet_Byte(coderom[fla_addr_r++]);
            Make_Packet_Byte(coderom[fla_addr_r++]);
        }
        if (dbg.mask & DBG_DATA6)
        {           
            Make_Packet_Byte(coderom[fla_addr_r++]);
            Make_Packet_Byte(coderom[fla_addr_r++]);
        }
        if (dbg.mask & DBG_DATA7)
        {       
            Make_Packet_Byte(coderom[fla_addr_r++]);
            Make_Packet_Byte(coderom[fla_addr_r++]); 
        }               
    }
    #if (0)
    if (fla_addr_r == FLASH_LAST_ADDR+1)
    {
        fla_addr_r = FLASH_START_ADDR;
    }
    #endif
    uart.tx_checksum = ((~uart.tx_checksum)&0x00ffff)-1;    
    uart.tx_queue[uart.tx_write_idx++] = (uint8_t)(uart.tx_checksum>>8);
    uart.tx_queue[uart.tx_write_idx++] = (uint8_t)(uart.tx_checksum>>0);
    uart.tx_queue[uart.tx_write_idx++] = DBG_SMARTKEY_GET_CR;
    uart.tx_queue[uart.tx_write_idx++] = DBG_SMARTKEY_GET_LF;
        
    IE1 |= BIT(4);
    USI0DR = uart.tx_queue[uart.tx_read_idx++];
}
#if (0)
/*************************************************************
 - FUNCTION & CLASS NAME
    : void Flash_Write_Data(void)
    
 - DESCRIPTION
    : 
    
 - PARAMETER & RETURN
    : 
    
*************************************************************/
void Flash_Write_Data(void)
{
    uint8_t i;

    if (dbg.flag.flash_dbg == 0) return;

    if (fla_addr_w < (FLASH_LAST_ADDR+1))
    {
        for (i=dbg.start_idx; i<dbg.start_idx+dbg.ch_cnt; i++)  
        {   
            if (dbg.mask & DBG_SMARTKEY_SUM)                
            {
                page_unit[fla_idx++] = (uint8_t)(t_ts.pRawData[i][0]>>8);
                page_unit[fla_idx++] = (uint8_t)(t_ts.pRawData[i][0]>>0);
            }
            if (dbg.mask & DBG_SMARTKEY_REL)                
            {               
                page_unit[fla_idx++] = (uint8_t)(t_ts.pRawData[i][1]>>8);
                page_unit[fla_idx++] = (uint8_t)(t_ts.pRawData[i][1]>>0);
            }
            if (dbg.mask & DBG_SMARTKEY_BASE)           
            {
                page_unit[fla_idx++] = (uint8_t)(t_ts.pBaseData[i][0]>>8);
                page_unit[fla_idx++] = (uint8_t)(t_ts.pBaseData[i][0]>>0);
            }
            if (dbg.mask & DBG_SMARTKEY_DELTA)              
            {
                page_unit[fla_idx++] = (uint8_t)(t_ts.pBaseData[i][1]>>8);
                page_unit[fla_idx++] = (uint8_t)(t_ts.pBaseData[i][1]>>0);
            }
            if (fla_idx == FLASH_PAGE_SIZE)
            {
                fla_idx = 0;
                Flash_Write_Page(fla_addr_w, page_unit);
                fla_addr_w += FLASH_PAGE_SIZE;
            }
        }
    }
    else
    {
        Flash_Send_Data();
    }
}
#else
/*************************************************************
 - FUNCTION & CLASS NAME
    : void Flash_Write_Data(void)
    
 - DESCRIPTION
    : 
    
 - PARAMETER & RETURN
    : 
    
*************************************************************/
void Flash_Write_Data(void)
{
    uint8_t i;

    if (dbg.flag.flash_dbg == 0) return;

    if (fla_addr_w < (FLASH_LAST_ADDR+1))
    {
        for (i=dbg.start_idx; i<dbg.start_idx+dbg.ch_cnt; i++)  
        {   
            if (dbg.mask & DBG_DATA0)                
            {
                page_unit[fla_idx++] = (uint8_t)(raw_data[i][0]>>8);
                page_unit[fla_idx++] = (uint8_t)(raw_data[i][0]>>0);
                if (fla_idx == FLASH_PAGE_SIZE)
                {
                    fla_idx = 0;
                    Flash_Write_Page(fla_addr_w, page_unit);
                    fla_addr_w += FLASH_PAGE_SIZE;
                }
            }
            if (dbg.mask & DBG_DATA1)                
            {               
                page_unit[fla_idx++] = (uint8_t)(baseline[i][0]>>8);
                page_unit[fla_idx++] = (uint8_t)(baseline[i][0]>>0);
                if (fla_idx == FLASH_PAGE_SIZE)
                {
                    fla_idx = 0;
                    Flash_Write_Page(fla_addr_w, page_unit);
                    fla_addr_w += FLASH_PAGE_SIZE;
                }
            }
            if (dbg.mask & DBG_DATA2)           
            {
                page_unit[fla_idx++] = (uint8_t)(raw_data[i][1]>>8);
                page_unit[fla_idx++] = (uint8_t)raw_data[i][1]>>0);
                if (fla_idx == FLASH_PAGE_SIZE)
                {
                    fla_idx = 0;
                    Flash_Write_Page(fla_addr_w, page_unit);
                    fla_addr_w += FLASH_PAGE_SIZE;
                }
            }
            if (dbg.mask & DBG_DATA3)              
            {
                page_unit[fla_idx++] = (uint8_t)(baseline[i][1]>>8);
                page_unit[fla_idx++] = (uint8_t)(baseline[i][1]>>0);
                if (fla_idx == FLASH_PAGE_SIZE)
                {
                    fla_idx = 0;
                    Flash_Write_Page(fla_addr_w, page_unit);
                    fla_addr_w += FLASH_PAGE_SIZE;
                }
            }
            if (dbg.mask & DBG_DATA4)                
            {
                page_unit[fla_idx++] = (uint8_t)(abs(diff_data[i])>>8);
                page_unit[fla_idx++] = (uint8_t)(abs(diff_data[i])>>0);
                if (fla_idx == FLASH_PAGE_SIZE)
                {
                    fla_idx = 0;
                    Flash_Write_Page(fla_addr_w, page_unit);
                    fla_addr_w += FLASH_PAGE_SIZE;
                }
            }
            if (dbg.mask & DBG_DATA5)              
            {               
                page_unit[fla_idx++] = (uint8_t)(abs(diff_data[i])>>8);
                page_unit[fla_idx++] = (uint8_t)(abs(diff_data[i])>>0);
                if (fla_idx == FLASH_PAGE_SIZE)
                {
                    fla_idx = 0;
                    Flash_Write_Page(fla_addr_w, page_unit);
                    fla_addr_w += FLASH_PAGE_SIZE;
                }
            }
            if (dbg.mask & DBG_DATA6)          
            {
                page_unit[fla_idx++] = (uint8_t)(thd_detect[i]>>8);
                page_unit[fla_idx++] = (uint8_t)(thd_detect[i]>>0);
                if (fla_idx == FLASH_PAGE_SIZE)
                {
                    fla_idx = 0;
                    Flash_Write_Page(fla_addr_w, page_unit);
                    fla_addr_w += FLASH_PAGE_SIZE;
                }
            }
            if (dbg.mask & DBG_DATA7)              
            {
                page_unit[fla_idx++] = (uint8_t)(thd_detect[i]>>8);
                page_unit[fla_idx++] = (uint8_t)(thd_detect[i]>>0);
                if (fla_idx == FLASH_PAGE_SIZE)
                {
                    fla_idx = 0;
                    Flash_Write_Page(fla_addr_w, page_unit);
                    fla_addr_w += FLASH_PAGE_SIZE;
                }
            }
        }
    }
    else
    {
        Flash_Send_Data();
    }
}
#endif
#endif  //#if (DBG_FLASH_SAVE == 1)

