/** *******************************************************************
 * @file		A96T418.h
 * @brief		define A96T418's SFR
 * @author	 	ABOV Sensor Solution Team
 *
 * Copyright(C) 2020, ABOV Semiconductor
 * All rights reserved.
 *
 **********************************************************************/
#ifndef _A96T418_H_
#define _A96T418_H_

/*-----------------------------------------
        A96T418 18.09.14 Ver.01 (Tom)
-----------------------------------------*/

#define ON			1
#define OFF			0
#define TS_MAX_KEY 20

#define cli()		do{IE0 &= ~0x80;}while(0)
#define sei()		do{IE0 |=  0x80;}while(0)

//----------------------------------------------------- 0x80
sfr     P0          =   0x80;
sbit    P00         =   0x80;
sbit    P01         =   0x81;
sbit    P02         =   0x82;
sbit    P03         =   0x83;
sbit    P04         =   0x84;
sbit    P05         =   0x85;
sbit    P06         =   0x86;
sbit    P07         =   0x87;

sfr     SP          =   0x81;
sfr16   DPTR0       =   0x82;
sfr     DPL         =   0x82;
sfr     DPH         =   0x83;
sfr16   DPTR1       =   0x84;
sfr     DPL1        =   0x84;
sfr     DPH1        =   0x85;
sfr     LVICR       =   0x86;
sfr     PCON        =   0x87;

//----------------------------------------------------- 0x88
sfr     P1          =   0x88;
sbit    P10         =   0x88;
sbit    P11         =   0x89;
sbit    P12         =   0x8A;
sbit    P13         =   0x8B;
sbit    P14         =   0x8C;
sbit    P15         =   0x8D;
sbit    P16         =   0x8E;
sbit    P17         =   0x8F;

sfr     WTDR        =   0x89;   // Write Only
sfr     WTCNT       =   0x89;   // Read Only
sfr     SCCR        =   0x8A;
sfr     BITCR       =   0x8B;
sfr     BITCNT      =   0x8C;   // Read Only
sfr     WDTCR       =   0x8D;
sfr     WDTDR       =   0x8E;   // Write Only
sfr     WDTCNT      =   0x8E;   // Read Only
sfr     BUZDR       =   0x8F;


//----------------------------------------------------- 0x90
sfr     P2          =   0x90;
//sbit    P20         =   0x90;
sbit    P21         =   0x91;
sbit    P22         =   0x92;
sbit    P23         =   0x93;
sbit    P24         =   0x94;
sbit    P25         =   0x95;
sbit    P26         =   0x96;
sbit    P27         =   0x97;

sfr     P0OD        =   0x91;
sfr     P1OD        =   0x92;
sfr     P2OD        =   0x93;
//sfr     P4OD        =   0x94;
//sfr     P5PU        =   0x95;
sfr     WTCR        =   0x96;
sfr     BUZCR       =   0x97;


//----------------------------------------------------- 0x98
sfr     P3          =   0x98;
sbit    P30         =   0x98;
sbit    P31         =   0x99;

sfr     CRC_CON     =   0x99;
sfr16   CRC_DATA    =   0x9A;
sfr     CRC_DATL    =   0x9A;
sfr     CRC_DATH    =   0x9B;
sfr     ADCCRL      =   0x9C;
sfr     ADCCRH      =   0x9D;
sfr     ADCDRL      =   0x9E;   // Read Only
sfr     ADCDRH      =   0x9F;   // Read Only


//----------------------------------------------------- 0xA0
sfr     P0IO        =   0xA1; // P0 Direction Register
sfr     EO          =   0xA2;
sfr16   EIPOL0      =   0xA4;
sfr     EIPOL0L     =   0xA4;
sfr     EIPOL0H     =   0xA5;
sfr     EIFLAG1     =   0xA6;
sfr     EIPOL1      =   0xA7;


//----------------------------------------------------- 0xA8
sfr     IE          	=   0xA8;
sfr     IE0          	=   0xA8;
sbit    EINT10_INT_EN  =   0xA8;
sbit    EINT11_INT_EN  =   0xA9;
//sbit    USI1_I2C_INT_EN =   0xAA;
//sbit    USI1_RX_INT_EN  =   0xAB;
sbit    LED_INT_EN 	=   0xAA;
sbit    TOUCH_INT_EN  	=   0xAB;
//sbit    USI1_TX_INT_EN =   0xAC;
sbit    EINT_INT_EN   	=   0xAD;
sbit    EA           	=   0xAF;

sfr     IE1         =   0xA9;
sfr     IE2         =   0xAA;
sfr     IE3         =   0xAB;
sfr     P0PU        =   0xAC;
sfr     P1PU        =   0xAD;
sfr     P2PU        =   0xAE;
sfr     P3PU        =   0xAF;

//----------------------------------------------------- 0xB0
sfr     P1IO        =   0xB1; 	// P1 Direction Register
sfr     T0CR        =   0xB2;
sfr     T0CNT       =   0xB3;   	// Read Only
sfr     T0DR        =   0xB4;
sfr     T0CDR       =   0xB4;   	// Read Only


//----------------------------------------------------- 0xB8
sfr     IP          =   0xB8;
sfr     P2IO        =   0xB9;
sfr16   T1CR        =   0xBA;
sfr     T1CRL       =   0xBA;
sfr     T1CRH       =   0xBB;
sfr16   T1ADR       =   0xBC;
sfr     T1ADRL      =   0xBC;
sfr     T1ADRH      =   0xBD;
sfr16   T1BDR       =   0xBE;
sfr     T1BDRL      =   0xBE;
sfr     T1BDRH      =   0xBF;


