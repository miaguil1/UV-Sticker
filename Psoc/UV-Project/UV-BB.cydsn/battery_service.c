/*
File Name: bas.c
Battery Management Service
Measures the Percent of the Battery Life
Functions:
-BasCallBack()
    Summary:
       This is an event callback function to receive service specific events from 
       Battery Service.
    Parameters:
      event - the event code
      *eventParam - the event parameters
    Return:
      None
-MeasureBattery()
    Summary:
        This function measures the battery voltage and sends it to the client.
    Parameters:
        None
    Return:
        None
*/
#include "common.h"
#include "bas.h"

uint16 batterySimulationNotify = 0u;
uint16 batteryMeasureNotify = 0u;


void BasCallBack(uint32 event, void *eventParam)
{
    uint8 locServiceIndex = ((CYBLE_BAS_CHAR_VALUE_T *)eventParam)->serviceIndex;
    
    switch(event)
    {
        case CYBLE_EVT_BASS_NOTIFICATION_ENABLED:
            if(BAS_SERVICE_MEASURE == locServiceIndex)
            {
                batteryMeasureNotify = ENABLED;
            }
            break;
                
        case CYBLE_EVT_BASS_NOTIFICATION_DISABLED:
//            UART("CYBLE_EVT_BASS_NOTIFICATION_DISABLED: %x \r\n", locServiceIndex);
            if(BAS_SERVICE_MEASURE == locServiceIndex)
            {
                batteryMeasureNotify = DISABLED;
            }
            break;
        case CYBLE_EVT_BASC_NOTIFICATION:
            break;
        case CYBLE_EVT_BASC_READ_CHAR_RESPONSE:
            break;
        case CYBLE_EVT_BASC_READ_DESCR_RESPONSE:
            break;
        case CYBLE_EVT_BASC_WRITE_DESCR_RESPONSE:
            break;
		default:
//            DBG_PRINTF("Not supported event\r\n");
			break;
    }
}

void MeasureBattery(void)
{
    CYBLE_API_RESULT_T apiResult;
    
     /* Set the ADC Voltage Reference to 1.024V and Enable Reference Bypass */
	uint32 sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
	ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_INTERNAL1024BYPASSED;
    
    /* 5 ms delay for reference capacitor to charge */
	CyDelay(5u);
    
    /* Start the ADC conversion at this voltage reference and Record Value */
	ADC_StartConvert();
	ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    uint16 Battery_ADC = ADC_GetResult16(ADC_BATTERY_CHANNEL);
    
    /* Set the reference to VDD and disable reference bypass */
	sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
	ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_VDDA;
    
    /* Convert Battery Value ADC to Millivolts */
	float battery_mv = (float)(Battery_ADC * 1024) / 2048;
    
    /* Convert battery level voltage to percentage using linear approximation
    *  divided to two sections according to typical performance of 
    *  CR2033 battery specification:
    *  3V - 100%
    *  2.8V - 29%
    *  2.0V - 0%
    */
    uint8 batteryLevel = (uint8) ((battery_mv - BATTERY_MIN) / (BATTERY_MAX - BATTERY_MIN) * 100);
    
    // If the Battery Voltage Level is below 10%, the Low Power LED turns on
    if(batteryLevel < (10u))
    {
        LowPower_LED_Write(LED_ON);
    }
    else
    {
        LowPower_LED_Write(LED_OFF);
    }

    /* Update Battery Level characteristic value and send Notification */
    apiResult = CyBle_BassSendNotification(cyBle_connHandle, BAS_SERVICE_MEASURE, CYBLE_BAS_BATTERY_LEVEL, sizeof(batteryLevel), &batteryLevel);
    
    //Omit variable "cyBle_connHandle" to just update Characteristic Value
    // Update Battery Level characteristic value and Don't Send Notification
    //apiResult = CyBle_BassSendNotification(BAS_SERVICE_MEASURE, CYBLE_BAS_BATTERY_LEVEL, sizeof(batteryLevel), &batteryLevel);
//        if(apiResult != CYBLE_ERROR_OK)
//        {
//            UART_PutChar("API Error: %x \r\n", apiResult);
//            batteryMeasureNotify = DISABLED;
//        }
//        else // Update Battery Level Via UART
//        {
//            UART_PutChar('s');
//            UART_SEND_NUM(batteryLevel);
//            UART_Send_Char('\n');
//            DBG_PRINTF("MeasureBatteryLevelUpdate: %d \r\n",batteryLevel);
//        } Send Debugging Info over UART
}
