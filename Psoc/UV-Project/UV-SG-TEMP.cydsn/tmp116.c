#include "tmp116.h"

float tmp116_get_celsius(void)
{
    float reg_cels_conv = 7812.5; //1 Register unit = 0.0078125 Celcius
    float celsius_counts = (float) tmp116_get_uint16();
    float tmp116_celsius = reg_cels_conv*celsius_counts/1000000;
    return tmp116_celsius;
}

uint16 tmp116_get_uint16(void)
{
    uint32 tmp116_gnd_address = 0x48; //Slave Address for TMP116, ADD0 = GND
    uint32 tmp116_temp_address = 0x00;  //Temperature values stored in this Address of TMP116
    uint8 i2c_temp_counts[2];
    uint32 temp_register_byte_count = 2; //Number of bytes of buffer to read

    system_read_i2c(tmp116_gnd_address, tmp116_temp_address, i2c_temp_counts, temp_register_byte_count);
    
    uint16 uint16_i2c_counts =  (i2c_temp_counts[0] << 8) | i2c_temp_counts[1];
    return uint16_i2c_counts;
}

void tmp116_string_celsius(char *tmp116_temperature)
{
    float int_temp = tmp116_get_celsius();
    sprintf(tmp116_temperature, "%.4f", int_temp);  
}

void tmp116_uart(void)
{
    char tmp116_temperature[5]; //Initializes the Character Array
    tmp116_string_celsius(tmp116_temperature); //Places the TMP116 Temperature in Character Vector

    char tmp116_uart_string[7] = {'0','0','0','0','0','0','0'}; //Stores TMP116 Data in Message
    tmp116_uart_string[0] = 't'; //Places an t as the first element in the arrray
    tmp116_uart_string[6] = '\n'; //Places a new line character in the last spot in the array
    
    //Placing Value in Packet between new message carrier and last message carrier
    for(unsigned int j = 1; j<strlen(tmp116_temperature); j++)
    {
        tmp116_uart_string[j] = tmp116_temperature[j-1];    
    }
    
    //Sends the Value over UART
    for(unsigned int i = 0; i<strlen(tmp116_uart_string); i++)
    {
//        UART_UartPutChar(tmp116_uart_string[i]);           
    } 
}

void tmp116_get_uint8(uint8 *tmp116_uint8)
{
    char tmp116_char[5]; //Initializes the Character Array
    tmp116_string_celsius(tmp116_char); 
    for(uint8 i = 0; i<strlen(tmp116_char); i++)
    {
        tmp116_uint8[i] = (uint8) tmp116_char[i];
    }
}

//Reads the state of the LED and writes that value into the GATT Database
void update_tmp116()
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle; //Temporary BLE Handle
    
    //If not connected, no need to update GATT Database/Server
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED || temperature_Notify == 0)
    {
        return; //Leaves the function update_tmp116()
    }

    tmp116_uart(); //Debug Temperature through UART
    uint8 tmp116_uint8[5];
    tmp116_get_uint8(tmp116_uint8); //Places the TMP116 Temperature in Character Vector
    
    tempHandle.attrHandle = CYBLE_BODY_TEMPERATURE_TEMPERATURE_CHAR_HANDLE;
    tempHandle.value.val = tmp116_uint8;
    tempHandle.value.len = 5; //Value is stored as an array of 5 uint8
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0); //Writing new value to Gatt Server    
    CyBle_GattsNotification(cyBle_connHandle, &tempHandle); //Sends out Notification to Gatt Central
}