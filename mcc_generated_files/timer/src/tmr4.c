/**
 * TMR4 Generated Driver File
 *
 * @file tmr4.c
 * 
 * @ingroup  tmr4
 * 
 * @brief Driver implementation for the TMR4 module.
 *
 * @version Driver Version 4.0.0
 *
 * @version Package Version 5.0.0
 */

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

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

/**
  Section: Included Files
*/

#include <xc.h>
#include "../tmr4.h"
#include "../../system/pins.h"
#include "../../adc/adc.h"

static void (*TMR4_PeriodMatchCallback)(void);
static void TMR4_DefaultPeriodMatchCallback(void);

/**
  Section: TMR4 APIs
*/

volatile bool continueSleep = true;
volatile bool activeConnection = false;
volatile TMR4_State tmr4State = SLEEP_MODE; // Define globally
volatile uint16_t flowBased;

void TMR4_Initialize(void)
{
    T4CLKCON = (4 << _T4CLKCON_T4CS_POSN);  // T4CS LFINTOSC

    T4HLT = (0 << _T4HLT_T4MODE_POSN)   // T4MODE Software control
        | (0 << _T4HLT_T4CKSYNC_POSN)   // T4CKSYNC Not Synchronized
        | (0 << _T4HLT_T4CKPOL_POSN)   // T4CKPOL Rising Edge
        | (0 << _T4HLT_T4PSYNC_POSN);  // T4PSYNC Not Synchronized

    T4RST = (0 << _T4RST_T4RSEL_POSN);  // T4RSEL T4CKIPPS pin

    T4PR = 0x30;    // Period 2.02323s; Frequency 242Hz; Count 48

    T4TMR = 0x0;

    TMR4_PeriodMatchCallback = TMR4_DefaultPeriodMatchCallback;
    
    PIR11bits.TMR4IF = 0;   
    PIE11bits.TMR4IE = 1;

    T4CON = (7 << _T4CON_T4CKPS_POSN)   // T4CKPS 1:128
        | (1 << _T4CON_TMR4ON_POSN)   // TMR4ON on
        | (9 << _T4CON_T4OUTPS_POSN);  // T4OUTPS 1:10
}

void TMR4_Deinitialize(void)
{
    T4CONbits.TMR4ON = 0;
    
    PIR11bits.TMR4IF = 0;	   
    PIE11bits.TMR4IE = 0;		
    
    T4CON = 0x0;
    T4CLKCON = 0x0;
    T4HLT = 0x0;
    T4RST = 0x0;
    T4PR = 0xFF;
    T4TMR =0x0;
}

void TMR4_Start(void)
{   
    T4CONbits.TMR4ON = 1;
}

void TMR4_Stop(void)
{   
    T4CONbits.TMR4ON = 0;
}

void TMR4_ModeSet(TMR4_HLT_MODE mode)
{  
    T4HLTbits.T4MODE = mode;
}

void TMR4_ExtResetSourceSet(TMR4_HLT_EXT_RESET_SOURCE reset)
{   
    T4RSTbits.T4RSEL = reset;
}

uint8_t TMR4_CounterGet(void)
{
    return T4TMR;
}

void TMR4_CounterSet(uint8_t count)
{  
    T4TMR = count;
}

void TMR4_PeriodSet(uint8_t periodVal)
{
    T4PR = periodVal;
}

uint8_t TMR4_PeriodGet(void)
{
    return T4PR;
}

uint8_t TMR4_MaxCountGet(void)
{
    return TMR4_MAX_COUNT;
}

void TMR4_TMRInterruptEnable(void)
{
    PIE11bits.TMR4IE = 1;
}

void TMR4_TMRInterruptDisable(void)
{
    PIE11bits.TMR4IE = 0;
}

void TMR4_ISR(void)
{
    // The ticker is set to 1 -> The callback function gets called every time this ISR executes.
    if(NULL != TMR4_PeriodMatchCallback)
    {
        TMR4_PeriodMatchCallback();
    }
   PIR11bits.TMR4IF = 0;
}

void TMR4_PeriodMatchCallbackRegister(void (* callbackHandler)(void))
{
   TMR4_PeriodMatchCallback = callbackHandler;
}

