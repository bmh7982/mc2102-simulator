/**
 *******************************************************************************
 * @file        flash.h
 * @author      ABOV R&D Division
 * @brief       A96T418 flash deriver code
 *
 * Copyright 2022 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

#ifndef _FLASH_HEADER_
#define _FLASH_HEADER_

#include "typedef.h"


#define call_id     0x03
#define write_id    0x76

#define FLASH_START_ADDR	0x4000
#define FLASH_LAST_ADDR		0x7fff
#define FLASH_PAGE_SIZE 	64
#define FLASH_PAGE_N		((0x8000-FLASH_START_ADDR)/FLASH_PAGE_SIZE)
#define coderom ((uint8_t volatile code  *) 0)


extern uint8_t rSecurity_Call;
extern uint8_t rSecurity_Write;

extern int8_t Flash_Erase(uint16_t addr);
extern int8_t Flash_Write(uint16_t addr, uint8_t *dt);
extern int8_t Flash_Read(uint16_t addr, uint8_t *dt);
extern uint8_t Check_LSIRC (void);
extern void Erase_Security_ID(void);
#endif //_FLASH_HEADER_