//----------------------------------------------------- 0xC0
sfr     EIFLAG0     =   0xC0;
sfr     P3IO        =   0xC1;
sfr16   T2CR        =   0xC2;
sfr     T2CRL       =   0xC2;
sfr     T2CRH       =   0xC3;
sfr16   T2ADR       =   0xC4;
sfr     T2ADRL      =   0xC4;
sfr     T2ADRH      =   0xC5;
sfr16   T2BDR       =   0xC6;
sfr     T2BDRL      =   0xC6;
sfr     T2BDRH      =   0xC7;


//----------------------------------------------------- 0xC8
sfr     OSCCR       =   0xC8;
sfr     UCTRL1      =   0xCB;
sfr     UCTRL2      =   0xCC;
sfr     UCTRL3      =   0xCD;
sfr     USTAT       =   0xCF;


//----------------------------------------------------- 0xD0
sfr     PSW         =   0xD0;
sbit    P           =   0xD0;
sbit    F1          =   0xD1;
sbit    OV          =   0xD2;
sbit    RS0         =   0xD3;
sbit    RS1         =   0xD4;
sbit    F0          =   0xD5;
sbit    AC          =   0xD6;
sbit    CY          =   0xD7;

sfr     P5IO        =   0xD1;
sfr16   P0FSR       =   0xD2;
sfr     P0FSRL      =   0xD2;
sfr     P0FSRH      =   0xD3;
sfr16   P1FSR       =   0xD4;
sfr     P1FSRL      =   0xD4;
sfr     P1FSRH      =   0xD5;
sfr     P2FSRL      =   0xD6;
sfr     P2FSRH      =   0xD7;


//----------------------------------------------------- 0xD8
sfr     LVRCR       =   0xD8;
sfr     USI0CR1     =   0xD9;
sfr     USI0CR2     =   0xDA;
sfr     USI0CR3     =   0xDB;
sfr     USI0CR4     =   0xDC;
sfr     USI0SAR     =   0xDD;
sfr     P0DB        =   0xDE;
sfr     P123DB      =   0xDF;

//----------------------------------------------------- 0xE0
sfr     ACC         =   0xE0;
sfr     USI0ST1     =   0xE1;
sfr     USI0ST2     =   0xE2;   // Read Only
sfr     USI0BD      =   0xE3;
sfr     USI0SHDR    =   0xE4;
sfr     USI0DR      =   0xE5;
sfr     USI0SCLR    =   0xE6;
sfr     USI0SCHR    =   0xE7;


//----------------------------------------------------- 0xE8
sfr     RSTFR       =   0xE8;
sfr     P3FSR       =   0xEE;


//----------------------------------------------------- 0xF0
sfr     B           =   0xF0;

//----------------------------------------------------- 0xF8
sfr     IP1         =   0xF8;
sfr     UBAUD       =   0xFC;
sfr     UDATA       =   0xFD;
sfr     FPCR        =   0xFE;
sfr     P5FSR       =   0xFF;

//==================================================================== //
// XSFR                                                                //
//==================================================================== //

#define     T3CRH       *(volatile unsigned char xdata *) 0x1000
#define     T3CRL       *(volatile unsigned char xdata *) 0x1001
#define     T3ADRH      *(volatile unsigned char xdata *) 0x1002
#define     T3ADRL      *(volatile unsigned char xdata *) 0x1003
#define     T3BDRH      *(volatile unsigned char xdata *) 0x1004
#define     T3BDRL      *(volatile unsigned char xdata *) 0x1005

#define     T4CRH       *(volatile unsigned char xdata *) 0x1008
#define     T4CRL       *(volatile unsigned char xdata *) 0x1009

#define     T4ADR       *(volatile unsigned int xdata *) 0x100A
#define     T4ADRH      *(volatile unsigned char xdata *) 0x100A
#define     T4ADRL      *(volatile unsigned char xdata *) 0x100B
#define     T4BDR       *(volatile unsigned int xdata *) 0x100C
#define     T4BDRH      *(volatile unsigned char xdata *) 0x100C
#define     T4BDRL      *(volatile unsigned char xdata *) 0x100D

#define     T5CRH       *(volatile unsigned char xdata *) 0x1010
#define     T5CRL       *(volatile unsigned char xdata *) 0x1011
#define     T5ADR       *(volatile unsigned int xdata *) 0x1012
#define     T5ADRH      *(volatile unsigned char xdata *) 0x1012
#define     T5ADRL      *(volatile unsigned char xdata *) 0x1013
#define     T5BDR       *(volatile unsigned int xdata *) 0x1014
#define     T5BDRH      *(volatile unsigned char xdata *) 0x1014
#define     T5BDRL      *(volatile unsigned char xdata *) 0x1015

#define     UCTRL4      *(volatile unsigned char xdata *) 0x1018
#define     FPCR        *(volatile unsigned char xdata *) 0x1019
#define     RTOCH       *(volatile unsigned char xdata *) 0x101A    // Read Only
#define     RTOCL       *(volatile unsigned char xdata *) 0x101B    // Read Only

#define     FEMR        *(volatile unsigned char xdata *) 0x1020
#define     FECR        *(volatile unsigned char xdata *) 0x1021
#define     FESR        *(volatile unsigned char xdata *) 0x1022
#define     FETCR       *(volatile unsigned char xdata *) 0x1023
#define     FEARM1      *(volatile unsigned char xdata *) 0x1024
#define     FEARL1      *(volatile unsigned char xdata *) 0x1025
#define     FEARH       *(volatile unsigned char xdata *) 0x1028
#define     FEARM       *(volatile unsigned char xdata *) 0x1029
#define     FEARL       *(volatile unsigned char xdata *) 0x102A


