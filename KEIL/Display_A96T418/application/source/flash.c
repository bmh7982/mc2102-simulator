/**
 *******************************************************************************
 * @file        flash.c
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
 
#include <intrins.h>
#include "..\Common\A96T418.h" 
#include "..\Common\common.h"
#include "flash.h"
#include "debug.h"

#if (DBG_FLASH_SAVE == 1)

#define PAGEBUF_SIZE    64
#define PAGEBUF_ADDR    0x0000

//#define cli()     (EA = 0)
//#define sei()     (EA = 1)

#define coderom ((uint8_t volatile code  *) 0)
#define Flash_Exit()    FEMR = 0x00                 // Set flash to normal mode.

#define WAITTIME 163        // 2.5625ms @ LSIRC 128KHz

uint8_t rSecurity_Call;
uint8_t rSecurity_Write;

// from flash_enter.a51
extern void Flash_LoadData(uint8_t dt, uint16_t add);
extern void Flash_Enter(void);

//==============================================================================
void Erase_Security_ID(void)
{
    rSecurity_Call = 0;                     //
    rSecurity_Write = 0;                    //
}
//------------------------------------------------------------------------------
uint8_t Check_Security_ID(void)
{
    if ( (rSecurity_Call != call_id) && (rSecurity_Write != write_id) )
    {   Erase_Security_ID();                //
        return 1;                           // fail
    }
    else return 0;                          // pass
}
//------------------------------------------------------------------------------
/*
uint8_t Check_LSIRC (void)
{
    if ( (OSCCR & 0x40) == 0x40 )   // LSIRC ON ?
    {
        return 0;
    }
    else
    {
        OSCCR |=  ( LSIRC_EN << 6);
        wait_100uSec(10);   // stabilzation time
        return 1;
    }
}
*/
//------------------------------------------------------------------------------
// flash erase, write addr -> 0, (0+PAGEBUF_SIZE), (0+PAGEBUF_SIZE*2),...
// flash erase, write unit -> PAGEBUF_SIZE
//
int8_t Flash_Erase(uint16_t addr)
{
    uint16_t i;
    
    uint16_t temp0;
    uint16_t temp1;
    
    if(Check_Security_ID())
        return -1;                  // Security ID fail
    
    // Enable program mode
    cli();              // Global INT disable
    Flash_Enter();

    // erase
    FEMR = 0x81;    // Select flash and enable control.
    FECR = 0x02;    // Reset page buffer.
    FEMR = 0x89;    // Select page buffer.

    for(i=0;i<PAGEBUF_SIZE;i++){
        Flash_LoadData(0, i+PAGEBUF_ADDR);
    }

    FEMR = 0x91;        // Set Erase mode.
    FETCR = WAITTIME;   // Set Erase time. 

    FEARL = (uint8_t)(addr&0xff);
    FEARM = (uint8_t)((addr>>8)&0xff);
    FEARH = 0;

    if(Check_Security_ID())          //
    {   Erase_Security_ID();            //
        return -1;
    }

    FECR = 0x0B;    // Start Erase.
    _nop_();

    while( !( FESR & 0x80));        // Read status register.

    Flash_Exit();                       // Set flash to normal mode.
    sei();
    Erase_Security_ID();                //

    // read data  
    for(i=0; i<PAGEBUF_SIZE;i++){   // Read flash data.
        if(coderom[addr+i] != 0x00) //if(coderom[addr] != 0x00) 
        {
            temp0 = coderom[addr];
            temp1 = addr;
            _nop_();
            
            return -1;
        }
        addr++;
    }

    return 0;
}

int8_t Flash_Write(uint16_t addr, uint8_t *dt)
{
    uint16_t i;
    uint8_t *pdt;

    if(Check_Security_ID())
        return -1;         

    // Enable program mode
    cli();              // Global INT disable
    Flash_Enter();

    // write
    FEMR = 0x81;    // Select flash and enable control.
    FECR = 0x02;    // Reset page buffer.
    FEMR = 0x89;    // Select page buffer.

    pdt = dt;
    for(i=0;i<PAGEBUF_SIZE;i++){
        Flash_LoadData(*pdt, i+PAGEBUF_ADDR);
        pdt++;
    }

    FEMR = 0xA1;            // Set write mode.
    FETCR = WAITTIME;       // Set Erase time. 
    FEARL = (uint8_t)(addr&0xff);
    FEARM = (uint8_t)((addr>>8)&0xff);
    FEARH = 0x00;

    if(Check_Security_ID())      //
    {   Erase_Security_ID();        //
        return -1;                  //
    }
    else FECR = 0x0B;               // Start program.
    
    _nop_();                        //
    while ( !( FESR & 0x80));       //
    
    Flash_Exit();                       // Set flash to normal mode.
    sei();
    Erase_Security_ID();                //

    // read data
    pdt = dt;
    for(i=0;i<PAGEBUF_SIZE;i++){    // Read flash data.
        if (coderom[addr]!=*pdt) 
          return -1;
        
        addr++;
        pdt++;
    }

    return 0;
}

int8_t Flash_Read(uint16_t addr, uint8_t *dt)
{
    uint16_t i;
    uint8_t *pdt;
    
    // read data
    pdt = dt;
    for(i=addr; i<(addr+PAGEBUF_SIZE); i++) // Read flash data.
    {
        *pdt = coderom[i];
        pdt++;
    }
    
    return 0;
}
#endif  //#if (DBG_FLASH_SAVE == 1)