/**
  Generated Interrupt Manager Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.c

  @Summary:
    This is the Interrupt Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description:
    This header file provides implementations for global interrupt handling.
    For individual peripheral handlers please see the peripheral driver for
    all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F1619
        Driver Version    :  2.03
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above or later
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

#include "interrupt_manager.h"
#include "mcc.h"

void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        TMR0_ISR();
    }
    else if(INTCONbits.PEIE == 1)
    {
        if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
        {
            ADC_ISR();
        } 
        else if(PIE3bits.CLC3IE == 1 && PIR3bits.CLC3IF == 1)
        {
            CLC3_ISR();
        } 
        else if(PIE4bits.SMT1PRAIE == 1 && PIR4bits.SMT1PRAIF == 1)
        {
            SMT1_PR_ACQ_ISR();
        } 
        else if(PIE1bits.TXIE == 1 && PIR1bits.TXIF == 1)
        {
            EUSART_TxDefaultInterruptHandler();
        } 
        else if(PIE1bits.RCIE == 1 && PIR1bits.RCIF == 1)
        {
            EUSART_RxDefaultInterruptHandler();
        } 
        else if(PIE5bits.PID1EIE == 1 && PIR5bits.PID1EIF == 1)
        {
            MATHACC_Error_ISR();
        } 
        else if(PIE5bits.PID1DIE == 1 && PIR5bits.PID1DIF == 1)
        {
            MATHACC_PID_ISR();
        } 
        else
        {
            //Unhandled Interrupt
        }
    }      
    else
    {
        //Unhandled Interrupt
    }
}
/**
 End of File
*/