// ==================================================================== //
// Flash and EEPROM Memory REGISTER                                     //
// ==================================================================== //
// (0xF1) FEMR;              // FECON        Flash and EEPROM mode register
#define FLASH_SEL               (0x80)
#define FLASH_PGM_MODE          (0x20)
#define FLASH_ERASE_MODE        (0x10)
#define FLASH_PBUFF_SEL         (0x08)
#define FLASH_OTPE_SEL          (0x04)
#define FLASH_VERFY_MODE        (0x02)          // self verify mode
#define FLASH_CON_ENABLE        (0x01)

// (0xF2) FECR;              // FECON        Flash and EEPROM control register
#define FLASH_BULK_ERASE        (0x80 | 0x03)
#define FLASH_MODE_EXIT         (0x30 | 0x03)
#define FLASH_START_ERASE_PGM   (0x08 | 0x03)
#define FLASH_START_READ        (0x04 | 0x03)
#define FLASH_RESET             (0x01)
#define FLASH_PBUFF_RESET       (0x02)
#define FLASH_FECR_INIT         (0x03)

// (0xF3) FESR;              // FECON        Flash and EEPROM status register
#define FLASH_BUSY              (0x80)
#define FLASH_VERIFY_OK         (0x40)
#define FLASH_CRC_MODE          (0x20)
#define FLASH_MWAIT_EN          (0x10)
#define FLASH_IRQ               (0x08)
#define FLASH_ST_PGM_MODE       (0x04)
#define FLASH_ST_ERASE_MODE     (0x02)
#define FLASH_ST_VERIFY_MODE    (0x01)

// (0xE7) FETR;              // FECON        Flash and EEPROM test register
#define FLASH_LOCK_DISABLE      (0x80)
#define FLASH_VPP_OUT_ENABLE    (0x60)
#define FLASH_FULL_READ         (0x08)
#define FLASH_PAGE_READ         (0x00)
#define FLASH_X_FAST            (0x04)
#define FLASH_Y_FAST            (0x00)
#define FLASH_EVEN_ENABLE       (0x02)
#define FLASH_ODD_ENABLE        (0x01)
#define FLASH_VMARGIN_ENABLE    (0x01)


// Interrupt vectors of A96G140
#define EINT10_VECT         0   // IE.0
#define EINT11_VECT         1   // IE.1
#define LED_VECT       		2   // IE.2
#define TOUCH_VECT        	3   // IE.3
#define RES4_VECT        	4   // IE.4
#define EINT_VECT           5   // IE.5

#define EINT8_VECT          6   // IE1.0
#define USART2_TX_VECT      7   // IE1.1
#define USI0_I2C_VECT       8   // IE1.2
#define USI0_RX_VECT        9   // IE1.3
#define USI0_TX_VECT        10  // IE1.4
#define EINT12_VECT         11  // IE1.5

#define T0_OVER_VECT        12  // IE2.0
#define T0_MATCH_VECT       13  // IE2.1
#define T1_MATCH_VECT       14  // IE2.2
#define T2_MATCH_VECT       15  // IE2.3
#define T3_MATCH_VECT       16  // IE2.4
#define T45_MATCH_VECT      17  // IE2.5

#define ADC_VECT            18  // IE3.0
#define USART2_RX_VECT      19  // IE3.1
#define WT_VECT             20  // IE3.2
#define WDT_VECT            21  // IE3.3
#define BIT_VECT            22  // IE3.4
#define LVI_VECT            23  // IE3.5

// Interrupt en/dis control
// IE REG
#define eint10_en()         (EINT10_INT_EN = 1)
#define eint10_dis()        (EINT10_INT_EN = 0)

#define eint11_en()         (EINT11_INT_EN = 1)
#define eint11_dis()        (EINT11_INT_EN = 0)

#define led_int_en()        (LED_INT_EN = 1)
#define led_int_dis()       (LED_INT_EN = 0)

#define touch_int_en()        (TOUCH_INT_EN = 1)
#define touch_int_dis()       (TOUCH_INT_EN = 0)

#define eint0_7_en()        (EINT_INT_EN = 1)
#define eint0_7_dis()       (EINT_INT_EN = 0)

#define global_int_en()     (EA = 1)
#define global_int_dis()    (EA = 0)

// IE1 REG
#define eint8_int_en()      (IE1 |=0x01)
#define eint8_int_dis()     (IE1 &= ~(0x01))

#define usart1_txint_en()   (IE1 |=0x02)
#define usart1_txint_dis()  (IE1 &= ~(0x02))

#define usi0_i2c_en()       (IE1 |=0x04)
#define usi0_i2c_dis()      (IE1 &= ~(0x04))

#define usi0_rx_en()        (IE1 |=0x08)
#define usi0_rx_dis()       (IE1 &= ~(0x08))

#define usi0_tx_en()        (IE1 |=0x10)
#define usi0_tx_dis()       (IE1 &= ~(0x10))

#define eint12_int_en()     (IE1 |=0x20)
#define eint12_int_dis()    (IE1 &= ~(0x20))

// IE2 REG
#define timer0_over_en()    (IE2 |=0x01)
#define timer0_over_dis()   (IE2 &= ~(0x01))

