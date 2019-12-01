/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F1619
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "stdio.h"

/*
                         Main application
 */


static volatile int32_t edgesWidths[40];
static volatile int16_t edgesCount;
static volatile int16_t acumulatedResult = 0;
static volatile int16_t acumulationCount = 0;

static volatile int16_t edgesCount;
static volatile int32_t edgesWidths[40];

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    ADC_SelectChannel(5);
    TMR2_Start();
    while (1)
    {
    }
}

void AdcInterrupt(void)
{
    int16_t result = 0;
    PIR1bits.ADIF = 0;
    acumulationCount++;
    acumulatedResult += ADC_GetConversionResult();
    if(acumulationCount>=16)
    {
        result = acumulatedResult >> 4;
        acumulationCount = 0;
        acumulatedResult = 0;
        result = result >> 2;
        DAC1_SetOutput(result);
    }
    LATC = 0x00;
}

void Clc3Interrupt(void)
{
    int32_t meanWidth;
    
    if((CLC3CON & 0x20) > 0)
    {
        SMT1CON0 = SMT1CON0 | 0x80; // Enable SMT
        SMT1TMRL = 0x00;
        SMT1TMRU = 0x00;
        SMT1TMRH = 0x00;
    }
    else
    {
        SMT1TMRL = 0x00;
        SMT1TMRU = 0x00;
        SMT1TMRH = 0x00;
        SMT1CON0 = SMT1CON0 & (~0x80); // Disable SMT
        
        if(edgesCount>0)
        {
            meanWidth = 0;
            for(int32_t i=0; i<edgesCount; i++)
            {
                meanWidth = meanWidth + edgesWidths[i];
            }
            meanWidth = meanWidth / edgesCount;
        }
        MATHACC_PIDController(500, meanWidth);
        edgesCount = 0;
    }
}

void MathAccInterrupt(void)
{
    int32_t pwm;
    
    MATHACCResult matr = MATHACC_ResultGet();
  
    int32_t value = ((int32_t)matr.byteLL<<0) |((int32_t)matr.byteLH<<8)
            | ((int32_t)matr.byteHL<<16) | ((int32_t)matr.byteHH<<24);
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
}

void Smt1PrInterrupt(void)
{
    int32_t edge = SMT1_GetCapturedPeriod();
    edgesWidths[edgesCount] = edge;
    edgesCount++;
}

/**
 End of File
*/