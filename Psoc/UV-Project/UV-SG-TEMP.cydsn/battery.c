#include "battery.h"

uint16 batterySimulationNotify = 0u;
uint16 batteryMeasureNotify = 0u;

/*******************************************************************************
* Function Name: MeasureBattery()
********************************************************************************
*
* Summary:
*   This function measures the battery voltage and sends it to the client.
*
*******************************************************************************/
uint8 measure_battery(void)
{       
	/* Set the reference to 1.024V and enable reference bypass */
	uint32 sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
	ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_INTERNAL1024BYPASSED;
	            
	/* 25 ms delay for reference capacitor to charge */
	/* Perform a measurement. Store this value in Vref. */
	CyDelay(25u);
	ADC_StartConvert();
	ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);

    uint16 adcResult = ADC_GetResult16(BATTERY_CHANNEL);
	/* Calculate input voltage by using ratio of ADC counts from reference
	*  and ADC Full Scale counts. */
            
    /* Set the reference to VDD and disable reference bypass */
	sarControlReg = ADC_SAR_CTRL_REG & ~ADC_VREF_MASK;
	ADC_SAR_CTRL_REG = sarControlReg | ADC_VREF_VDDA;
    
	uint32 mvolts = (1024 * 2048) / adcResult;
    
    /* Convert battery level voltage to percentage using linear approximation
    *  divided to two sections according to typical performance of 
    *  CR2033 battery specification:
    *  3V - 100%
    *  2.8V - 29%
    *  2.0V - 0%
    */
    uint8 batteryLevel;
    if(mvolts < MEASURE_BATTERY_MIN)
    {
        batteryLevel = 0;
    }
    else if(mvolts < MEASURE_BATTERY_MID)
    {
        batteryLevel = (mvolts - MEASURE_BATTERY_MIN) * MEASURE_BATTERY_MID_PERCENT / 
                       (MEASURE_BATTERY_MID - MEASURE_BATTERY_MIN); 
    }
    else if(mvolts < MEASURE_BATTERY_MAX)
    {
        batteryLevel = MEASURE_BATTERY_MID_PERCENT +
                       (mvolts - MEASURE_BATTERY_MID) * (100 - MEASURE_BATTERY_MID_PERCENT) / 
                       (MEASURE_BATTERY_MAX - MEASURE_BATTERY_MID); 
    }
    else
    {
        batteryLevel = 100;
    }
    return batteryLevel;    
}

//Reads the state of the LED and writes that value into the GATT Database
void update_battery()
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle; //Temporary BLE Handle
    
    //If not connected, no need to update GATT Database/Server
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    {
        return; //Leaves the function update_battery()
    }
    uint8 battery_level = measure_battery();
    
    tempHandle.attrHandle = CYBLE_BATTERY_BATTERY_LEVEL_CHAR_HANDLE;
    tempHandle.value.val = (uint8 *)&battery_level; //Casting the pointer as an 8 bit pointer
    tempHandle.value.len = 1; //Uint8 value is stored as 1 8 bit unsigned integer
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0); //Writing new value to Gatt Server    
    CyBle_GattsNotification(cyBle_connHandle, &tempHandle); //Sends out Notification to Gatt Central
}