#define timer0_match_en()   (IE2 |=0x02)
#define timer0_match_dis()  (IE2 &= ~(0x02))

#define timer1_match_en()   (IE2 |=0x04)
#define timer1_match_dis()  (IE2 &= ~(0x04))

#define timer2_match_en()   (IE2 |=0x08)
#define timer2_match_dis()  (IE2 &= ~(0x08))

#define timer3_match_en()   (IE2 |=0x10)
#define timer3_match_dis()  (IE2 &= ~(0x10))

#define timer4_5_match_en()  (IE2 |=0x20)
#define timer4_5_match_dis() (IE2 &= ~(0x20))

// IE3 REG
#define adc_int_en()        (IE3 |=0x01)
#define adc_int_dis()       (IE3 &= ~(0x01))

#define usart1_rxint_en()   (IE3 |=0x02)
#define usart1_rxint_dis()  (IE3 &= ~(0x02))

#define wt_int_en()         (IE3 |=0x04)
#define wt_int_dis()        (IE3 &= ~(0x04))

#define wdt_int_en()        (IE3 |=0x08)
#define wdt_int_dis()       (IE3 &= ~(0x08))

#define bit_int_en()        (IE3 |=0x10)
#define bit_int_dis()       (IE3 &= ~(0x10))

#define lvi_int_en()        (IE3 |=0x20)
#define lvi_int_dis()       (IE3 &= ~(0x20))
// ==================================================================== //

#define 	IE02_LED		0x04

// ==================================================================== //

// UCTRL1 reg
#define UDRIE			0x80
#define TXCIE			0x40
#define RXCIE			0x20
#define WAKEIE			0x10
#define TXE				0x08
#define RXE				0x04
#define USARTEN			0x02
#define U2X				0x01

// USTAT reg
#define UDRE			0x80
#define TXC				0x40
#define RXC				0x20
#define WAKE			0x10
#define DOR				0x04
#define FE				0x02
#define PE				0x01

// ==================================================================== //
// T0CR
#define T0EN	7
#define T0MS	4
#define T0CK	1
#define T0CC	0

// T1CR
#define T1EN	7
#define T1CK	5
#define T1MS	4
#define T1CC	0

sfr  	BCCR    		= 	0x8B;   	// BIT          W    8'b-001_0111    BIT Clock Control Register

#if 0
/*
// SYSCON
sfr  	RSFR    		= 	0xE8;   	// RSF          R/W  8'b----_--00    RSF Control Register
sfr  	BODR   		= 	0xD8;    	// BOD          R/W  8'b0010_0001    BOD Control Register @tom LVRCR(???)
sfr  	LVIR     		= 	0x86;  	// LVI          R/W  8'b----_--00    LVD Control Register
sfr  	PCON    		= 	0x87;   	// Core         R/W  8'b0000_0000    Power Control Register
sfr  	SCCR   		= 	0x8A;   	// CLKGEN       R/W  8'b00--_0001    System Clock Control Register
sfr  	OSCCR  		= 	0xC8;    	// CLKGEN       R/W  8'b00--_0001    System Clock Control Register
sfr  	BITCR    		= 	0x8B;   	// BIT          W    8'b-001_0111    BIT Clock Control Register
sfr  	BITR     		= 	0x8C;  	// BIT          R    8'b0000_0000    BIT Data  Register

// WDT 
sfr     WDTMR		=       0x8D; // Watch Dog Timer Mode Register
sfr     WDTR		=       0x8E; // Watch Dog Timer Register
sfr     WDTCR		=       0x8E; // 

// INTCON
sfr     IE3			=       0xAB; // Interrupt Enable Register
sfr     IE2			=       0xAA; // Interrupt Enable Register
sfr     IE1			=       0xA9; // Interrupt Enable Register
sfr     IE0			=       0xA8; // Interrupt Enable Register
sfr     IE			=       0xA8; // Interrupt Enable Register
sbit    EA 			=       0xAF;

//sfr     EIENAB		=       0xA3; // External Interrupt Enable Register
//sfr     EIFLAG		=       0xA4; // External Interrupt Flag Register
//sfr     EIEDGE		=       0xA5; // Interrupt Edge Register
//sfr     EIPOLA		=       0xA6; // External Interrupt Polarity Register
//sfr     EIBOTH		=       0xA7; // External Interrupt Enable Register

sfr     IP			=       0xB8; // Interrupt Priority Register
sfr     IP1			=       0xF8; // Interrupt Priority Register 1

// TIMER 0
sfr     T0CR		=       0xB2; // Timer 0 Control Register
sfr     T0CR1		=       0xB3; // Timer 0 Control High Register
sfr     CDR0L		=       0xB4; // Timer 0 Capture Low Register
sfr     T0L			=       0xB4;
sfr     PWM0DRL	=       0xB4; // Timer 0 PWM Duty Low Register
sfr     CDR0H		=       0xB5; // Timer 0 Capture High Register
sfr     T0H			=       0xB5;
sfr     PWM0DRH	=       0xB5; // Timer 0 PWM Duty High Register
sfr     T0DRL		=       0xB6; // Timer 0 Data Low Register
sfr     PWM0PRL	=       0xB6; // Timer 0 PWM Period Low Register
sfr     T0DRH		=       0xB7; // Timer 0 Data High Register
sfr     PWM0PRH	=       0xB7; // Timer 0 PWM Period High Register

// TIMER 1
sfr     T1CRL		=       0xBA; // Timer 1 Control Register
sfr     T1CRH		=       0xBB; // Timer 1 Control High Register
sfr     CDR1L		=       0xBC; // Timer 1 Capture Low Register
sfr     T1L			=       0xBC;
sfr     PWM1DRL	=       0xBC; // Timer 1 PWM Duty Low Register
sfr     CDR1H		=       0xBD; // Timer 1 Capture High Register
sfr     T1H			=       0xBD;
sfr     PWM1DRH	=       0xBD; // Timer 1 PWM Duty High Register
sfr     T1DRL		=       0xBE; // Timer 1 Data Low Register
sfr     PWM1PRL	=       0xBE; // Timer 1 PWM Period Low Register
sfr     T1DRH		=       0xBF; // Timer 1 Data High Register
sfr     PWM1PRH	=       0xBF; // Timer 1 PWM Period High Register
*/
#endif

