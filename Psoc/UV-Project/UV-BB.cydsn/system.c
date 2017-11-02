/*
File Name: system.c
Overall Psoc System Commands
Measures the Temperature of The Source
Functions:
-init_hardware()
    Summary:
        This function starts all the necessary internal hardware components of the psoc
    Parameters:
        None
    Return:
        None
    
-system_enable_interrupts()
    Summary:
        This function enables all interrupts in the Psoc
    Parameters:
        None
    Return:
        None
    
-system_disable_interrupts()
    Summary:
        This function disables all interrupts in the Psoc
    Parameters:
        None
    Return:
        None
    
-adc_conversion()
    Summary:
        This function starts an ADC Conversion then waits until its over
    Parameters:
        None
    Return:
        None
*/    

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
    //I2C_TMP116_Start(); //Starting the I2C communication for TMP116 
    //SG_AMP_Start(); //Starting internal Op-amp titled SG_AMP
    //UV5_AMP_Start(); //Starting internal Op-amp titled UV5_AMP
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








/*******************************************************************************
* Function Name: LowPowerImplementation()
********************************************************************************
* Summary:
* Implements low power in the project.
*
* Parameters:
* None
*
* Return:
* None
*
* Theory:
* The function tries to enter deep sleep as much as possible - whenever the 
* BLE is idle and the UART transmission/reception is not happening. At all other
* times, the function tries to enter CPU sleep.
*
*******************************************************************************/
static void LowPowerImplementation(void)
{
    CYBLE_LP_MODE_T bleMode;
    uint8 interruptStatus;
    
    /* For advertising and connected states, implement deep sleep 
     * functionality to achieve low power in the system. For more details
     * on the low power implementation, refer to the Low Power Application 
     * Note.
     */
    if((CyBle_GetState() == CYBLE_STATE_ADVERTISING) || (CyBle_GetState() == CYBLE_STATE_CONNECTED))
    {
        /* Request BLE subsystem to enter into Deep-Sleep mode between connection and advertising intervals */
        bleMode = CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
        /* Disable global interrupts */
        interruptStatus = CyEnterCriticalSection();
        /* When BLE subsystem has been put into Deep-Sleep mode */
        if(bleMode == CYBLE_BLESS_DEEPSLEEP)
        {
            /* And it is still there or ECO is on */
//            if((CyBle_GetBleSsState() == CYBLE_BLESS_STATE_ECO_ON) || (CyBle_GetBleSsState() == CYBLE_BLESS_STATE_DEEPSLEEP))
//            {
//            #if (DEBUG_UART_ENABLED == ENABLED)
//                /* Put the CPU into the Deep-Sleep mode when all debug information has been sent */
//                if((UART_DEB_SpiUartGetTxBufferSize()) == 0u)
//                {
//                    CySysPmDeepSleep();
//                }
//                else /* Put the CPU into Sleep mode and let SCB to continue sending debug data */
//                {
//                    CySysPmSleep();
//                }
//            #else
//                CySysPmDeepSleep();
//            #endif /* (DEBUG_UART_ENABLED == ENABLED) */
//            }
        }
        else /* When BLE subsystem has been put into Sleep mode or is active */
        {
            /* And hardware doesn't finish Tx/Rx opeation - put the CPU into Sleep mode */
            if(CyBle_GetBleSsState() != CYBLE_BLESS_STATE_EVENT_CLOSE)
            {
                CySysPmSleep();
            }
        }
        /* Enable global interrupt */
        CyExitCriticalSection(interruptStatus);
    }
}
void ShowValue(CYBLE_GATT_VALUE_T *value)
{
    int16 i;
    
    for(i = 0; i < value->len; i++)
    {
        DBG_PRINTF("%2.2x ", value->val[i]);
    }
    DBG_PRINTF("\r\n");
}

//Breaking up a uint32 signal to 4 uint8 parts 
void Set32ByPtr(uint8 ptr[], uint32 value)
{
    ptr[0u] = (uint8) value;
    ptr[1u] = (uint8) (value >> 8u);    
    ptr[2u] = (uint8) (value >> 16u);    
    ptr[3u] = (uint8) (value >> 24u);
}

int _write(int file, char *ptr, int len)
{
    int i;
    file = file;
    for (i = 0; i < len; i++)
    {
        UART_DEB_UartPutChar(*ptr++);
    }
    return len;
}
