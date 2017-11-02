#include "system.h"

const float vdd_calibration = 3255.01064;   
const float uv_gain[] = {9.94, 9.94, 10.02, 9.91, 10.01}; //Gain Resistor Values for Each Photodiode Set in Mega Ohms
const float uv_respons[] = {113, 69, 69, 181, 181}; //Responsitivity of Photodiode in nA / mW/cm^2
const float amp_iov[] = {1, 1, 1, 1, 1}; //Input Offset Voltage of Amplifiers
const float amp_ibc[] = {1, 1, 1, 1, 1}; //Input Bias Current of Amplifiers
const float sg_resistors[] = {1.024, 0.023, 1.02, 1.001, 1.02, 1.02, 1.02, 3300, 3300}; //Resistors(kOhm): {Rx, R1, R2, R3, R4, R5, R6, R7, R8} See "TopDesign.cysch

void init_hardware(void)
{
    UART_Start(); //Starting UART internal communication
    I2C_TMP116_Start(); //Starting the I2C communication for TMP116 
    SG_AMP_Start(); //Starting internal Op-amp titled SG_AMP
    UV5_AMP_Start(); //Starting internal Op-amp titled UV5_AMP
    ADC_Start(); //Starting ADC
}

void system_enable_interrupts(void)
{
    CyGlobalIntEnable;
}

void system_disable_interrupts(void)
{
    CyGlobalIntDisable;
}

void adc_conversion(void)
{
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    ADC_StopConvert();   
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

void system_sleep(void)
{
    CySysPmSleep();
}

void system_deepsleep(void)
{
    CySysPmDeepSleep();
}

void system_stop_eco(void)
{
    CySysClkEcoStop();
}

void system_set_imo(int mhz)
{
    CySysClkWriteImoFreq(mhz);
}

