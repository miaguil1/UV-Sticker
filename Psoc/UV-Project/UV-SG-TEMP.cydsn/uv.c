#include "uv.h"

// GUVA || GUVB Photodiodes

float uv_measure(void)
{
    float adc_counts_float = (float) adc_acquire_channel(UV_CHANNEL);
    //float adc_counts_float = (float) adc_acquire_channel(GUVA_CHANNEL);
    float milli_volts = (adc_counts_float*vdd_calibration)/2048; 
    return milli_volts;
}

float uv_get_pd(void)
{
    float uv_mv = uv_measure(); //Measure Raw ADC value from Port
//    float v_out = uv_mv - amp_iov[diode_num-1] - amp_ibc[diode_num-1]*uv_gain[diode_num-1]; //Get PhotoDiode Voltage, subtract Amplifier Noise
//    float uv_current = v_out/uv_gain[diode_num-1]; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_current = uv_mv/uv_gain; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_pd = uv_current/uv_respons; //Getting Power Density from PhotoDiode
    return (uv_pd/1000); //Returning UV Photodiode Power Density in mW/cm^2
}

float uv_get_index(void)
{
    float uv_pd = uv_get_pd();  // Getting UV Power Density
    float index = uv_pd / 26;    //Converting UV Power Density to UV Index
    return index;   //Returning UV index
}

void uv_get_pd_string(char *uv_pd_string)
{
    float uv_pd = uv_get_pd(); //Returns the Power Density of that PhotoDiode
    sprintf(uv_pd_string, "%.4f", uv_pd); //Places the Float Value of Power Density in String
}

void uv_get_uint8(uint8 *uv_uint8)
{
    char uv_pd_string[5]; //Initializes the Character Array
    uv_get_pd_string(uv_pd_string);
    for(uint8 i = 0; i<strlen(uv_pd_string); i++)
    {
        uv_uint8[i] = (uint8) uv_pd_string[i];
    }
}

void uv_uart(void)
{
    char uv_pd_string[5]; //Initializes the Character Array
    uv_get_pd_string(uv_pd_string); //Places the power density of diode in Character Vector

    char uv_uart_string[7]; //Stores UV Photodiode Power Density in Message
    uv_uart_string[0] = 'u'; //Places an s as the first element in the arrray
    uv_uart_string[6] = '\n'; //Places a new line character in the last spot in the array
    
    //Placing Value in Packet between new message carrier and last message carrier
    for(unsigned int j = 1; j<strlen(uv_pd_string); j++)
    {
        uv_uart_string[j] = uv_pd_string[j-1];    
    }
    
    //Sends the Value over UART
    for(unsigned int i = 0; i<strlen(uv_uart_string); i++)
    {
//        UART_UartPutChar(uv_uart_string[i]);           
    } 
}

//Reads the state of the LED and writes that value into the GATT Database
void update_UV()
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle; //Temporary BLE Handle
    
    //If not connected, no need to update GATT Database/Server
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED || uv_Power_Notify == 0)
    {
        return; //Leaves the function update_UV()
    }
    uint8 uv_pd[5] = {0};         //Initializes the Character Array
    uv_get_uint8(uv_pd);    //Getting UV power Density as an uint8 array
    uv_uart();
    
    tempHandle.attrHandle = CYBLE_UV_MEASUREMENT_POWER_DENSITY_CHAR_HANDLE;
    //Cast it into a 8 bit integer pointer
    tempHandle.value.val = uv_pd; 
    tempHandle.value.len = 5; //Uint16 value is stored as 2 8 bit integer
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0); //Writing new value to Gatt Server    
    CyBle_GattsNotification(cyBle_connHandle, &tempHandle); //Sends out Notification to Gatt Central
    
}