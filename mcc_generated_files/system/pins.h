/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA0 aliases
#define Key1_TRIS                 TRISAbits.TRISA0
#define Key1_LAT                  LATAbits.LATA0
#define Key1_PORT                 PORTAbits.RA0
#define Key1_WPU                  WPUAbits.WPUA0
#define Key1_OD                   ODCONAbits.ODCA0
#define Key1_ANS                  ANSELAbits.ANSELA0
#define Key1_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define Key1_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define Key1_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define Key1_GetValue()           PORTAbits.RA0
#define Key1_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define Key1_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define Key1_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define Key1_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define Key1_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define Key1_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define Key1_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define Key1_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set RA1 aliases
#define Key2_TRIS                 TRISAbits.TRISA1
#define Key2_LAT                  LATAbits.LATA1
#define Key2_PORT                 PORTAbits.RA1
#define Key2_WPU                  WPUAbits.WPUA1
#define Key2_OD                   ODCONAbits.ODCA1
#define Key2_ANS                  ANSELAbits.ANSELA1
#define Key2_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define Key2_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define Key2_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define Key2_GetValue()           PORTAbits.RA1
#define Key2_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define Key2_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define Key2_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define Key2_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define Key2_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define Key2_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define Key2_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define Key2_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RA2 aliases
#define btRST__TRIS                 TRISAbits.TRISA2
#define btRST__LAT                  LATAbits.LATA2
#define btRST__PORT                 PORTAbits.RA2
#define btRST__WPU                  WPUAbits.WPUA2
#define btRST__OD                   ODCONAbits.ODCA2
#define btRST__ANS                  ANSELAbits.ANSELA2
#define btRST__SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define btRST__SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define btRST__Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define btRST__GetValue()           PORTAbits.RA2
#define btRST__SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define btRST__SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define btRST__SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define btRST__ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define btRST__SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define btRST__SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define btRST__SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define btRST__SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set RA3 aliases
#define btKey__TRIS                 TRISAbits.TRISA3
#define btKey__LAT                  LATAbits.LATA3
#define btKey__PORT                 PORTAbits.RA3
#define btKey__WPU                  WPUAbits.WPUA3
#define btKey__OD                   ODCONAbits.ODCA3
#define btKey__ANS                  ANSELAbits.ANSELA3
#define btKey__SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define btKey__SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define btKey__Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define btKey__GetValue()           PORTAbits.RA3
#define btKey__SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define btKey__SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define btKey__SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define btKey__ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define btKey__SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define btKey__SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define btKey__SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define btKey__SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RA4 aliases
#define btRX_TX_TRIS                 TRISAbits.TRISA4
#define btRX_TX_LAT                  LATAbits.LATA4
#define btRX_TX_PORT                 PORTAbits.RA4
#define btRX_TX_WPU                  WPUAbits.WPUA4
#define btRX_TX_OD                   ODCONAbits.ODCA4
#define btRX_TX_ANS                  ANSELAbits.ANSELA4
#define btRX_TX_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define btRX_TX_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define btRX_TX_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define btRX_TX_GetValue()           PORTAbits.RA4
#define btRX_TX_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define btRX_TX_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define btRX_TX_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define btRX_TX_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define btRX_TX_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define btRX_TX_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define btRX_TX_SetAnalogMode()      do { ANSELAbits.ANSELA4 = 1; } while(0)
#define btRX_TX_SetDigitalMode()     do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set RA5 aliases
#define btTX_RX_TRIS                 TRISAbits.TRISA5
#define btTX_RX_LAT                  LATAbits.LATA5
#define btTX_RX_PORT                 PORTAbits.RA5
#define btTX_RX_WPU                  WPUAbits.WPUA5
#define btTX_RX_OD                   ODCONAbits.ODCA5
#define btTX_RX_ANS                  ANSELAbits.ANSELA5
#define btTX_RX_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define btTX_RX_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define btTX_RX_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define btTX_RX_GetValue()           PORTAbits.RA5
#define btTX_RX_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define btTX_RX_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define btTX_RX_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define btTX_RX_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define btTX_RX_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define btTX_RX_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define btTX_RX_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define btTX_RX_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RA6 aliases
#define flowGND_TRIS                 TRISAbits.TRISA6
#define flowGND_LAT                  LATAbits.LATA6
#define flowGND_PORT                 PORTAbits.RA6
#define flowGND_WPU                  WPUAbits.WPUA6
#define flowGND_OD                   ODCONAbits.ODCA6
#define flowGND_ANS                  ANSELAbits.ANSELA6
#define flowGND_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define flowGND_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define flowGND_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define flowGND_GetValue()           PORTAbits.RA6
#define flowGND_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define flowGND_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define flowGND_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define flowGND_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define flowGND_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define flowGND_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define flowGND_SetAnalogMode()      do { ANSELAbits.ANSELA6 = 1; } while(0)
#define flowGND_SetDigitalMode()     do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set RA7 aliases
#define flowV_AN_TRIS                 TRISAbits.TRISA7
#define flowV_AN_LAT                  LATAbits.LATA7
#define flowV_AN_PORT                 PORTAbits.RA7
#define flowV_AN_WPU                  WPUAbits.WPUA7
#define flowV_AN_OD                   ODCONAbits.ODCA7
#define flowV_AN_ANS                  ANSELAbits.ANSELA7
#define flowV_AN_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define flowV_AN_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define flowV_AN_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define flowV_AN_GetValue()           PORTAbits.RA7
#define flowV_AN_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define flowV_AN_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define flowV_AN_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define flowV_AN_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define flowV_AN_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define flowV_AN_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define flowV_AN_SetAnalogMode()      do { ANSELAbits.ANSELA7 = 1; } while(0)
#define flowV_AN_SetDigitalMode()     do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set RB0 aliases
#define LOCK_TRIS                 TRISBbits.TRISB0
#define LOCK_LAT                  LATBbits.LATB0
#define LOCK_PORT                 PORTBbits.RB0
#define LOCK_WPU                  WPUBbits.WPUB0
#define LOCK_OD                   ODCONBbits.ODCB0
#define LOCK_ANS                  ANSELBbits.ANSELB0
#define LOCK_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define LOCK_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define LOCK_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define LOCK_GetValue()           PORTBbits.RB0
#define LOCK_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define LOCK_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define LOCK_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define LOCK_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define LOCK_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define LOCK_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define LOCK_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define LOCK_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 aliases
#define VALVE_OPEN_TRIS                 TRISBbits.TRISB1
#define VALVE_OPEN_LAT                  LATBbits.LATB1
#define VALVE_OPEN_PORT                 PORTBbits.RB1
#define VALVE_OPEN_WPU                  WPUBbits.WPUB1
#define VALVE_OPEN_OD                   ODCONBbits.ODCB1
#define VALVE_OPEN_ANS                  ANSELBbits.ANSELB1
#define VALVE_OPEN_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define VALVE_OPEN_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define VALVE_OPEN_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define VALVE_OPEN_GetValue()           PORTBbits.RB1
#define VALVE_OPEN_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define VALVE_OPEN_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define VALVE_OPEN_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define VALVE_OPEN_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define VALVE_OPEN_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define VALVE_OPEN_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define VALVE_OPEN_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define VALVE_OPEN_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 aliases
#define VALVE_CLOSE_TRIS                 TRISBbits.TRISB2
#define VALVE_CLOSE_LAT                  LATBbits.LATB2
#define VALVE_CLOSE_PORT                 PORTBbits.RB2
#define VALVE_CLOSE_WPU                  WPUBbits.WPUB2
#define VALVE_CLOSE_OD                   ODCONBbits.ODCB2
#define VALVE_CLOSE_ANS                  ANSELBbits.ANSELB2
#define VALVE_CLOSE_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define VALVE_CLOSE_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define VALVE_CLOSE_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define VALVE_CLOSE_GetValue()           PORTBbits.RB2
#define VALVE_CLOSE_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define VALVE_CLOSE_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define VALVE_CLOSE_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define VALVE_CLOSE_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define VALVE_CLOSE_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define VALVE_CLOSE_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define VALVE_CLOSE_SetAnalogMode()      do { ANSELBbits.ANSELB2 = 1; } while(0)
#define VALVE_CLOSE_SetDigitalMode()     do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB4 aliases
#define battV_TRIS                 TRISBbits.TRISB4
#define battV_LAT                  LATBbits.LATB4
#define battV_PORT                 PORTBbits.RB4
#define battV_WPU                  WPUBbits.WPUB4
#define battV_OD                   ODCONBbits.ODCB4
#define battV_ANS                  ANSELBbits.ANSELB4
#define battV_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define battV_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define battV_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define battV_GetValue()           PORTBbits.RB4
#define battV_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define battV_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define battV_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define battV_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define battV_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define battV_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define battV_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define battV_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set RB5 aliases
#define batGND_TRIS                 TRISBbits.TRISB5
#define batGND_LAT                  LATBbits.LATB5
#define batGND_PORT                 PORTBbits.RB5
#define batGND_WPU                  WPUBbits.WPUB5
#define batGND_OD                   ODCONBbits.ODCB5
#define batGND_ANS                  ANSELBbits.ANSELB5
#define batGND_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define batGND_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define batGND_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define batGND_GetValue()           PORTBbits.RB5
#define batGND_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define batGND_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define batGND_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define batGND_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define batGND_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define batGND_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define batGND_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define batGND_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RB6 aliases
#define PGC_TRIS                 TRISBbits.TRISB6
#define PGC_LAT                  LATBbits.LATB6
#define PGC_PORT                 PORTBbits.RB6
#define PGC_WPU                  WPUBbits.WPUB6
#define PGC_OD                   ODCONBbits.ODCB6
#define PGC_ANS                  ANSELBbits.ANSELB6
#define PGC_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define PGC_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define PGC_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define PGC_GetValue()           PORTBbits.RB6
#define PGC_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define PGC_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define PGC_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define PGC_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define PGC_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define PGC_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define PGC_SetAnalogMode()      do { ANSELBbits.ANSELB6 = 1; } while(0)
#define PGC_SetDigitalMode()     do { ANSELBbits.ANSELB6 = 0; } while(0)

