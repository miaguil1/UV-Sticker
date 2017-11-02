/*
File Name: temperature_service.c
Temperature Measurement Service
Measures the Temperature of the Source and Communicates the information via Bluetooth
Functions:
-HtsCallBack()
    Summary:
        This is an event callback function to receive service specific events from 
        Health Thermometer Service.
    Parameters:
        event - the event code
        *eventParam - the event parameters
    Return:
        None
    
-BLE_Measure_Temperature()
    Summary:
        This function measures the temperature using either TMP116 or LMT70 and sends it to the client.
    Parameters:
        temp_sensor - Temperature Sensor to use: TMP116=T or LMT70=L
    Return:
        None
*/    
#include "temperature_service.h"
uint16 temperatureMeasure = 0u;
uint32 temperatureTimer = 1u;

uint16 initialMeasurementInterval = 10;
char message[100];
uint8 measure = ENABLED; 

uint8 temp_data[HTS_TEMP_DATA_MIN_SIZE] = {0u, 0u, 0u, 0u, 0u};

void HtsCallBack(uint32 event, void *eventParam)
{
    uint8 locCharIndex = ((CYBLE_HTS_CHAR_VALUE_T *)eventParam)->charIndex;

    switch(event)
    {
        case CYBLE_EVT_HTSS_NOTIFICATION_ENABLED:
            break;
        case CYBLE_EVT_HTSS_NOTIFICATION_DISABLED:
            break;
        case CYBLE_EVT_HTSS_INDICATION_ENABLED:
            //DBG_PRINTF("CYBLE_EVT_HTSS_INDICATION_ENABLED: char: %x\r\n", locCharIndex);
            if(locCharIndex == CYBLE_HTS_TEMP_MEASURE)
            {
                temperatureMeasure = ENABLED;
                measure = ENABLED;
                temp_data[0] = 0u;
            }
            break;
        case CYBLE_EVT_HTSS_INDICATION_DISABLED:
            //DBG_PRINTF("CYBLE_EVT_HTSS_INDICATION_DISABLED: char: %x\r\n", locCharIndex);
            if(locCharIndex == CYBLE_HTS_TEMP_MEASURE)
            {
                temperatureMeasure = DISABLED;
            }
            break;
        case CYBLE_EVT_HTSS_INDICATION_CONFIRMED:
            //DBG_PRINTF("CYBLE_EVT_HTSS_INDICATION_CONFIRMED\r\n");
            break;
        case CYBLE_EVT_HTSS_CHAR_WRITE:
            sprintf(message,"CYBLE_EVT_HTSS_CHAR_WRITE: %x ", locCharIndex);
            send_string(message);
            ShowValue(((CYBLE_HTS_CHAR_VALUE_T *)eventParam)->value);
            if(locCharIndex == CYBLE_HTS_MEASURE_INTERVAL)
            {
                uint16 interval;
                interval = CyBle_Get16ByPtr(((CYBLE_HTS_CHAR_VALUE_T *)eventParam)->value->val);
                
                /* Store new interval value */
                initialMeasurementInterval = interval;
                if(interval != 0u)
                {
                    /* Reset the measurement interval and start the measurement process. */
                    temperatureTimer = 1u;
                    mainTimer++;
                }
            }
            break;
        case CYBLE_EVT_HTSC_NOTIFICATION:
            break;
        case CYBLE_EVT_HTSC_INDICATION:
            break;
        case CYBLE_EVT_HTSC_READ_CHAR_RESPONSE:
            break;
        case CYBLE_EVT_HTSC_WRITE_CHAR_RESPONSE:
            break;
        case CYBLE_EVT_HTSC_READ_DESCR_RESPONSE:
            break;
        case CYBLE_EVT_HTSC_WRITE_DESCR_RESPONSE:
            break;
		default:
            sprintf(message, "Not supported event");
            send_string(message);
			break;
    }
}

void BLE_Measure_Temperature(char temp_sensor)
{
    static int32 temperatureCelsius;
    CYBLE_API_RESULT_T apiResult;
    
    /* Setting the temperature units to Celcius */
    temp_data[0] = CYBLE_HTS_MEAS_FLAG_TEMP_UNITS_BIT;
    
    /* Do not measure temperature when 0 interval is set */
    if((initialMeasurementInterval != 0u) && (--temperatureTimer == 0u)) 
    {
        temperatureTimer = initialMeasurementInterval;
        
        measure = 0u;
        /* Enables injection channel and performs a measurement. */
        if(temp_sensor == 'T')
        {
            temperatureCelsius = lmt70_get_celsius();
        }
        else if(temp_sensor == 'L')
        {
            temperatureCelsius = tmp116_get_celsius();
        }
        else
        {
            temperatureCelsius = 0;
        }
        
        /* Convert int32 to the IEEE-11073 FLOAT-Type.
        *  It is defined as a 32-bit value with a 24-bit mantissa and an 8-bit exponent.
        *  For the integer temperature, 24-bit value has been used with mantissa equal to 0 */
        int32 temperatureValue = 0x00FFFFFF;

        /* Copy temperature to array */
        Set32ByPtr(temp_data + 1u, (uint32)temperatureCelsius);
        
        /* Send temperature to client */
        apiResult = CyBle_HtssSendIndication(cyBle_connHandle, CYBLE_HTS_TEMP_MEASURE, sizeof(temp_data), temp_data);
        
        if(apiResult != CYBLE_ERROR_OK)
        {
            char message[100];
            sprintf(message,"CyBle_HtssSendIndication API Error: %x", apiResult);
            send_string(message);
            temperatureMeasure = DISABLED;
        }
        else
        {
            char message[100];
            sprintf(message,"MeasureTemperature: %d %c  ", (int16)temperatureValue, 'C');
            send_string(message);
        }
        
    }
}
