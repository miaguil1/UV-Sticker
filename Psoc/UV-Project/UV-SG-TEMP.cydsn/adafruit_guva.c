#include "adafruit_guva.h"

float adafruit_guva_measure()
{
    uint32 pd_channel = 1;

    float adc_counts_float = (float) adc_acquire_channel(pd_channel);
    float milli_volts = (adc_counts_float*vdd_calibration)/2048; 
    return milli_volts;
}

float adafruit_guva_get_pd()
{
    float adafruit_guva_mv = adafruit_guva_measure(); //Measure Raw ADC value from Port
    float adafruit_guva_current = adafruit_guva_mv/4.30; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_pd = adafruit_guva_current/113; //Getting Power Density from PhotoDiode
    return uv_pd; //Returning UV Photodiode Power Density in mW/cm^2
}

void adafruit_guva_get_pd_string(char *adafruit_guva_pd_string)
{
    float adafruit_guva_pd = adafruit_guva_get_pd(); //Returns the Power Density of that Adafruit GUVA PhotoDiode
    sprintf(adafruit_guva_pd_string, "%.4f", adafruit_guva_pd); //Places the Float Value of Power Density in String
}

void adafruit_guva_uart()
{
    char a_guva_pd_string[5]; //Initializes the Character Array for where the value will be stored
    adafruit_guva_get_pd_string(a_guva_pd_string); //Places the power density of diode in Character Vector

    char a_guva_uart_string[7];
    a_guva_uart_string[0] = 'a'; //Places an a as the first element in the arrray
    a_guva_uart_string[6] = '\n'; //Places a new line character in the last spot in the array
    
    //Placing Value in Packet between new message carrier and last message carrier
    for(unsigned int j = 1; j<strlen(a_guva_pd_string); j++)
    {
        a_guva_uart_string[j] = a_guva_pd_string[j-1];    
    }
    
    //Sends the Value over UART
    for(unsigned int i = 0; i<strlen(a_guva_uart_string); i++)
    {
        UART_UartPutChar(a_guva_uart_string[i]);           
    } 
}

//Reads the state of the LED and writes that value into the GATT Database
void updateCapsense()
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle; //Temporary BLE Handle
    
    //If not connected, no need to update GATT Database/Server
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    {
        return; //Leaves the function updateCapsense()
    }
    uint16 fingerPos = 5;
    tempHandle.attrHandle = CYBLE_UV_MEASUREMENT_POWER_DENSITY_CHAR_HANDLE;
    //Cast it into a 8 bit integer pointer
    tempHandle.value.val = (uint8 *)&fingerPos; //Storing the finger's Position
    tempHandle.value.len = 2; //uint16 value is stored as 2 8 bit integer
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0); //Writing new value to Gatt Server    
    CyBle_GattsNotification(cyBle_connHandle, &tempHandle); //Sends out Notification to Gatt Central
}