sfr     I2CMR		=       0xDA; // I2C Mode Control Register
sfr     I2CSR		=       0xDB; // I2C Status Register
sfr     I2CSCLLR		=       0xDC; // I2C SCL Low Period Register
sfr     I2CSCLHR		=       0xDD; // I2C SCL High Period Register
sfr     I2CSDAHR	=       0xDE; // I2C SDA Hold Register
sfr     I2CDR		=       0xDF; // I2C Data Register
sfr     I2CSAR1		=       0xD6; // I2C Slave Address1 Register
sfr     I2CSAR		=       0xD7; // I2C Slave Address Register

#if 0
/*

//sfr     TMISR		=       0xD5; // Timer Interrupt Status Register

// I2C
sfr     I2CMR		=       0xDA; // I2C Mode Control Register
sfr     I2CSR		=       0xDB; // I2C Status Register
sfr     I2CSCLLR		=       0xDC; // I2C SCL Low Period Register
sfr     I2CSCLHR		=       0xDD; // I2C SCL High Period Register
sfr     I2CSDAHR	=       0xDE; // I2C SDA Hold Register
sfr     I2CDR		=       0xDF; // I2C Data Register
sfr     I2CSAR1		=       0xD6; // I2C Slave Address1 Register
sfr     I2CSAR		=       0xD7; // I2C Slave Address Register

// Flash and EEPROM Memory REGISTER
sfr     FEMR		=       0xEA; // Flash and EEPROM mode register
sfr     FECR		=       0xEB; // Flash and EEPROM control register
sfr     FESR		=       0xEC; // Flash and EEPROM status register
sfr     FETCR		=       0xED; // Flash and EEPROM time control register
sfr     FEARL		=       0xF2; // Flash and EEPROM address register low
sfr     FEARM		=       0xF3; // Flash and EEPROM address register middle
sfr     FEARH		=       0xF4; // Flash and EEPROM address register high
sfr     FEDR		=       0xF5; // Flash and EEPROM data register
sfr     FETR		=       0xF6; // Flash test register
#if 0
// USART REGISTER
sfr     UREG_CTRL1	= 0xFA;       // USART        R/W 8'b0000_0000    USART Control Register 1
sfr     UREG_CTRL2	= 0xFB;       // USART        R/W 8'b0000_0000    USART Control Register 2
sfr     UCTRL1		= 0xFA;       // USART        R/W 8'b0000_0000    USART Control Register 1
sfr     UCTRL2		= 0xFB;       // USART        R/W 8'b0000_0000    USART Control Register 2
sfr     UCTRL3		= 0xFC;       // USART        R/W 8'b0000_0000    USART Control Register 3
sfr     USTAT		= 0xFD;       // USART        R/W 8'b1000_0000    USART Status Register
sfr     UBAUD		= 0xFE;       // USART        R/W 8'b1111_1111    USART BaudRate Register
sfr     UDATA		= 0xFF;       // USART        R/W 8'b0000_0000    USART Data Register
#endif
sfr	  ACC		=	  0xE0;

sfr     TSCRH		=       0xE2; 
sfr     TSCRL		=       0xE3; 
sfr     TSDR		=       0xE4; 
sfr     TSRXER		=       0xE5; 
sfr     TSTXER		=       0xE6;
#if 0
sfr     DIMME		=       0xAE;
sfr     DIMM1		=       0xD2;
sfr     DIMM2		=       0xD3;
sfr     DIMM3		=       0xD4;
#endif
sfr	  B			=	  0xF0;
sfr	  PSW		=	  0xD0;
sfr	  SP			=	  0x81;
sfr16	  _DPTR	=	  0x82;
sfr	  DPL		=	  0x82;
sfr	  DPH		=	  0x83;
sfr	  DPL1		=	  0x84;
sfr	  DPH1		=	  0x85;

sfr     EO			=	  0xA2; // EXTENDED OPERATION REGISTER

sfr LDOCR = 0x8F;

#define LDO_MODE_EN 0x00 //default
#define LDO_MODE_BY 0x01 //bypass

#define LDO_LEVEL_3_3V 0x00 //default
#define LDO_LEVEL_2_5V 0x02

#define LDO_DIS_EN 0x00 //default
#define LDO_DIS_DI 0x04 //disable



//=============================================================
//=============================================================

//=============================================================
//	Register bit aliasing definition
//=============================================================
// UCTRLx1 reg
	// mode
#define ASYS_MODE		0x00
#define SYNC_MODE		0x40
#define SPI_MODE		0xC0
	// parity
#define NO_PARITY		0x00
#define EVEN_PARITY		0x20
#define ODD_PARITY		0x30
	// length of data bit
#define USIZE5			0x00
#define USIZE6			0x02
#define USIZE7			0x04
#define USIZE8			0x06
#define USIZE9			0x0e

// UCTRLx2 reg
#define UDRIE			0x80
#define TXCIE			0x40
#define RXCIE			0x20
#define WAKEIE			0x10
#define TXE				0x08
#define RXE				0x04
#define USARTEN			0x02
#define U2X				0x01

// UCTRL3 reg
#define uMASTER			0x80
#define LOOPS			0x40
#define DISXCK			0x20
#define SPISS			0x10
#define SOFTRST			0x08
#define USBS			0x04

// USTAT reg
#define UDRE			0x80
#define TXC				0x40
#define RXC				0x20
#define WAKE			0x10
#define DOR				0x04
#define FE				0x02
#define PE				0x01

// T0CR
#define T0EN	7
#define T0_PE	6
#define CAP0	5
#define T0CK0	2
#define T0CN	1
#define T0ST	0

// T1CR
#define T1EN	7
#define T1_PE	6
#define CAP1	5
#define T1CK0	2
#define T1CN	1
#define T1ST	0

#define	IE00_EXT0		0x01
#define 	IE01_EXT1		0x02
#define 	IE02_LED		0x04
#define 	IE03_EXT3		0x08
#define	IE04_TCYCLE		0x10
#define	IE05_TOUCH		0x20

#define 	IE10_EMPTY		0x01
#define	IE11_EMPTY		0x02
#define	IE12_SPI0		0x04
#define	IE13_I2C		0x08
#define	IE14_EMPTY		0x10
#define	IE15_EMPTY		0x20

#define	IE20_T0			0x01
#define	IE21_T1			0x02
#define	IE22_T2			0x04
#define	IE23_T3			0x08
#define	IE24_EMPTY		0x10
#define	IE25_EEPROM		0x20

#define 	IE30_EMPTY		0x01
#define 	IE31_EMPTY		0x02
#define 	IE32_EMPTY		0x04
#define 	IE33_WDT		0x08
#define 	IE34_BIT		0x10
#define 	IE35_EMPTY		0x20

#define 	IE40_EMPTY		0x01
#define 	IE41_EMPTY		0x02
#define 	IE42_EMPTY		0x04
#define 	IE43_EMPTY		0x08
#define 	IE44_EXT4		0x10
#define 	IE45_EMPTY		0x20

#define 	IE50_EMPTY		0x01
#define 	IE51_EMPTY		0x02
#define 	IE52_EMPTY		0x04
#define 	IE53_EMPTY		0x08
#define 	IE54_EMPTY		0x10
#define 	IE55_EMPTY		0x20

// SCCR bit aliasing definition
#define STOP1	0x80
#define DIV1	0x40
#define DIV0	0x20
#define CBYS	0x10
#define ISTOP	0x08
#define REDUCEC	0x04
#define REDUCEC_TS	0x02
#define CS		0x01

// WDTMR aliasing definition
#define WDTEN	0x80
#define WDTRSON	0x40
#define WDTCL	0x20
#define WDTIFR	0x01

// IE2 aliasing definition
#define INT17E	0x20		// ROM
#define INT16E	0x10		// BIT
#define INT15E	0x08		// WDT
#define INT14E	0x04		// Reserved
#define INT13E 	0x02		// Timer1
#define INT12E	0x01		// Timer0

//PSR 
#define PSR_UART_P13P14 0x02
#define PSR_I2C_P10P11_OCD 0x00
#define PSR_I2C_P13P14 0x00

#define PSR_I2C_P10P11_18 0x10
#define PSR_I2C_P13P14_18 0x08
#define PSR_I2C_P12_18 0x04

//EIEDGE
#define EDGE0_LEVEL 0x00
#define EDGE0_EDGE 0x01
#define EDGE1_LEVEL 0x00
#define EDGE1_EDGE 0x02
//EIPOLA
#define POLA0_H 0x00
#define POLA0_L 0x01
#define POLA1_H 0x00
#define POLA1_L 0x10
#define POLA0_RISING 0x00
#define POLA0_FALLING 0x01
#define POLA1_RISING 0x00
#define POLA1_FALLING 0x02
//EIENAB
#define ENAB0_DISABLE 0x00
#define ENAB0_ENABLE 0x01
#define ENAB1_DISABLE 0x00
#define ENAB1_ENABLE 0x02
*/
#endif

