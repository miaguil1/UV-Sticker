#include "system.h"
#include "guvb_c31sm.h"

//const float vdd_calibration = 3255.01064;  
const float vdd_calibration = 3300.00;   
const float uv_gain = 5; //Gain Resistor Values for Each Photodiode Set in Mega Ohms
const float uv_respons = 113; //Responsitivity of Photodiode in nA / mW/cm^2
const float amp_iov[] = {1, 1}; //Input Offset Voltage of Amplifiers
const float amp_ibc[] = {1, 1}; //Input Bias Current of Amplifiers
const float sg_resistors[] = {1.024, 0.023, 1.02, 1.001, 1.02, 1.02, 1.02, 3300, 3300}; //Resistors(kOhm): {Rx, R1, R2, R3, R4, R5, R6, R7, R8} See "TopDesign.cysch

uint8 uv_Power_Notify = 0;
uint8 uv_Index_Notify = 0;
uint8 temperature_Notify = 0;
uint8 respiration_Notify = 0;
uint8 battery_Notify = 0;


// Set the frequency of the watchdog timer
// f = 32768/x => E.G. (32768/(64*4096) = 0.125 = 1/8 Hz
const uint32 wdt0_frequency = 8; // Refresh frequency for WDT Timer 0: Multiples of 1/8th second 4096 = 1/8th Second
const uint32 wdt1_frequency = 16; // Refresh frequency for WDT Timer 1: Multiples of 1/8th second 4096 = 1/8th Second
const uint32 timer2_toggle = 18;  // bit #18 is the bit for the timer to check. bit #18 = 8 Sec, 1 bit = 1/8th Sec 

void system_init_hardware(void)
{
    UART_Start(); //Starting UART internal communication
    I2C_Start(); //Starting the I2C communication for TMP116 
    //SG_AMP_Start(); //Starting internal Op-amp titled SG_AMP
    UV5_AMP_Start(); //Starting internal Op-amp titled UV5_AMP
    ADC_Start(); //Starting ADC
    CyDelay(10);
    setup_guvb_c31sm(); // Setup GUVB_C31SM
}

void system_red_led_blink()
{
    LED_RED_Write(~LED_RED_Read()); //Turn RED LED the opposite State
    CyDelay(500);
    LED_RED_Write(~LED_RED_Read()); //Turn RED LED the opposite State
}

void system_enable_interrupts(void)
{
    CyGlobalIntEnable;
}

void system_disable_interrupts(void)
{
    CyGlobalIntDisable;
}

void system_sleep(void)
{
    adc_sleep();    // Telling ADC to go into deep sleep mode
    i2c_sleep();    // Telling I2C to go into deep sleep mode
    uart_sleep();   // Telling UART to go into deep sleep mode
    opamp_sleep();  // Telling All Op-Amps to go into deep sleep mode
    CySysPmSleep(); // Telling System to go into sleep mode
    shutdown_guvb_c31sm();  // Shuting down GUVB_C31SM to save power
}

void system_wakeup(void)
{
    adc_wakeup();   // Waking up ADC component from deep sleep mode
    i2c_wakeup();   // Waking up I2C component from deep sleep mode
    uart_wakeup();  // Waking up UART component from deep sleep mode
    opamp_wakeup(); // Waking up All Op-Amps from deep sleep mode
    wakeup_guvb_c31sm();    // Wake up GUVB_C31SM Module from Shutdown
}

void system_deepsleep(void)
{
    CySysPmDeepSleep(); // Telling System to go into deep sleep
}

void adc_conversion(void)
{
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    ADC_StopConvert();   
}

void system_read_i2c(uint32 device_address, uint8 register_address, uint8 *register_value, uint32 register_byte_count)
{
//    uint32 device_address = Right-justified 7-bit Slave address (valid range 8 to 120).
    uint32 i2c_mode_no_stop = I2C_I2C_MODE_NO_STOP; //Transfer Mode Possibilities
    uint32 i2c_mode_repeat_start = I2C_I2C_MODE_REPEAT_START; //Transfer Mode Possibilities
    uint32 i2c_error;
    
    uint8 *address_buffer_value = &register_address;
    uint32 address_buffer_length = 1;    
    
//    Write to the Slave Device the address register you want to read from
    do
    {
        i2c_error =  I2C_I2CMasterWriteBuf(device_address, address_buffer_value, address_buffer_length, i2c_mode_no_stop);        
    }
    while(i2c_error != I2C_I2C_MSTR_NO_ERROR);
    /* Wait for the data transfer to complete */ 
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)); //Wait until the Master has completed reading    
    /* Clear Read Complete Status bit */
    I2C_I2CMasterClearStatus();
    I2C_I2CMasterClearWriteBuf();
    
