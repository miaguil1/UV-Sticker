#include "sg.h"

float sg_measure()
{
    uint32 sg_channel = 0;

    float adc_counts_float = (float) adc_acquire_channel(sg_channel);
    float milli_volts = (adc_counts_float*vdd_calibration)/2048; 
    return milli_volts;
}

float sg_get_strain()
{
    float sg_mv = sg_measure(); //Measure Raw ADC value from Strain Guage Port
    float v_out = sg_mv - amp_iov[1] - amp_ibc[1]*sg_resistors[1]; //Get PhotoDiode Voltage, subtract Amplifier Noise
    float gain = (1 + 2 * sg_resistors[6] / sg_resistors[8]); //Calculating Gain from Strain Guage Differential Amplifier
    float sg_current = v_out/sg_resistors[2]; //Getting PhotoDiode Current from PhotoDiode Voltage
    float sg_strain = sg_current/sg_resistors[3]/gain; //Getting Power Density from PhotoDiode
    return sg_strain; //Returning Strain Guage Percent Change(%)
}

void sg_get_strain_string(char *sg_strain_string)
{
    float sg_strain = sg_get_strain(); //Returns the Strain Guage Percent Change
    sprintf(sg_strain_string, "%.4f", sg_strain); //Places the Float Value of Strain Guage in String   
}

void sg_uart()
{
    char sg_strain_string[5]; //Initializes the Character Array
    sg_get_strain_string(sg_strain_string); //Places the strain guage percent change in Character Vector

    char sg_uart_string[7]; //Stores UV Photodiode Power Density in Message
    sg_uart_string[0] = 's'; //Places an s as the first element in the arrray
    sg_uart_string[6] = '\n'; //Places a new line character in the last spot in the array
    
    //Placing Value in Packet between new message carrier and last message carrier
    for(unsigned int j = 1; j<strlen(sg_strain_string); j++)
    {
        sg_uart_string[j] = sg_strain_string[j-1];    
    }
    
    //Sends the Value over UART
    for(unsigned int i = 0; i<strlen(sg_strain_string); i++)
    {
//        UART_UartPutChar(sg_uart_string[i]);           
    } 
}

//Reads the state of the LED and writes that value into the GATT Database
void update_sg()
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle; //Temporary BLE Handle
    
    //If not connected, no need to update GATT Database/Server
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    {
        return; //Leaves the function updateCapsense()
    }
    uint16 strain_guage = (uint16) sg_get_strain();
    tempHandle.attrHandle = CYBLE_BATTERY_BATTERY_LEVEL_CHAR_HANDLE;
    //Cast it into a 8 bit integer pointer
    tempHandle.value.val = (uint8 *)&strain_guage; //Storing the Strain Guage Value
    tempHandle.value.len = 2; //Uint16 value is stored as 2 8 bit integer
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0); //Writing new value to Gatt Server    
    CyBle_GattsNotification(cyBle_connHandle, &tempHandle); //Sends out Notification to Gatt Central
}