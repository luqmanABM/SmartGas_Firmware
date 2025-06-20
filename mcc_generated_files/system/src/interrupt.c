/**
 * Interrupt Manager Generated Driver File.
 *
 * @file interrupt.c
 * 
 * @ingroup interrupt 
 * 
 * @brief This file contains the API prototypes for the Interrupt Manager driver.
 * 
 * @version Interrupt Manager Driver Version 2.0.4
*/

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../../system/interrupt.h"
#include "../../system/system.h"
#include "../pins.h"
#include "../pins.h"

void (*INT0_InterruptHandler)(void);
void (*INT1_InterruptHandler)(void);
void (*INT2_InterruptHandler)(void);

volatile bool continueSleep = true;
void  INTERRUPT_Initialize (void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    INTCON0bits.IPEN = 0;

    // Clear the interrupt flag
    // Set the external interrupt edge detect
    EXT_INT0_InterruptFlagClear();   
    EXT_INT0_risingEdgeSet();    
    // Set Default Interrupt Handler
    INT0_SetInterruptHandler(INT0_DefaultInterruptHandler);
    EXT_INT0_InterruptEnable();

    // Clear the interrupt flag
    // Set the external interrupt edge detect
    EXT_INT1_InterruptFlagClear();   
    EXT_INT1_fallingEdgeSet();    
    // Set Default Interrupt Handler
    INT1_SetInterruptHandler(INT1_DefaultInterruptHandler);
    EXT_INT1_InterruptEnable();

    // Clear the interrupt flag
    // Set the external interrupt edge detect
    EXT_INT2_InterruptFlagClear();   
    EXT_INT2_fallingEdgeSet();    
    // Set Default Interrupt Handler
    INT2_SetInterruptHandler(INT2_DefaultInterruptHandler);
    EXT_INT2_InterruptEnable();

}

/**
 * @ingroup interrupt
 * @brief Executes whenever a high-priority interrupt is triggered. This routine checks the source of the interrupt and calls the relevant interrupt function.
 * @pre INTERRUPT_Initialize() is already called.
 * @param None.
 * @return None.
 */
void __interrupt() INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(PIE9bits.U3RXIE == 1 && PIR9bits.U3RXIF == 1)
    {
        UART3_RxInterruptHandler();
    }
    else if(PIE9bits.U3IE == 1 && PIR9bits.U3IF == 1)
    {
        UART3_GeneralInterruptHandler();
    }
    else if(PIE9bits.U3TXIE == 1 && PIR9bits.U3TXIF == 1)
    {
        UART3_TxInterruptHandler();
    }
    else if(PIE3bits.TMR1IE == 1 && PIR3bits.TMR1IF == 1)
    {
        TMR1_OverflowISR();
    }
    else if(PIE1bits.INT0IE == 1 && PIR1bits.INT0IF == 1)
    {
        INT0_ISR();
    }
    else if(PIE11bits.TMR4IE == 1 && PIR11bits.TMR4IF == 1)
    {
        TMR4_ISR();
    }
    else if(PIE6bits.INT1IE == 1 && PIR6bits.INT1IF == 1)
    {
        INT1_ISR();
    }
    else if(PIE10bits.INT2IE == 1 && PIR10bits.INT2IF == 1)
    {
        INT2_ISR();
    }
    else if(PIE1bits.ADIE == 1 && PIR1bits.ADIF == 1)
    {
        ADC_ISR();
    }
    else if(PIE2bits.ADTIE == 1 && PIR2bits.ADTIF == 1)
    {
        ADC_ThresholdISR();
    }
    else
    {
        //Unhandled Interrupt
    }
}

void INT0_ISR(void)
{
    EXT_INT0_InterruptFlagClear();
    
    continueSleep = false;  // Exit sleep loop
    // Callback function gets called everytime this ISR executes
    INT0_CallBack();    
}


void INT0_CallBack(void)
{
    // Add your custom callback code here
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}

void INT0_SetInterruptHandler(void (* InterruptHandler)(void)){
    INT0_InterruptHandler = InterruptHandler;
}

void INT0_DefaultInterruptHandler(void){
    // add your INT0 interrupt custom code
    // or set custom function using INT0_SetInterruptHandler()
}
void INT1_ISR(void)
{
    EXT_INT1_InterruptFlagClear();
    
    continueSleep = false;  // Exit sleep loop
    // Callback function gets called everytime this ISR executes
    INT1_CallBack();    
}


void INT1_CallBack(void)
{
    // Add your custom callback code here
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}

void INT1_SetInterruptHandler(void (* InterruptHandler)(void)){
    INT1_InterruptHandler = InterruptHandler;
}

void INT1_DefaultInterruptHandler(void){
    // add your INT1 interrupt custom code
    // or set custom function using INT1_SetInterruptHandler()
}
void INT2_ISR(void)
{
    EXT_INT2_InterruptFlagClear();
    
    if (btKey__GetValue() == LOW)  // Check if Bluetooth is connected
    {
        continueSleep = false;  // Wake up MCU when a device is connected
    }


    // Callback function gets called everytime this ISR executes
    INT2_CallBack();    
}


void INT2_CallBack(void)
{
    // Add your custom callback code here
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}

void INT2_SetInterruptHandler(void (* InterruptHandler)(void)){
    INT2_InterruptHandler = InterruptHandler;
}

void INT2_DefaultInterruptHandler(void){
    // add your INT2 interrupt custom code
    // or set custom function using INT2_SetInterruptHandler()
}

/**
 End of File
*/