//    Read from the address register you previously wrote to the Slave Device to read from
    do
    {
        i2c_error = I2C_I2CMasterReadBuf(device_address, register_value, register_byte_count, i2c_mode_repeat_start);
    }
    while(i2c_error != I2C_I2C_MSTR_NO_ERROR);
    /* Wait for the data transfer to complete */   
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_RD_CMPLT)); //Wait until the Master has completed reading    
    /* Clear Read Complete Status bit */
    I2C_I2CMasterClearStatus();
    I2C_I2CMasterClearReadBuf();
}

void system_write_i2c(uint32 device_address, uint8 *buffer_value, uint32 register_byte_count) 
{
//    uint32 device_address = Right-justified 7-bit Slave address (valid range 8 to 120).
//    Register Address and Data Values are contained inside Buffer Value Array
    
    uint32 i2c_mode = I2C_I2C_MODE_COMPLETE_XFER; //I2C Complete Transfer Mode
    uint32 i2c_error;
    do
    {
    i2c_error =  I2C_I2CMasterWriteBuf(device_address, buffer_value, register_byte_count, i2c_mode);        
    }
    while(i2c_error != I2C_I2C_MSTR_NO_ERROR);
    /* Wait for the data transfer to complete */ 
    while(!(I2C_I2CMasterStatus() & I2C_I2C_MSTAT_WR_CMPLT)); //Wait until the Master has completed reading    
    /* Clear Read Complete Status bit */
    I2C_I2CMasterClearStatus();
    I2C_I2CMasterClearWriteBuf();
}
    
uint16 adc_acquire_channel(uint32 channel)
{
    adc_conversion();
    uint16 adc_counts = (uint16) ADC_GetResult16(channel);
    return adc_counts;
}

void adc_sleep(void)
{
    if (ADC_SAR_CTRL_REG  & ADC_ENABLE) 
    { 
        ADC_Sleep(); 
    }     
}

void adc_wakeup(void)
{
    ADC_Wakeup();    
}

void i2c_sleep(void)
{
    I2C_Sleep(); // Prepares the I2C component for Deep Sleep   
}

void i2c_wakeup(void)
{
    I2C_Wakeup(); // Tells the I2C component to Wake Up
}

void uart_sleep(void)
{
    UART_Sleep(); // Prepares the UART component for Deep Sleep
}

void uart_wakeup(void)
{
    UART_Wakeup(); // Tells the UART component to Wake up
}

void opamp_sleep(void)
{
    SG_AMP_Sleep(); // Prepares the SG Op-Amp component for sleep
    UV5_AMP_Sleep();    // Preapres the UV5 Op-Amp component for sleep
}

void opamp_wakeup(void)
{
    SG_AMP_Wakeup();    // Tells the SG Op-Amp component to Wake Up
    UV5_AMP_Wakeup();   // Tells the UV5 Op-Amp component to Wake Up
    
}

//  Start using External WCO
void system_use_wco(void)
{  
    CySysClkWcoStart();     // Start WCO
    CySysClkSetLfclkSource(CY_SYS_CLK_LFCLK_SRC_WCO);   // Select WCO as the clock source
    CySysWdtUnlock();
    CySysClkIloStop();  //Stop ILO (Internal Oscillator)   
    CySysWdtLock();
}
 
//  Start using External ECO
void system_use_eco(void)
{
    CySysClkEcoStart(2000); // 2000 is the timeout period
}
    
// Stop Using ECO
void system_stop_eco(void)
{
    CySysClkEcoStop();
}

void system_set_imo(int mhz)
{
    CySysClkWriteImoFreq(mhz);
}