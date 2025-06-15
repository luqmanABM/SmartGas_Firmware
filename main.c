#include "mcc_generated_files/system/system.h"
#include <string.h>
#include <math.h>


extern volatile unsigned char Activity_Start;   // Declare Activity_Start as extern to access it from tmr1.c
extern volatile unsigned int Timer_Countdown;   // Declare Timer_Countdown as extern
extern volatile bool continueSleep;
extern volatile bool activeConnection;
extern volatile uint16_t flowBased;

//EEPROM Memory Bytes
#define EEPROM_CREDIT_BALANCE (EEPROM_START_ADDRESS + 0x00)
#define EEPROM_TANK_CAPACITY  (EEPROM_START_ADDRESS + 0x05) // +1 byte gap
#define EEPROM_TANK_BALANCE   (EEPROM_START_ADDRESS + 0x0A) // +1 byte gap
#define EEPROM_POWER_CYCLE    (EEPROM_START_ADDRESS + 0x0F) // +1 byte gap
#define EEPROM_FLOW_OFFSET    (EEPROM_START_ADDRESS + 0x14) // +1 byte gap
#define EEPROM_FUEL_COST      (EEPROM_START_ADDRESS + 0x19) // +1 byte gap for good practice to prevent memory write overlap

// Variable Definitions
typedef struct {
    uint8_t aDemo   : 1; // bit0
    uint8_t aValve   : 1; // bit1
    uint8_t aBal    : 1; // bit2
    uint8_t aTank   : 1; // bit3
    uint8_t aBatt   : 1; // bit4
    uint8_t aGeneral: 1; // bit5
} AlarmFlags;
AlarmFlags alarms = {0}; // Initialize all alarms to off (0)

uint32_t pCode = 0x12345678;  // Unique and diverse byte structure
uint16_t pBattV = 0;        // E.g., 60% battery
uint16_t powerCycle; 

uint16_t tankRemainingPercentage = 0; // Example value, max is 100 (Percentage up to 2 decimal points)
uint32_t creditBalance;         //current Credit Balance
uint16_t flowVoltageMV = 0;     //Flow Voltage in MV
uint16_t flowOffset;             // Flow Offset
uint32_t flowJoules;            //Flow Energy In Joules
uint32_t flowCredit;            // Flow Change Rate Value for Money Subtraction
uint8_t  flowNoise = 4;             // Flow Noise
uint32_t fuelCostPerUnit;       //Fuel / Gas Gost Per Unit

uint32_t tankCapacity;  // Tank Maximum Capacity
uint32_t tankBalance;   // Balance Remaining Balance

uint8_t packAlarmFlags(AlarmFlags alarms) {
    // Combine all the individual alarm bits into a single byte
    return (alarms.aGeneral << 5) | (alarms.aBatt << 4) | (alarms.aTank << 3) |
           (alarms.aBal << 2) | (alarms.aValve << 1) | alarms.aDemo;
}

