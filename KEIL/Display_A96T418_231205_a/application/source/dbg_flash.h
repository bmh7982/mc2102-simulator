/**
 *******************************************************************************
 * @file        dbg_flash.h
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

#ifndef __DBGFLASH_H__
#define __DBGFLASH_H__

#include "typedef.h"


extern uint8_t fla_idx;
extern uint16_t fla_addr_w;
extern uint16_t fla_addr_r;

void Flash_Erase_Page(uint16_t addr);
void Flash_Write_Page(uint16_t addr, uint8_t* pDat);
void Flash_Write_Data(void);

#endif //__DBGFLASH_H__