/* XSFR */
                                                             

 /* LED */                                                             
//=============================================================
#define	COMOE			(*(volatile unsigned char xdata *) 0x2f00)
#define	SEGOE1		(*(volatile unsigned char xdata *) 0x2f01)
#define	SEGOE2		(*(volatile unsigned char xdata *) 0x2f02)
#define	PRESD			(*(volatile unsigned char xdata *) 0x2f03)
#define	CSER			(*(volatile unsigned char xdata *) 0x2f04)
#define	COMPWID		(*(volatile unsigned char xdata *) 0x2f05)
#define	CDIMM0			(*(volatile unsigned char xdata *) 0x2f06)
#define	CDIMM1			(*(volatile unsigned char xdata *) 0x2f07)
#define	CDIMM2			(*(volatile unsigned char xdata *) 0x2f08)
#define	CDIMM3			(*(volatile unsigned char xdata *) 0x2f09)
#define	LEDSTPD0		(*(volatile unsigned char xdata *) 0x2f0A)
#define	LEDSTPD1		(*(volatile unsigned char xdata *) 0x2f0B)
#define	LEDSTPD2		(*(volatile unsigned char xdata *) 0x2f0C)
#define	LEDSR			(*(volatile unsigned char xdata *) 0x2f0D)
#define	LEDCON3		(*(volatile unsigned char xdata *) 0x2f0E)
#define	LEDCON2		(*(volatile unsigned char xdata *) 0x2f0F)
#define	LEDCON1		(*(volatile unsigned char xdata *) 0x2f10)
//#define	COMIOLTESTE1		*(volatile unsigned char xdata *) 0x2F10
//#define	COMIOLTESTE2		*(volatile unsigned char xdata *) 0x2F11
#define	DISPLAYRAM0L		*(volatile unsigned char xdata *) 0x2F13
#define	DISPLAYRAM0M		*(volatile unsigned char xdata *) 0x2F14
#define	DISPLAYRAM1L		*(volatile unsigned char xdata *) 0x2F15
#define	DISPLAYRAM1M		*(volatile unsigned char xdata *) 0x2F16
#define	DISPLAYRAM2L		*(volatile unsigned char xdata *) 0x2F17
#define	DISPLAYRAM2M		*(volatile unsigned char xdata *) 0x2F18
#define	DISPLAYRAM3L		*(volatile unsigned char xdata *) 0x2F19
#define	DISPLAYRAM3M		*(volatile unsigned char xdata *) 0x2F1A
#define	DISPLAYRAM4L		*(volatile unsigned char xdata *) 0x2F1B
#define	DISPLAYRAM4M		*(volatile unsigned char xdata *) 0x2F1C
#define	DISPLAYRAM5L		*(volatile unsigned char xdata *) 0x2F1D
#define	DISPLAYRAM5M		*(volatile unsigned char xdata *) 0x2F1E
#define	DISPLAYRAM6L		*(volatile unsigned char xdata *) 0x2F1F
#define	DISPLAYRAM6M		*(volatile unsigned char xdata *) 0x2F20
#define	DISPLAYRAM7L		*(volatile unsigned char xdata *) 0x2F21
#define	DISPLAYRAM7M		*(volatile unsigned char xdata *) 0x2F22