bool ValveManual_Open = true;
bool ValveState_Open = false;
bool isLock = true;  // Lock state
bool SHUTDOWN_FLAG = true;
bool SCREEN_STATE = true;
bool FLOW_STATE_ANALYSIS = false;
//bool continueSleep = true;
int lockCounter = 0; // Counter to track seconds for lock timeout
int SCREEN_ON_TIME = 5;		//X value for Wakeup mode in second
int SCREEN_OFF_TIME = 10;       // X value for Sleep Mode in second
uint16_t eepromWriteCounter = 0;  // Counts elapsed seconds
// Control Lock to Lock or Unlock
void LockControl(void)
{
    // Lock control logic
    if (isLock == false) {
        DC_Boost_SetHigh();
        LOCK_SetDigitalOutput();  // Configure pin as output
        LOCK_SetPushPull();       // Enable push-pull mode for strong signal control
        LOCK_SetPullup();         // Enable pull-up for added stability
        LOCK_SetHigh();           // Set the lock pin high to engage the lock
        LED4_SetHigh();
    } else {
        // Logic for when isLock == true (disengage the lock)
        LOCK_SetLow();            // Disengage the lock by setting the pin low
        // Check if DC_Boost is currently high before setting it low
        if (DC_Boost_GetValue() == 1) {
            DC_Boost_SetLow();    // Turn off DC boost to save power
        }
        LOCK_SetDigitalOutput();  // Ensure pin remains in output mode
        LOCK_SetPushPull();       // Keep push-pull mode for strong signal control
        LED4_SetLow();
    }
}
// Lock Counter function to change unlock state
void incementLockCounter(void)
{
    if (isLock == false) {
        lockCounter++; // Increment the counter
        // Check if 30 seconds have passed
        if (lockCounter >= 15) {
            isLock = true;    // Automatically lock after 15 seconds
            lockCounter = 0; // Reset the counter
        }
    } else {
        // Reset the counter if lock is true
        lockCounter = 0;
    }
}
// Make a delay
void custom_delay_ms(uint16_t duration_ms) {
    while (duration_ms--) {
        __delay_ms(1);  // Delay for 1 millisecond
    }
}
// Make a buze tone
void play_tone(uint16_t frequency, uint16_t duration_ms) {
    uint16_t period = (_XTAL_FREQ / (frequency * 4 * 8)) - 1;  // Calculate PR2
    PWM1_16BIT_WritePeriodRegister(period);  // Set period
    PWM1_16BIT_SetSlice1Output1DutyCycleRegister(period / 2);  // 50% duty cycle
    PWM1_16BIT_LoadBufferRegisters();
    PWM1_16BIT_Enable();  // Enable PWM output

    custom_delay_ms(duration_ms);  // Play tone for the duration

    PWM1_16BIT_SetSlice1Output1DutyCycleRegister(0);  // Stop tone
    PWM1_16BIT_LoadBufferRegisters();
    __delay_ms(50);  // Small gap before the next tone
}
//EEPROM Write uInt32
void EEPROM_WriteUInt32(uint24_t addr, uint32_t value) {
    NVM_UnlockKeySet(UNLOCK_KEY);
    EEPROM_Write(addr + 0, (value >> 24) & 0xFF);
    NVM_UnlockKeyClear();
    while (NVM_IsBusy());

    NVM_UnlockKeySet(UNLOCK_KEY);
    EEPROM_Write(addr + 1, (value >> 16) & 0xFF);
    NVM_UnlockKeyClear();
    while (NVM_IsBusy());

    NVM_UnlockKeySet(UNLOCK_KEY);
    EEPROM_Write(addr + 2, (value >> 8) & 0xFF);
    NVM_UnlockKeyClear();
    while (NVM_IsBusy());

    NVM_UnlockKeySet(UNLOCK_KEY);
    EEPROM_Write(addr + 3, value & 0xFF);
    NVM_UnlockKeyClear();
    while (NVM_IsBusy());
}
// Read 4-byte value from EEPROM
uint32_t EEPROM_ReadUInt32(uint24_t addr) {
    uint8_t b0 = EEPROM_Read(addr + 0);
    uint8_t b1 = EEPROM_Read(addr + 1);
    uint8_t b2 = EEPROM_Read(addr + 2);
    uint8_t b3 = EEPROM_Read(addr + 3);
    return ((uint32_t)b0 << 24) | ((uint32_t)b1 << 16) | ((uint32_t)b2 << 8) | b3;
}
// EEPROM Write uInt16
void EEPROM_WriteUInt16(uint24_t addr, uint16_t value) {
    NVM_UnlockKeySet(UNLOCK_KEY);
    EEPROM_Write(addr, (value >> 8) & 0xFF);
    NVM_UnlockKeyClear();
    while (NVM_IsBusy());

    NVM_UnlockKeySet(UNLOCK_KEY);
    EEPROM_Write(addr + 1, value & 0xFF);
    NVM_UnlockKeyClear();
    while (NVM_IsBusy());
}
// Read 2-byte value from EEPROM
uint16_t EEPROM_ReadUInt16(uint24_t addr) {
    uint8_t b0 = EEPROM_Read(addr);
    uint8_t b1 = EEPROM_Read(addr + 1);
    return ((uint16_t)b0 << 8) | b1;
}
//Get ADC Signal for Flow Offset purpose
float getFlowOffset(void)
{
    // Select ADC Channel (ANA7 for flow measurement)
    ADC_ChannelSelect(ADC_CHANNEL_ANC4);
    //ADC_ChannelSelect(ADC_CHANNEL_ANA7);
    
    __delay_ms(10);

    // Start ADC conversion
    ADC_ConversionStart();
    while (!ADC_IsConversionDone());  // Wait for conversion to complete
    
    // Get ADC result
    adc_result_t adcResult = ADC_ConversionResultGet();
    // Convert ADC result to voltage (2.048V reference, 12-bit ADC)
    float adcVoltage = (adcResult * 2.048) / 4095.0;
    // Convert voltage to flow measurement in millivolts
    float flowMeasurement = adcVoltage * 1000.0;
    
    return flowMeasurement;  // Return the scaled value in millivolts
}

