/**
  MATHACC Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    mathacc.h

  @Summary
    This is the generated header file for the MATHACC driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs driver for MATHACC.
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

#ifndef MATHACC_H
#define MATHACC_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
 Section: Data Type Definitions
*/

/**
  MATHACC result structure

  @Summary
    Define result structure for math acc results

  @Description
    This structure is to collect results  for MATHACC mode operation and
    add & multiply operations of MATHACC module. The mentioned module
    have 36 bits result which is mapped into the structure.

 */
typedef struct
{
    uint8_t byteLL;
    uint8_t byteLH;
    uint8_t byteHL;
    uint8_t byteHH;
    uint8_t byteU;
} MATHACCResult;

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Interface Routines
*/
        
/**
  @Summary
    Initializes the MATHACC module

  @Description
    This routine initializes the MATHACC module

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    MATHACCResult result;

    MATHACC_Initialize();
    MATHACC_PIDController(0x0f, 0xf0);
    // have some other application code running here..

    // completion of MATHACC module operation triggers the module interrupt, now
    // read the result.
    result = MATHACC_ResultGet();
    </code>
*/
void MATHACC_Initialize(void);

/**
  @Summary
    Starts PID calculation

  @Description
    This function triggers the module to start PID caculation.

  @Preconditions
    K1, K2, and K3 values should be calculated and loaded to respective module
    registers, such as, PIDK1, PIDK2, and PIDK3.

    Load PIDZ1, and PIDZ2 registers if applicable.

  @Param
    setpoint - PID Setpoint data
    input    - PID input data

  @Returns
    None

  @Example
    <code>
    Refer MATHACC_Initialize() example
    </code>
*/
void MATHACC_PIDController(int16_t setpoint, int16_t input);

/**
  @Summary
    Get the value of Z1 register

  @Description
    Get the value of Z1 register

  @Preconditions
    None

  @Param
    None

  @Returns
    Returns 17bit value of Z1 register

  @Example
    <code>
    uint32_t value = MATHACC_Z1Get();
    </code>
*/
uint32_t MATHACC_Z1Get(void);

/**
  @Summary
    Get the value of Z2 register

  @Description
    Get the value of Z2 register

  @Preconditions
    None

  @Param
    None

  @Returns
    Returns 17bit value of Z1 register

   @Example
    <code>
    uint32_t value = MATHACC_Z2Get();
    </code>
*/
uint32_t MATHACC_Z2Get(void);

/**
  @Summary
    Load a value to Z1 register

  @Description
    Load a value to Z1 register

  @Preconditions
    None

  @Param
    value - 17bit value to be loaded to Z1 register

  @Returns
    None

  @Example
    <code>
    MATHACC_LoadZ1(0x10000);
    </code>
*/
void MATHACC_LoadZ1(uint32_t value);

/**
  @Summary
    Load a value to Z2 register

  @Description
    Load a value to Z2 register

  @Preconditions
    None

  @Param
    value - 17bit value to be loaded to Z2 register

  @Returns
    None

   @Example
    <code>
    MATHACC_LoadZ2(0x10000);
    </code>
*/
void MATHACC_LoadZ2(uint32_t value);

/**
  @Summary
    Read the result

  @Description
    Read the result available in PIDOUT registers.

  @Preconditions
    None

  @Param
    None

  @Returns
    Return the result of type 'MATHACCResult'

  @Example
    <code>
    MATHACCResult result = MATHACC_ResultGet();
    </code>
*/
MATHACCResult MATHACC_ResultGet(void);

/**
  @Summary
    Clear the result

  @Description
    Clear the result by clearing PIDOUT registers.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Example
    <code>
    MATHACC_ClearResult();
    </code>
*/
void MATHACC_ClearResult(void);

/**
  @Summary
    Math Accelerator module error interrupt routine

  @Description
    This function will be invoked on error overflow during module operation
*/
void MATHACC_Error_ISR( void );

/**
  @Summary
    Math Accelerator module interrupt routine

  @Description
    This function will be invoked on completion of module operation
*/
void MATHACC_PID_ISR( void );

#ifdef __cplusplus  // Provide C++ Compatibility

}
#endif
#endif /*_MATHACC_H*/