//static void TMR4_DefaultPeriodMatchCallback(void)
//{
//    continueSleep = true;  // Stop sleep when Timer4 reaches its period
//    //continueSleep = false;  //original
//}
//static void TMR4_DefaultPeriodMatchCallback(void)
//{
//    static uint8_t wakeupAttempt = 0;  // Counter for Bluetooth connection attempts
//
//    // STEP 1: Wake up and activate Bluetooth for checking
//    btTX_RX_SetHigh();
//    btTX_RX_SetDigitalOutput();
//
//    btRST__SetHigh();
//    btRST__SetDigitalOutput();
//
//    wakeupAttempt++;
//
//    // STEP 2: Check Bluetooth connection for 2 seconds
//    uint16_t timeout = 2000;  // 2 seconds in milliseconds
//    uint16_t elapsedTime = 0;
//
//    while (elapsedTime < timeout)  
//    {
//        if (activeConnection)  // If connection detected
//        {
//            continueSleep = false;  // Stay awake
//            wakeupAttempt = 0;  // Reset wakeup counter
//            return;
//        }
//        //__delay_ms(10);  // Small wait to avoid blocking execution
//        elapsedTime += 10;  // Accumulate elapsed time
//    }
//
//    // STEP 3: No connection detected, return to sleep
//    if (wakeupAttempt >= 1)  // If checked once and no connection
//    {
//        wakeupAttempt = 0;  // Reset counter
//        continueSleep = true;  // Continue sleep mode
//    }
//
//    // STEP 4: Turn off Bluetooth pins to save power
//    btTX_RX_SetLow();
//    btTX_RX_SetDigitalInput();
//
//    btRST__SetLow();
//    btRST__SetDigitalOutput();
//}
static void TMR4_DefaultPeriodMatchCallback(void)
{
    if (tmr4State == SLEEP_MODE) 
    {
        // Wake up to check Bluetooth connection
        tmr4State = CHECK_CONNECTION_MODE;
        
        TMR4_PeriodSet(0x7E);  // Adjust Timer4 to 4 sec

        // Activate Flow Pin
        flowGND_SetHigh();
        // Activate Bluetooth pins
        btRST__SetHigh();              // Make sure RESET is not triggered
        btRST__SetDigitalOutput();     
        btRST__ResetPullup();          
        btRST__SetDigitalMode();
        btTX_RX_SetDigitalInput();    // TX line ready to transmit
        btTX_RX_SetDigitalMode();      
        btTX_RX_SetPullup();           // Pull-up may help if line floating
        btTX_RX_SetHigh();             // TX idle state is HIGH
        
        uint16_t flowCurrentValue = (uint16_t)getFlowOffset(); // Read ADC value
        if (flowCurrentValue > flowBased)  // If flow detected
        {
            //continueSleep = false;  // Wake up MCU
            activeConnection = true;
        }
        // Deactivate Flow Pin
        flowGND_SetLow();

        TMR4_Start();  // Start Timer4 for 4 sec check
    } 
    else if (tmr4State == CHECK_CONNECTION_MODE) 
    {
        // Check Bluetooth connection
        if (activeConnection)  
        {
            continueSleep = false;  // Fully wake up
        }

        else
        {
            // No connection found then sleep mode
            tmr4State = SLEEP_MODE;

            // Extend Timer4 period back to 10 sec
            TMR4_PeriodSet(0xE2);  // Adjust Timer4 to approximately 15 sec

            // Deactivate Bluetooth pins to save power
            btTX_RX_SetLow();            // Deactivate TX pin
            btTX_RX_SetDigitalInput();   // Set TX pin as input
            btTX_RX_SetDigitalMode();    // Set btTX_RX to digital mode
            btTX_RX_ResetPullup();       // Disable pull-up on btTX_RX

            btRST__SetLow();             // Ensure reset pin is inactive
            btRST__SetDigitalOutput();   // Configure btRST as output
            btRST__ResetPullup();        // Disable pull-up on btRST
            btRST__SetDigitalMode();     // Set btRST to digital mode
            
            continueSleep = true;  
        }

        TMR4_Start();  // Restart Timer4
    }
}