// Valve Stop
void StopValve(void)
{
    VALVE_OPEN_SetLow(); // Stop the opening signal
    VALVE_CLOSE_SetLow(); // Stop the closing signal
}
// Valve Open
void OpenValve(void)
{
    DC_Boost_SetHigh();        // Activate the boost converter for sufficient power
    __delay_ms(100);            // Allow the boost converter to stabilize
    VALVE_CLOSE_SetLow();      // Ensure the close signal is deactivated
    __delay_ms(50);            // Small delay to prevent overlapping signals
    VALVE_OPEN_SetDigitalOutput();
    VALVE_OPEN_SetPushPull();
    VALVE_OPEN_SetPullup();
    VALVE_OPEN_SetHigh();      // Engage the open signal to open the valve
    __delay_ms(2000);           // Time needed for the valve to open fully
    StopValve();              // Stop all signals to avoid continuous driving
    DC_Boost_SetLow();         // Turn off the boost converter to save power
    
}
// Valve Close
void CloseValve(void)
{
    DC_Boost_SetHigh();        // Activate the boost converter for sufficient power
    __delay_ms(100);            // Allow the boost converter to stabilize
    VALVE_OPEN_SetLow();       // Ensure the open signal is deactivated
    VALVE_CLOSE_SetDigitalOutput();
    VALVE_CLOSE_SetPushPull();
    VALVE_CLOSE_SetPullup();
    VALVE_CLOSE_SetHigh();     // Engage the close signal to close the valve
    __delay_ms(2000);           // Time needed for the valve to close fully
    StopValve();              // Stop all signals to avoid continuous driving
    DC_Boost_SetLow();         // Turn off the boost converter to save power
}
//key1 tap
void key1_callback(void) {
    //continueSleep = false;
    // Logic for key1 (RA0) press
    LED2_SetHigh();
    flowOffset = (uint16_t)getFlowOffset();  // Convert to integer
    flowBased = flowOffset+flowNoise;
    play_tone(300, 250);  // Long low tone for 500ms
    EEPROM_WriteUInt16(EEPROM_FLOW_OFFSET, flowOffset);
//    if (ValveManual_Open==true){
//        CloseValve();
//        ValveManual_Open=false;
//    } else {
//        OpenValve();
//        ValveManual_Open=true;
//    }
    LED2_SetLow();
}
//key2 tap
void key2_callback(void) {
    //continueSleep();
    if (isLock == false) {
        // Reset the counter if lock is true
        isLock = true;
        lockCounter = 0;
        LED4_SetLow();
    } else {
        isLock = false;   
        lockCounter = 0; // Reset the counter
    }
    //play_tone(300, 100);  // Long low tone for 500ms
}
void btTX_RX_callback(void) {
   
}
//
// Pin initialize for Mode Sleep
void Mode_Sleep(void)
{
    continueSleep = true;
    
    flowGND_SetLow();
    //batt
    battV_SetLow();
    battV_SetDigitalOutput();
    batGND_SetLow();
    batGND_SetDigitalInput();
    batGND_SetLow();
    batGND_SetDigitalInput();
    //batGND_SetHigh();
    
    INTERRUPT_GlobalInterruptDisable();  // Disable interrupts globally
    
    LED1_SetLow();
    LED2_SetLow();
    LED3_SetLow();
    LED4_SetLow();
    //buzzer
    PWM1_16BIT_Disable();// Disable PWM module (buzzer used)
    buzzer_SetLow();// Set buzzer pin to low and ensure it's a digital output
    buzzer_SetDigitalOutput();
    buzzer_ResetPullup();
    buzzer_SetDigitalMode();
    //dc bosst
    DC_Boost_SetLow();
    DC_Boost_SetDigitalInput();
    // Voltage regulator
    regSW__SetLow();            // Turn off regulator
    regSW__SetDigitalOutput();  // Set pin as output
    regSW__ResetPullup();       // Disable pull-up
    regSW__SetDigitalMode();    // Set pin to digital mode
    // Valve Open
    VALVE_OPEN_SetLow();            // Set VALVE_OPEN low
    VALVE_OPEN_SetDigitalOutput();  // Configure as output
    VALVE_OPEN_ResetPullup();       // Disable pull-up
    VALVE_OPEN_SetDigitalMode();    // Set to digital mode
    // Valve Close
    VALVE_CLOSE_SetLow();           // Set VALVE_CLOSE low
    VALVE_CLOSE_SetDigitalOutput(); // Configure as output
    VALVE_CLOSE_ResetPullup();      // Disable pull-up
    VALVE_CLOSE_SetDigitalMode();   // Set to digital mode
    // Lock control
    LOCK_SetLow();              // Deactivate control signal
    LOCK_SetDigitalOutput();    // Configure as output
    LOCK_ResetPullup();         // Disable pull-up
    LOCK_SetDigitalMode();      // Set to digital mode
//    // Capacitive Button 1
//    Key1_SetLow();
//    Key1_SetDigitalOutput();   // Set btKey as output
//    Key1_ResetPullup();        // Disable pull-up on btKey
//    Key1_SetDigitalMode();     // Set btKey to digital mode    
    // Capacitive Button 2(Lock))
//    Key2_SetLow();
//    Key2_SetDigitalOutput();   // Set btKey as output
//    Key2_ResetPullup();        // Disable pull-up on btKey
//    Key2_SetDigitalMode();     // Set btKey to digital mode
    //bluetooth
    btKey__SetHigh();            // Signal module to enter sleep mode
    btKey__SetDigitalOutput();   // Set btKey as output
    btKey__ResetPullup();        // Disable pull-up on btKey
    btKey__SetDigitalMode();     // Set btKey to digital mode

    btRX_TX_SetLow();            // Deactivate RX pin
    btRX_TX_SetDigitalInput();   // Set RX pin as input
    btRX_TX_ResetPullup();       // Disable pull-up on btRX_TX
    btRX_TX_SetDigitalMode();    // Set btRX_TX to digital mode
    
    btTX_RX_SetLow();            // Deactivate TX pin
    btTX_RX_SetDigitalInput();   // Set TX pin as input
    btTX_RX_SetDigitalMode();    // Set btTX_RX to digital mode
    btTX_RX_ResetPullup();       // Disable pull-up on btTX_RX
    
    btRST__SetLow();             // Ensure reset pin is inactive
    btRST__SetDigitalOutput();   // Configure btRST as output
    btRST__ResetPullup();        // Disable pull-up on btRST
    btRST__SetDigitalMode();     // Set btRST to digital mode
}
// Pin initilize for Mode Active
void Mode_Active(void)
{
    flowGND_SetHigh();
    //batt
    battV_SetLow();
    battV_SetDigitalInput();
    batGND_SetDigitalOutput();
    batGND_SetLow();
    //buzzer
    buzzer_SetDigitalOutput(); // Ensure buzzer pin is set as output
    buzzer_SetPullup();        // (Optional) Enable pull-up if needed for stability
    buzzer_SetDigitalMode();   // Set the pin to digital mode for PWM operation
    PWM1_16BIT_Disable();
    //voltage booster
    DC_Boost_SetDigitalOutput();
    DC_Boost_SetLow();    // DC Boost closed by default
    //Voltage regulator
    regSW__SetDigitalOutput();  // Set pin as output
    regSW__ResetPullup();       // (Optional) Disable pull-up for stability
    regSW__SetDigitalMode();    // Set pin to digital mode
    //valve
    VALVE_OPEN_SetDigitalOutput();
    VALVE_CLOSE_SetDigitalOutput();
    VALVE_OPEN_SetLow();  // Valve closed by default
    VALVE_CLOSE_SetLow(); // Valve closed by default
    // Lock control - Wake-up mode
    LOCK_SetDigitalOutput();    // Ensure pin is output
    LOCK_SetDigitalMode();      // Set pin to digital mode
    LOCK_SetLow();        // Lock ON
    //Bluetooth
    btKey__SetLow();               // Pull KEY pin LOW to wake module
    btKey__SetDigitalOutput();     
    btKey__ResetPullup();          
    btKey__SetDigitalMode();       

    btRST__SetHigh();              // Make sure RESET is not triggered
    btRST__SetDigitalOutput();     
    btRST__ResetPullup();          
    btRST__SetDigitalMode();       

    btRX_TX_SetDigitalInput();     // RX line ready to receive data
    btRX_TX_SetDigitalMode();      
    btRX_TX_SetPullup();           // Pull-up may help if line floating
    btRX_TX_SetHigh();           // Pull-up may help if line floating

    btTX_RX_SetDigitalInput();    // TX line ready to transmit
    btTX_RX_SetDigitalMode();      
    btTX_RX_SetPullup();           // Pull-up may help if line floating
    btTX_RX_SetHigh();             // TX idle state is HIGH
    
    INTERRUPT_GlobalInterruptEnable();  // Re-enable interrupts after wake-up
}
//// Board go to sleep
//void BoardSleep(void)
//{
//    Mode_Sleep();
//    
//    TMR4_TMRInterruptEnable();
//    INTERRUPT_GlobalInterruptEnable();  // Re-enable interrupts after wake-up
//    
//    LED1_SetLow();
//    
//    continueSleep = true;
//    activeConnection = false;
//    TMR4_Start();  // Start Timer4 before entering sleep
//    
//    while (continueSleep)  // Sleep until Timer4 callback updates continueSleep
//    {
//        SLEEP();
//        NOP();
//    }
//
////    SLEEP();  // Enter sleep mode
////    NOP();    // Execute a no-operation after sleep (ensures the MCU continues correctly)
////    
////     while (continueSleep)
////        {
////            SLEEP();
////            NOP();
////        }
//    TMR4_Stop();  // Stop Timer4 after waking up
//    PIR11bits.TMR4IF = 0;
//    Mode_Active();
//}
void BoardSleep(void)
{
    Mode_Sleep();
    LED1_SetLow();
    
    TMR4_TMRInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();  // Re-enable interrupts after wake-up

    continueSleep = true;  
    activeConnection = false;  
    flowBased = flowOffset+flowNoise;
    tmr4State = SLEEP_MODE;  

    TMR4_PeriodSet(0xE2);  // Adjust Timer4 to 15 sec
    TMR4_Start();

    while (continueSleep)  
    {
        SLEEP();
        NOP();
    }

    TMR4_Stop();
    PIR11bits.TMR4IF = 0;
    Mode_Active();
}
//Send WakeUp Request
void sendWakeUp(void)
{
    if (UART3_IsTxReady())
    {
        UART3_Write('U'); // Send the single character 'U' over UART
        //play_tone(1000, 100);  // Long low tone for 500ms
    }
}
// Send Pings communication
void sendPings(void)
{
    if (UART3_IsTxReady())
    {
        uint8_t pAlarm = packAlarmFlags(alarms);
        // Calculate checksum
        uint8_t CS = (uint8_t)(pAlarm + (tankRemainingPercentage & 0xFF) + (tankRemainingPercentage >> 8) + pBattV +
                                (creditBalance & 0xFF) + ((creditBalance >> 8) & 0xFF) +
                                ((creditBalance >> 16) & 0xFF) + (creditBalance >> 24) +
                                (pCode & 0xFF) + ((pCode >> 8) & 0xFF) +
                                ((pCode >> 16) & 0xFF) + (pCode >> 24) +
                                flowVoltageMV);

        // Send data over UART as raw bytes
        UART3_Write('S'); // Send 'S'
        UART3_Write('G'); // Send 'G'
        // Send other data
        UART3_Write(pAlarm);
        UART3_Write((tankRemainingPercentage >> 8) & 0xFF); // pTank.byte1
        UART3_Write(tankRemainingPercentage & 0xFF);        // pTank.byte0
        UART3_Write((pBattV >> 8) & 0xFF); // Send high byte of pBattV
        UART3_Write(pBattV & 0xFF);        // Send low byte of pBattV
        UART3_Write((creditBalance >> 24) & 0xFF); // creditBalance.byte3
        UART3_Write((creditBalance >> 16) & 0xFF); // creditBalance.byte2
        UART3_Write((creditBalance >> 8) & 0xFF);  // creditBalance.byte1
        UART3_Write(creditBalance & 0xFF);         // creditBalance.byte0
        UART3_Write((pCode >> 24) & 0xFF);    // pCode.byte3
        UART3_Write((pCode >> 16) & 0xFF);    // pCode.byte2
        UART3_Write((pCode >> 8) & 0xFF);     // pCode.byte1
        UART3_Write(pCode & 0xFF);            // pCode.byte0
        UART3_Write((flowVoltageMV >> 8) & 0xFF); // Send high byte of flowVoltageMV
        UART3_Write(flowVoltageMV & 0xFF);        // Send low byte of flowVoltageMV
        UART3_Write(CS); // Send checksum
    }
}
//Command success execute
void sendSuccessCommand(void)
{
    if (UART3_IsTxReady())
    {
        UART3_Write('W'); // Send the single character 'U' over UART
        play_tone(1000, 100);  // Long low tone for 500ms
    }
}
// Listen Bluetooth Receiving Data
void listenONDataReceive(void)
{
    static uint8_t rxBuffer[20];  // Buffer for multi-byte commands
    static uint8_t rxIndex = 0;   // Index to track buffer position
    static char currentCommand = '\0'; // Track current command
    static uint8_t expectedBytes = 0;  // Expected payload size
    // Read data only if there is something in the RX buffer
    if (UART3_IsRxReady())
    {
        unsigned char receivedByte = UART3_Read(); // Read a byte from UART

        if (currentCommand == '\0') { // Waiting for a new command
            switch (receivedByte) {
                case 'u': //
                    currentCommand = '\0'; // Reset state
                    rxIndex = 0;
                    Timer_Countdown = 0;
                    SHUTDOWN_FLAG = 0;
                    break;

                case 'N': 
                    currentCommand = 'N'; // Tank Capacity Command
                    rxIndex = 0;          // Reset buffer index
                    expectedBytes = 9; // 4 bytes (code) + 8 bytes (double amount) + 1 checksum
                    break;
                case 'T': // Sentinel for the Top-Up command
                    currentCommand = 'T'; // Enter 'T' command processing state
                    rxIndex = 0;          // Reset buffer index for payload
                    expectedBytes = 9; // 4 bytes (code) + 4 bytes (amount) + 1 checksum
                    break;
                case 'Z': 
                    //currentCommand = 'Z'; 
                    currentCommand = '\0'; // Reset state
                    rxIndex = 0;
                    flowOffset = (uint16_t)getFlowOffset();  // Convert to integer
                    EEPROM_WriteUInt16(EEPROM_FLOW_OFFSET, flowOffset);
                    sendSuccessCommand();
                    break;
                case 'K': // Other command logic
                    currentCommand = '\0'; // Reset state
                    rxIndex = 0;
                    CloseValve();
                    ValveManual_Open=0;
                    sendSuccessCommand();
                    break;
                case 'k': // Other command logic
                    currentCommand = '\0'; // Reset state
                    rxIndex = 0;
                    OpenValve();
                    ValveManual_Open=1;
                    sendSuccessCommand();
                    break;
                case 'C': // using L cause trigger when BT is disconnected
                    currentCommand = '\0'; // Reset state
                    rxIndex = 0;
                    isLock = false;
                    lockCounter = 0; // Reset the counter
                    sendSuccessCommand();
                    //play_tone(300, 100);  // Long low tone for 500ms
                    break;
                case 'c': // Other command logic
                    currentCommand = '\0'; // Reset state
                    rxIndex = 0;
                    isLock = true;
                    lockCounter = 0; // Reset the counter
                    sendSuccessCommand();
                    play_tone(300, 1000);
                    break;
                case 'D': // Another example
                    LED3_Toggle();
                    break;

                default: // Handle undefined commands
                    //LED4_Toggle();
                    break;
            }
        } else if (currentCommand == 'N') { // Receiving data for the 'N' command
            rxBuffer[rxIndex++] = receivedByte; // Store received byte
            if (rxIndex == expectedBytes) { // When full payload is received
                uint32_t receivedTankType = 0;
                uint8_t calculatedChecksum = 0;

                // Calculate checksum (sum of all received bytes except the last one)
                calculatedChecksum += 'N'; // Include sentinel
                for (int i = 0; i < expectedBytes - 1; i++) {
                    calculatedChecksum += rxBuffer[i];
                }
                calculatedChecksum &= 0xFF; // Use LSB

                if (calculatedChecksum == rxBuffer[expectedBytes - 1]) { // Verify checksum
                    char code[5]; // Reserve space for code (4 bytes + null-terminator)
                    
                    // Decode `code` (first 4 bytes)
                    strncpy(code, (char *)rxBuffer, 4);
                    code[4] = '\0'; // Null-terminate
                    // Decode `tankCapacity` (first 4 bytes)
                    receivedTankType = (rxBuffer[4] << 24) |
                                           (rxBuffer[5] << 16) |
                                           (rxBuffer[6] << 8) |
                                            rxBuffer[7];
                }
                
                if (receivedTankType == 12) {
                    tankCapacity = 597060000;
                } else if (receivedTankType == 24) {
                    tankCapacity = 1194120000;
                } else if (receivedTankType == 36) {
                    tankCapacity = 1791180000;
                } else if (receivedTankType == 48) {
                    tankCapacity = 1990200000;
                }
                
                
                tankBalance = tankCapacity;
                EEPROM_WriteUInt32(EEPROM_TANK_CAPACITY, tankCapacity);
                EEPROM_WriteUInt32(EEPROM_TANK_BALANCE, tankBalance);
                currentCommand = '\0'; // Reset state
                rxIndex = 0;           // Reset buffer index
                expectedBytes = 0;     // Reset expected bytes
                sendSuccessCommand();
            }
        }
        else if (currentCommand == 'T') { // Processing 'T' Top-Up command data
            rxBuffer[rxIndex++] = receivedByte; // Store received byte in buffer
            
            if (rxIndex == expectedBytes) { // Full payload received
                uint32_t amount = 0;
                uint32_t CurrentBalance = 0;
                uint8_t checksum = 0;
                // Calculate checksum (sum of all received bytes except the last one)
                checksum += 'T'; // Include sentinel
                for (int i = 0; i < expectedBytes - 1; i++) {
                    checksum += rxBuffer[i];
                }
                checksum &= 0xFF; // Use LSB
                
                if (checksum == rxBuffer[expectedBytes - 1]) { // Verify checksum
                    char code[5]; // Reserve space for code (4 bytes + null-terminator)

                    // Decode `code` (first 4 bytes)
                    strncpy(code, (char *)rxBuffer, 4);
                    code[4] = '\0'; // Null-terminate

                    // Decode `amount` (next 4 bytes)
                    amount = (rxBuffer[4] << 24) |
                             (rxBuffer[5] << 16) |
                             (rxBuffer[6] << 8) |
                             rxBuffer[7];
                }
                EEPROM_WriteUInt32(EEPROM_CREDIT_BALANCE, 0);
                CurrentBalance = creditBalance;
                creditBalance = (amount*10000)+CurrentBalance;//100,000,000
                EEPROM_WriteUInt32(EEPROM_CREDIT_BALANCE, creditBalance);
                currentCommand = '\0';
                rxIndex = 0;
                expectedBytes = 0;
                sendSuccessCommand();
            }
        }
    }
}
// flow adjustment based on threshold/slope
float adjustFlowMeasurement(float flowOrigin) {
    if (flowOrigin < 4) {
        return 0; // Keep values below 4 as zero
    }

    float factor = 1.0;

    // Apply linear scaling based on given threshold values
    if (flowOrigin <= 114) {
        factor = 17.25;
    } else if (flowOrigin <= 452) {
        factor = 5.74;
    } else {
        return 2593; // Cap the value at 2593 when flowMeasurement > 452
    }
    
    return flowOrigin * factor;
}
// get Battery Volt
float getBattery(void)
{
    // Select ADC Channel (ANA7 for flow measurement)
    ADC_ChannelSelect(ADC_CHANNEL_ANB4);
    
    __delay_ms(10);

    // Start ADC conversion
    ADC_ConversionStart();
    while (!ADC_IsConversionDone());  // Wait for conversion to complete
    
    // Get ADC result
    adc_result_t adcResult = ADC_ConversionResultGet();
    
    // Convert ADC result to voltage (2.048V reference, 12-bit ADC)
    float adcVoltage = (adcResult * 2.048) / 4095.0;
    
    // voltage divider
    float batteryVoltage = adcVoltage * (909 + 806) / 806;

    // Convert voltage to flow measurement in millivolts
    float batteryMeasurement = (batteryVoltage * 1000.0)-20;

    return batteryMeasurement;  // Return the scaled value in millivolts
}
//get flow voltage(mv))
float getFlow(void)
{
    flowNoise = 4;
    // Select ADC Channel (e.g., ANA7 for flow measurement)
    ADC_ChannelSelect(ADC_CHANNEL_ANC4);
    //ADC_ChannelSelect(ADC_CHANNEL_ANA7);
    
    __delay_ms(10); // Delay for ADC stabilization

    // Start ADC conversion
    ADC_ConversionStart();
    while (!ADC_IsConversionDone());  // Wait for conversion to complete
    
    // Get ADC result
    adc_result_t adcResult = ADC_ConversionResultGet();
    
    // Convert ADC result to voltage (2.048V reference, 12-bit ADC)
    float adcVoltage = (adcResult * 2.048) / 4095.0; // Assuming Vref+ = 2.048V
    
    // Convert voltage to flow measurement in millivolts
    float flowMeasurement = adcVoltage * 1000.0;

    // Adjust flow measurement based on offset and noise
    if (flowMeasurement > (flowOffset + flowNoise)) {
        flowMeasurement -= (flowOffset + flowNoise); // Subtract offset and noise
    } else {
        flowMeasurement = 0; // Set to zero if below threshold
    }
    
    //flowVoltageMV=adjustFlowMeasurement(flowMeasurement);
    flowVoltageMV = (uint16_t)roundf(adjustFlowMeasurement(flowMeasurement));
    
    return flowVoltageMV; // Ensure correct scaling
}
// convert flow to energy
float convertFlowToJoules(float butaneSLPM) {
    // Convert butane-only flow rate to LPG total
    float LPG_SLPM = butaneSLPM * (100.0 / 70.0); // Adjust for 70% butane, 30% propane

    // Convert SLPM to m³/s
    float LPG_m3_per_s = LPG_SLPM / (1000.0 * 60.0);

    // Energy conversion factor for LPG (MJ/m³)
    float LPG_enthalpy = 102.9e6; // 102.9 MJ/m³ converted to J/m³

    // Calculate total energy (Joules per second)
    return LPG_m3_per_s * LPG_enthalpy / 1000; // Joules per second (Watts)
}
// Calculate Flow Function
float calculateFlow(void) {
    float flowSLPM = getFlow(); // Keep precision instead of truncating
    return convertFlowToJoules(flowSLPM);
}
// Flow and Tank Measurement Function
void FlowAndTankMeasurement(void)
{
    // Get the flow rate in joules
    flowJoules = (int32_t) roundf(calculateFlow());
    flowCredit = flowJoules;
	
    if (tankBalance >= flowJoules && flowJoules > 0 && creditBalance >= flowCredit && creditBalance > 10000) {
        Timer_Countdown = 0;
        SHUTDOWN_FLAG = 0;
        tankBalance -= flowJoules; // Subtract flowJoules from tankBalance
        
        if (FLOW_STATE_ANALYSIS == 0) { // Corrected syntax
            creditBalance -= flowCredit; // Subtract flowCredit from creditBalance
        }
    }
    if (creditBalance <= flowCredit || creditBalance <= 10000) {
        if (ValveState_Open == 1){
            ValveState_Open = 0;
            CloseValve();
            alarms.aValve = 1; // means alarm valve ON ..valve is close
        }
        else {
            alarms.aValve = 0; // means valve is OFF.. valve is open
        }
    } else
    {
        if (ValveState_Open == 0){
            ValveState_Open = 1;
            OpenValve();
            alarms.aValve = 0; // means valve is OFF.. valve is open
        }else {
            alarms.aValve = 1; // means alarm valve ON ..valve is close
        }
    }

    // ' Construct checksum based on the sum of numeric variables
	// 	CS = "T" + "G" + VFlow.byte1 + VFlow.byte0 + FlowC.byte1 + FlowC.byte0 + _
	// 		 Flow_Propane.byte3 + Flow_Propane.byte2 + Flow_Propane.byte1 + Flow_Propane.byte0 + VFlowMassMeter.byte1 + VFlowMassMeter.byte0 + _	
	// 		 Flow_Butane.byte3 + Flow_Butane.byte2 + Flow_Butane.byte1 + Flow_Butane.byte0

	
	// ' Send data over serial, splitting WORD values into high and low bytes
	// IF FLOW_STATE_ANALYSIS = 1 THEN	SEROUT PORTC.6, 2, ["TG", _
	// 								VFO.BYTE1, VFO.BYTE0, _
	// 								VFlow.BYTE1, VFlow.BYTE0, _
	// 								FlowC.BYTE1, FlowC.BYTE0, _ 
	// 								Flow_Propane.byte3, Flow_Propane.byte2, Flow_Propane.byte1, Flow_Propane.byte0, _
	// 								VFlowMassMeter.BYTE1, VFlowMassMeter.BYTE0, _ 
	// 								Flow_Butane.byte3, Flow_Butane.byte2, Flow_Butane.byte1, Flow_Butane.byte0, _
	// 								CS]

    // Calculate the tank remaining percentage
    double percentage = ((double)tankBalance / (double)tankCapacity) * 100.0;
    uint16_t scaledPercentage = (uint16_t)(percentage * 100.0); // Scale to preserve two decimal points
    tankRemainingPercentage = scaledPercentage;
}
//EEPROM Fresh value
void EEPROM_SetupValue(void){
    flowOffset = (uint16_t)getFlowOffset(); // 1st cycle getting flow set
    creditBalance = 0;  //1st cycle set to zero
    tankCapacity = 0;
    tankBalance = 0;
    fuelCostPerUnit = 0;

    EEPROM_WriteUInt16(EEPROM_FLOW_OFFSET, flowOffset);
    __delay_ms(50);
    EEPROM_WriteUInt32(EEPROM_CREDIT_BALANCE, 0);
    __delay_ms(50);
    EEPROM_WriteUInt32(EEPROM_TANK_CAPACITY, 0);
    __delay_ms(50);
    EEPROM_WriteUInt32(EEPROM_TANK_BALANCE, 0);
    __delay_ms(50);
    EEPROM_WriteUInt32(EEPROM_FUEL_COST, 0);
    __delay_ms(50);
}
//EEPROM Load Existing Value
void EEPROM_LoadExistingValue(void){
    flowOffset = EEPROM_ReadUInt16(EEPROM_FLOW_OFFSET); 
    creditBalance = EEPROM_ReadUInt32(EEPROM_CREDIT_BALANCE); 
    tankCapacity = EEPROM_ReadUInt32(EEPROM_TANK_CAPACITY); 
    tankBalance = EEPROM_ReadUInt32(EEPROM_TANK_BALANCE); 
    fuelCostPerUnit = EEPROM_ReadUInt32(EEPROM_FUEL_COST); 
}
// Load and Initialize EEPROM Value 
void LoadOrInitializeEEPROM(void) {  
    // Read powerCycle value from EEPROM
    while (NVM_IsBusy());  // Ensure NVM is idle before operations
    powerCycle = EEPROM_ReadUInt16(EEPROM_POWER_CYCLE);
    __delay_ms(5);
    if (powerCycle >= 1) {  // If powerCycle is 0 or uninitialized, set default values
        powerCycle = powerCycle+1;
        EEPROM_WriteUInt16(EEPROM_POWER_CYCLE, powerCycle);
        EEPROM_LoadExistingValue();
        play_tone(1000, 100);  // Long low tone for 500ms
        play_tone(1000, 100);  // Long low tone for 500ms
    } else {  
        powerCycle = 1;  // Set initial cycle count
        EEPROM_WriteUInt16(EEPROM_POWER_CYCLE, powerCycle);
        EEPROM_SetupValue();
        play_tone(300, 100);  // Long low tone for 500ms
        play_tone(300, 100);  // Long low tone for 500ms
        play_tone(300, 100);  // Long low tone for 500ms
        play_tone(300, 100);  // Long low tone for 500ms
        play_tone(300, 100);  // Long low tone for 500ms
    }
}
// Main Routine Activity
void MainActivity(void)
{
    pBattV = (uint16_t)getBattery();
    FlowAndTankMeasurement();
    sendPings(); // Send data regardless of the condition
    //sendWakeUp();
}
// Program Funxtion Intiiliize
void ProgramInitialize(void)
{
    LoadOrInitializeEEPROM();  // Load or initialize EEPROM values 
}
// Pin initialize
void InitializePins(void)
{
    //DC Board
    DC_Boost_SetDigitalOutput();
    DC_Boost_SetLow();    // DC Boost closed by default
    // Lock
    LOCK_SetDigitalOutput();
    LOCK_SetLow();        // Lock OFF
    // Valve Pin Init
    VALVE_OPEN_SetDigitalOutput();
    VALVE_CLOSE_SetDigitalOutput();
    VALVE_OPEN_SetLow();  // Valve closed by default
    VALVE_CLOSE_SetLow(); // Valve closed by default
    // Batt Pin
    batGND_SetDigitalOutput();
    batGND_SetLow();
    // Flow Pin
    flowGND_SetDigitalOutput();
    // buzzer
    buzzer_SetDigitalMode();
    buzzer_SetDigitalOutput();
    //pwm
    PWM1_16BIT_Disable();
}
// main function (gateway) - program 
int main(void)
{
    SYSTEM_Initialize();
    InitializePins();
    ProgramInitialize();    
    Mode_Active();
    
    EXT_INT0_InterruptEnable();     // Ensure INT0 (Key1) and INT1 (Key2) are enabled
    EXT_INT1_InterruptEnable();     // Ensure INT0 (Key1) and INT1 (Key2) are enabled
    EXT_INT2_InterruptEnable();     // Ensure INT0 (Key1) and INT1 (Key2) are enabled
    
    INT0_SetInterruptHandler(key1_callback); // Set custom handler for Key1
    INT1_SetInterruptHandler(key2_callback); // Set custom handler for Key2
    INT2_SetInterruptHandler(btTX_RX_callback); // Set custom handler for Key2
    while (1)
    {   
       if (Activity_Start == 1) // Check if Activity_Start is set
       {
            Activity_Start = 0; // Reset Activity_Start to prevent continuous toggling
            incementLockCounter();
            
            if (SCREEN_STATE == 1) {
                // If the screen is on and the device is waking up
                LED1_Toggle();
                if (Timer_Countdown < SCREEN_ON_TIME && SHUTDOWN_FLAG == 1) {
                    MainActivity();
                }
                // If the screen is on but still within the allowed active time
                else if (Timer_Countdown < SCREEN_ON_TIME && SHUTDOWN_FLAG == 0) {
                    MainActivity();
                    if (Timer_Countdown >= 5) {
                        //sendWakeUp();
                    }
                }
                // If the screen is on, the timer has expired, and the device is not shutting down
                else if (Timer_Countdown >= SCREEN_ON_TIME && SHUTDOWN_FLAG == 0) {
                    MainActivity();
                    Timer_Countdown = 0;
                    SHUTDOWN_FLAG = 1;
                }
                // If the screen is on, the timer has expired, and the device is shutting down
                else if (Timer_Countdown >= SCREEN_ON_TIME && SHUTDOWN_FLAG == 1) {
                    MainActivity();
                    Timer_Countdown = 0;
                    SHUTDOWN_FLAG = 0;
                    BoardSleep();
                }
                eepromWriteCounter++; // Increment the EEPROM write counter            
                if (eepromWriteCounter >= 600) {    //// If 10 minutes (600 seconds) have passed, trigger EEPROM write
//                    WriteEEPROM = true;  // Set flag to indicate writing is needed
//                    eepromWriteCounter = 0; // Reset counter after writing
//                    EEPROM_Store(); // Call the function to write data to EEPROM
                }
            }
        }
        LockControl();
        listenONDataReceive(); // Listen for incoming data
    }
}