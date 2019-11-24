/**
  MATHACC Generated Driver  File

  @Company
    Microchip Technology Inc.

  @File Name
    mathacc.c

  @Summary
    This is the generated driver implementation for the MATHACC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides APIs for MATHACC.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F1619
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "mathacc.h"
#include "pwm3.h"

/**
  Section: MATHACC APIs
*/

void MATHACC_Initialize(void)
{
    // set the PID module to the options selected in the User Interface
    // PID1MODE PID Controller; PID1EN enabled; 
    PID1CON = 0x85;
    
    
    PID1K1H = (uint8_t) ((1213 & 0xFF00) >> 8);
    PID1K1L = (uint8_t)  (1213 & 0x00FF);
    PID1K2H = (uint8_t) ((-1841 & 0xFF00) >> 8);
    PID1K2L = (uint8_t)  (-1841 & 0x00FF);
    PID1K3H = (uint8_t) ((703 & 0xFF00) >> 8);
    PID1K3L = (uint8_t)  (703 & 0x00FF);

    PIR5bits.PID1DIF = 0;
    PIR5bits.PID1EIF = 0;
    PIE5bits.PID1DIE = 1;
    PIE5bits.PID1EIE = 1;
}

void MATHACC_PIDController(int16_t setpoint, int16_t input)
{
    PID1SETH = (uint8_t) (((uint16_t)setpoint & 0xFF00) >> 8);
    PID1SETL = (uint8_t)  (setpoint & 0x00FF);   
    PID1INH  = (uint8_t) (((uint16_t)input & 0xFF00) >> 8);
    PID1INL  = (uint8_t)  (input & 0x00FF);   // starts module operation
}
         

uint32_t MATHACC_Z1Get(void)
{
    uint32_t value = 0;

    value = (uint32_t)PID1Z1L & 0x000000FF;
    value = (value | ((uint32_t)PID1Z1H << 8)) & 0x0000FFFF;
    value = (value | ((uint32_t)PID1Z1U << 16)) & 0x0001FFFF;

    return value;
}

uint32_t MATHACC_Z2Get(void)
{
    uint32_t value = 0;

    value = (uint32_t)PID1Z2L & 0x000000FF;
    value = (value | ((uint32_t)PID1Z2H << 8)) & 0x0000FFFF;
    value = (value | ((uint32_t)PID1Z2U << 16)) & 0x0001FFFF;

    return value;
}

void MATHACC_LoadZ1(uint32_t value)
{
    PID1Z1L = (0x000000FF & value);
    PID1Z1H = ((0x0000FF00 & value)>>8);
    PID1Z1U = ((0x00010000 & value)>>16);
}

void MATHACC_LoadZ2(uint32_t value)
{
    PID1Z2L = (0x000000FF & value);
    PID1Z2H = ((0x0000FF00 & value)>>8);
    PID1Z2U = ((0x00010000 & value)>>16);
}

MATHACCResult MATHACC_ResultGet(void)
{
    MATHACCResult data;

    data.byteLL = PID1OUTLL;
    data.byteLH = PID1OUTLH;
    data.byteHL = PID1OUTHL;
    data.byteHH = PID1OUTHH;
    data.byteU = PID1OUTU;

    return data;
}

void MATHACC_ClearResult(void)
{
    PID1OUTLL = 0;
    PID1OUTLH = 0;
    PID1OUTHL = 0;
    PID1OUTHH = 0;
    PID1OUTU  = 0;
}

void MATHACC_Error_ISR( void )
{
    PIR5bits.PID1EIF = 0;
    
    // user code here for error handling
}

volatile int32_t pwm = 300;
volatile bool newValue;
volatile uint8_t a,b,c,d;
volatile int32_t value;

void MATHACC_PID_ISR( void )
{
    PIR5bits.PID1DIF = 0;

    MATHACCResult matr = MATHACC_ResultGet();


    a = matr.byteLL;
    b = matr.byteLH;
    c = matr.byteHL;
    d = matr.byteHH;
    
    value = ((int32_t)a<<0) |((int32_t)b<<8) | ((int32_t)c<<16) | ((int32_t)d<<24);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    value = value / 256;
    pwm = 450 - value;
    if(pwm<100)
    {
        pwm = 100;
    }
    if(pwm>800)
    {
        pwm = 800;
    }
    PWM3_LoadDutyValue(pwm);
    // user code here    
}
// end of file
     
        

        