#define	CCSIREF				*(volatile unsigned char xdata *) 0x2F58
#define	CCSCOARSE		*(volatile unsigned char xdata *) 0x2F30	

// LEDCON1 (LED Control Register)
#define	LEDST	(1<<0)  //LED start 
#define	LEDEN	(1<<1) 

#define	LEDMDAUTO				(0<<2)  //LED mode , 0:LED alone  
#define	LEDMDHANDSHAKE		(1<<2)  //LED mode , 1:Handshake mode 
#define	LEDMDSTOPCOUNT	(2<<2)  //LED mode , 2:Stop Count mode 
#define	LEDMDSMARTSHARE	(3<<2)  //LED mode , 3:Smart Share mode 
#define	LEDMDALONE	(4<<2)  //LED mode , 3:Smart Share mode 

#define	LEDMDMSK	(3<<2)  //LED mode mask, 2bits

// LEDCON2 (LED Control Register)
#define	LEDOVERLAP	(1<<7)  //LED overlap , 1:system clk 

// LEDSR (LED Status Register)
#define	LEDINTE			(1<<1)  //LED INT enable 
#define	LEDINT			(1<<2)  //LED INT
#define	LEDENDF		(1<<0)  //LED END Flag
#define	LEDMATCHF	(1<<3)  //LED MATCH FLAG

// COMR (COM Select Register)
#define 	COM_1SEL	0x01
#define 	COM_2SEL	0x03
#define 	COM_3SEL	0x07
#define 	COM_4SEL	0x0F
#define 	COM_5SEL	0x1F
#define 	COM_6SEL	0x3F
#define 	COM_7SEL	0x7F
#define 	COM_8SEL	0xFF

//COMxL,COMxM,COMxH
#define 	DIGIT0	0x3F
#define 	DIGIT1	0x06
#define 	DIGIT2	0x5B
#define 	DIGIT3	0x4F
#define 	DIGIT4	0x66
#define 	DIGIT5	0x6D
#define 	DIGIT6	0x7D
#define 	DIGIT7	0x07
#define 	DIGIT8	0x7F
#define 	DIGIT9	0x6F
#define 	DIGIT_DOT	0xC0

//=============================================================
#define	FUSE_CONF		*(volatile unsigned char xdata *) 0x2f50
#define	FUSE_CAL0		*(volatile unsigned char xdata *) 0x2f51
#define	FUSE_CAL1		*(volatile unsigned char xdata *) 0x2f52
#define	FUSE_RING		*(volatile unsigned char xdata *) 0x2f53
#define	FUSE_BGR3		*(volatile unsigned char xdata *) 0x2f54
#define	FUSE_FLAG		*(volatile unsigned char xdata *) 0x2f55
#define	FUSE_TOUC		*(volatile unsigned char xdata *) 0x2f56
#define	FUSE_PKG		*(volatile unsigned char xdata *) 0x2f57
#define	TEST_B			*(volatile unsigned char xdata *) 0x2f5E
#define	TEST_A			*(volatile unsigned char xdata *) 0x2f5F

#define	FCHH			*(volatile unsigned char xdata *) 0x2f60
#define	FCHL			*(volatile unsigned char xdata *) 0x2f61
#define	FCLH			*(volatile unsigned char xdata *) 0x2f62
#define	FCLL			*(volatile unsigned char xdata *) 0x2f63
#define	FCMR			*(volatile unsigned char xdata *) 0x2f64
	


//-----------------------------------------------------------------------------	  