// get/set RB7 aliases
#define PGD_TRIS                 TRISBbits.TRISB7
#define PGD_LAT                  LATBbits.LATB7
#define PGD_PORT                 PORTBbits.RB7
#define PGD_WPU                  WPUBbits.WPUB7
#define PGD_OD                   ODCONBbits.ODCB7
#define PGD_ANS                  ANSELBbits.ANSELB7
#define PGD_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define PGD_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define PGD_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define PGD_GetValue()           PORTBbits.RB7
#define PGD_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define PGD_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define PGD_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define PGD_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define PGD_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define PGD_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define PGD_SetAnalogMode()      do { ANSELBbits.ANSELB7 = 1; } while(0)
#define PGD_SetDigitalMode()     do { ANSELBbits.ANSELB7 = 0; } while(0)

// get/set RC0 aliases
#define LED1_TRIS                 TRISCbits.TRISC0
#define LED1_LAT                  LATCbits.LATC0
#define LED1_PORT                 PORTCbits.RC0
#define LED1_WPU                  WPUCbits.WPUC0
#define LED1_OD                   ODCONCbits.ODCC0
#define LED1_ANS                  ANSELCbits.ANSELC0
#define LED1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LED1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define LED1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LED1_GetValue()           PORTCbits.RC0
#define LED1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define LED1_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define LED1_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define LED1_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define LED1_SetAnalogMode()      do { ANSELCbits.ANSELC0 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set RC1 aliases
#define LED2_TRIS                 TRISCbits.TRISC1
#define LED2_LAT                  LATCbits.LATC1
#define LED2_PORT                 PORTCbits.RC1
#define LED2_WPU                  WPUCbits.WPUC1
#define LED2_OD                   ODCONCbits.ODCC1
#define LED2_ANS                  ANSELCbits.ANSELC1
#define LED2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED2_GetValue()           PORTCbits.RC1
#define LED2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define LED2_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define LED2_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define LED2_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define LED2_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set RC2 aliases
#define buzzer_TRIS                 TRISCbits.TRISC2
#define buzzer_LAT                  LATCbits.LATC2
#define buzzer_PORT                 PORTCbits.RC2
#define buzzer_WPU                  WPUCbits.WPUC2
#define buzzer_OD                   ODCONCbits.ODCC2
#define buzzer_ANS                  ANSELCbits.ANSELC2
#define buzzer_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define buzzer_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define buzzer_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define buzzer_GetValue()           PORTCbits.RC2
#define buzzer_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define buzzer_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define buzzer_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define buzzer_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define buzzer_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define buzzer_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define buzzer_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define buzzer_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 aliases
#define regSW__TRIS                 TRISCbits.TRISC3
#define regSW__LAT                  LATCbits.LATC3
#define regSW__PORT                 PORTCbits.RC3
#define regSW__WPU                  WPUCbits.WPUC3
#define regSW__OD                   ODCONCbits.ODCC3
#define regSW__ANS                  ANSELCbits.ANSELC3
#define regSW__SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define regSW__SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define regSW__Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define regSW__GetValue()           PORTCbits.RC3
#define regSW__SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define regSW__SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define regSW__SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define regSW__ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define regSW__SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define regSW__SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define regSW__SetAnalogMode()      do { ANSELCbits.ANSELC3 = 1; } while(0)
#define regSW__SetDigitalMode()     do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 aliases
#define flowV_TRIS                 TRISCbits.TRISC4
#define flowV_LAT                  LATCbits.LATC4
#define flowV_PORT                 PORTCbits.RC4
#define flowV_WPU                  WPUCbits.WPUC4
#define flowV_OD                   ODCONCbits.ODCC4
#define flowV_ANS                  ANSELCbits.ANSELC4
#define flowV_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define flowV_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define flowV_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define flowV_GetValue()           PORTCbits.RC4
#define flowV_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define flowV_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define flowV_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define flowV_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define flowV_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define flowV_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define flowV_SetAnalogMode()      do { ANSELCbits.ANSELC4 = 1; } while(0)
#define flowV_SetDigitalMode()     do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 aliases
#define LED3_TRIS                 TRISCbits.TRISC5
#define LED3_LAT                  LATCbits.LATC5
#define LED3_PORT                 PORTCbits.RC5
#define LED3_WPU                  WPUCbits.WPUC5
#define LED3_OD                   ODCONCbits.ODCC5
#define LED3_ANS                  ANSELCbits.ANSELC5
#define LED3_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define LED3_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define LED3_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define LED3_GetValue()           PORTCbits.RC5
#define LED3_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define LED3_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define LED3_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define LED3_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define LED3_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define LED3_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define LED3_SetAnalogMode()      do { ANSELCbits.ANSELC5 = 1; } while(0)
#define LED3_SetDigitalMode()     do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 aliases
#define LED4_TRIS                 TRISCbits.TRISC6
#define LED4_LAT                  LATCbits.LATC6
#define LED4_PORT                 PORTCbits.RC6
#define LED4_WPU                  WPUCbits.WPUC6
#define LED4_OD                   ODCONCbits.ODCC6
#define LED4_ANS                  ANSELCbits.ANSELC6
#define LED4_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define LED4_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define LED4_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define LED4_GetValue()           PORTCbits.RC6
#define LED4_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define LED4_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define LED4_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define LED4_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define LED4_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define LED4_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define LED4_SetAnalogMode()      do { ANSELCbits.ANSELC6 = 1; } while(0)
#define LED4_SetDigitalMode()     do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set RC7 aliases
#define DC_Boost_TRIS                 TRISCbits.TRISC7
#define DC_Boost_LAT                  LATCbits.LATC7
#define DC_Boost_PORT                 PORTCbits.RC7
#define DC_Boost_WPU                  WPUCbits.WPUC7
#define DC_Boost_OD                   ODCONCbits.ODCC7
#define DC_Boost_ANS                  ANSELCbits.ANSELC7
#define DC_Boost_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define DC_Boost_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define DC_Boost_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define DC_Boost_GetValue()           PORTCbits.RC7
#define DC_Boost_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define DC_Boost_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define DC_Boost_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define DC_Boost_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define DC_Boost_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define DC_Boost_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define DC_Boost_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define DC_Boost_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/