/* Touch */                                                             
//=============================================================
//=============================================================
enum{
    SFR_TS_CON = 0x00,	//0x2e80
    SFR_TS_MODE,		//0x2e81
    SFR_TS_SUM_CNT,		//0x2e82
    
    SFR_TS_CH_SEL_H,	//0x2e83
    SFR_TS_CH_SEL_M,	//0x2e84    
    SFR_TS_CH_SEL_L,	//0x2e85
    
    SFR_TS_S1_WIDTH,   //0x2E86  
    SFR_TS_SLP_CON, 	//0x2E87      
    SFR_TS_VREF,	   	//0x2E88  
    SFR_TS_TRIM,	   	//0x2E89  
    
    SFR_TS_CLK_CFG, 	//0x2E8A  
    SFR_TRIM_OSC,	   	//0x2E8B  
    SFR_DELTA_OSC,	   	//0x2E8C  
    SFR_TLED,		  	//0x2E8D      
    
    SFR_TS_VHS_HIGH, //0x2E8E      
    SFR_TS_VHS_LOW,	//0x2E8F 
    SFR_TS_VCOMP_H, //0x2E90  
    SFR_TS_VCOMP_L,	//0x2E91 
    
    SFR_TS_MAX
};

#define _DUMMY 8
typedef struct ts_t418
{
    //volatile unsigned int RAW[TS_MAX_KEY*2];//0x2E00~0x2E4F
    //volatile unsigned int SCO[TS_MAX_KEY];//0x2E50~0x2E77
    //volatile unsigned char DUMMY[8];//0x2E78~0x2E7F
    volatile unsigned int RAW[20*2];//0x2E00~0x2E4F
    volatile unsigned int SCO[20];//0x2E50~0x2E77
    volatile unsigned char DUMMY[8];//0x2E78~0x2E7F
    volatile unsigned char TS[SFR_TS_MAX];//0x2E80~0x2F91
} ts_t418;

#define bSFR	((volatile unsigned char xdata *) 0x2E00)
#define tSFR  ((ts_t418*)bSFR)
#define TS(X) (tSFR->TS[X])
#define TS_SCO(X) (tSFR->SCO[X])
#define TSRAW(X) (tSFR->RAW[X])

//#define T356_SCO_SIZE (3)
#define T418_SCO_SIZE (TS_MAX_KEY)
//#define SFR_A356_SIZE (SFR_TS_MAX+(T356_SCO_SIZE*2)+1)//protocol상 짝수 값을 위해.
#define SFR_T418_SIZE (SFR_TS_MAX+(T418_SCO_SIZE*2)/*+1*/)//protocol상 짝수 값을 위해.

typedef enum{
    TS_RUN = 0x01,
     TS_IF = 0x04, //Touch Sensor Interrupt Flag
//    BGR_EN = 0x08, //BGR enable
    OSC_EN = 0x10, //Oscillator enable
}TS_CON_TYPE;
#define _TS_START (OSC_EN|TS_RUN)

typedef enum{
    PORT_0 = 0x01, //Low, (00 : floating)
    PORT_1 = 0x02, //High
    WDT_STOP = 0x04, //only TS block is waked up by WDT. MCU is still in stop mode.
    SAP_0 = 0x10, //TS
    SAP_1 = 0x20, // ADC. The result of ADC is stored only at SUM_CH0 register
    SC_GAIN = 0x40, //SC_GAIN enable
    SREF = 0x80,//: External reference offset enable
}TS_MODE_TYPE;

typedef enum{
    TSCLKDIV0 = 0x01, //Touch Sensor Clock Divider
    TSCLKDIV1 = 0x02, //000 : OSCts / 1 (27MHz),2,4,8,16,32,64,128
    TSCLKDIV2 = 0x04, //
    TSCLKOE = 0x08, //Divided Touch Sensor Clock Output Enable
    ACLKDIV0 = 0x10, //ADC Clock Divider
    ACLKDIV1 = 0x20, //000 : OSCsys / 1 (16MHz),,2,4,8,16,32,64,128   
    ACLKDIV2 = 0x40, //010 : OSCsys / 4 (4MHz, default)
    ACLKSEL = 0x80, //default(0) 0: Touch clock, 1 : System clock
}TS_CLK_CFG_TYPE;

typedef enum{
    SR_OPEN = 0x00,
    SR_2_5k = 0x01,
    SR_5_0k = 0x02,
    SR_10_0k = 0x04,
    SR_20_0K = 0x08,
    SR_1_3K = 0x0F,
}TS_SVREF_TYPE; //VREF resistor select, 0x0F = 2.6k 

typedef enum{
    SCI_0_2pF = 0x00,
    SCI_0_6pF = 0x01,
    SCI_1_0pF = 0x02,
    SCI_1_4pF = 0x03,
    SCI_1_8pF = 0x04,
    SCI_2_2pF = 0x05,
    SCI_2_6pF = 0x06,
    SCI_3_0pF = 0x07,
}TS_SCI_TYPE;//Input Capacitor Selection

//SCC : Touch Sensor Conversion Capacitor Selection Register
typedef enum{
    SCC_1pF  = 0x00,
    SCC_3pF = 0x01,
    SCC_5pF = 0x02,
    SCC_7pF = 0x03,
    SCC_9pF = 0x04,
    SCC_11pF = 0x05,
    SCC_13pF = 0x06,
    SCC_15pF = 0x07,
}TS_SCC_TYPE;//Conversion Capacitor Selection

#endif	/* _A96T418_H_ */