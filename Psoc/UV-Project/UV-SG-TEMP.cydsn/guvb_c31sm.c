#include "guvb_c31sm.h"

// GUVB-C31SM Photodiodes
void setup_guvb_c31sm(void)
{
    uint32 register_byte_count = 1;
    uint32 mode_register = 0x01;  //GUVB-C31SM Mode Register
    uint8 pmode = 0b00000000;     //Setting Power mode to Normal mode, 00
    uint8 oper = 0b00100000;      //Setting Operations mode to UVB Operation, 10
    uint8 mode_register_value[1]= {};
    mode_register_value[0] = pmode & oper;   //Combining Power Management and Sensor Operations for 1 register
    system_write_i2c(mode_register, mode_register_value, register_byte_count);   //sending Message via I2C
    
    uint32 res_uv_register = 0x04;  //GUVB-C31SM Measuring Period & Sensor Resolution of Operation Register
    uint8 res_uv = 0b00000011;     //Setting Resolution to 16 bits and Sensor Measuring Time Period of 100ms, 011
    uint8 res_uv_register_value[1]= {};
    res_uv_register_value[0] = res_uv;
    system_write_i2c(res_uv_register, res_uv_register_value, register_byte_count);   //sending Message via I2C
    
    uint32 range_uvb_register = 0x07;  //GUVB-C31SM UVB range of operation
    uint8 range_uvb = 0b00000011;     //Setting UVB range of operation to (x8), 011
    uint8 range_uvb_register_value[1]= {};
    range_uvb_register_value[0] = range_uvb;
    system_write_i2c(range_uvb_register, range_uvb_register_value, register_byte_count);   //sending Message via I2C

    uint32 mode_ctl_register = 0x07;  //GUVB-C31SM Sleep Duration during low-power mode, based on measuring time of each operating mode
    uint8 mode_ctl = 0b00000001;     //Setting Sleep Duration to 4 times the measuring time, 001
    uint8 mode_ctl_register_value[1]= {};
    mode_ctl_register_value[0] = mode_ctl;
    system_write_i2c(mode_ctl_register, mode_ctl_register_value, register_byte_count);   //sending Message via I2C
    
    uint32 soft_reset_register = 0xB;  //GUVB-C31SM Soft Reset to Initialize Circuit. Power mode = Normal Mode (00)
    uint8 soft_reset = 0xA5;     //Soft Reset of UV sensor is Set, will autoclear once written to
    uint8 soft_reset_register_value[1]= {};
    soft_reset_register_value[0] = soft_reset;
    system_write_i2c(soft_reset_register, soft_reset_register_value, register_byte_count);   //sending Message via I2C
}

void shutdown_guvb_c31sm(void)
{
    uint32 register_byte_count = 1;
    uint32 mode_register = 0x01;  //GUVB-C31SM Mode Register
    uint8 pmode = 0b00000000;     //Setting Power mode to Normal mode, 00
    uint8 oper = 0b00100000;      //Setting Operations mode to UVB Operation, 10
    uint8 mode_register_value[1]= {};
    mode_register_value[0] = pmode & oper;   //Combining Power Management and Sensor Operations for 1 register
    system_write_i2c(mode_register, mode_register_value, register_byte_count);   //sending Message via I2C        
    
}

uint8 guvb_c31sm_chipid(void)
{
    uint32 chipid_register = 0x00;  //ChipID Register    
    uint32 chipid_byte_count = 1;    //Number of bytes to read from ChipID
    uint32 i2c_mode = I2C_I2C_MODE_COMPLETE_XFER; //Transfer Mode Possibilities
    uint32 i2c_error;
    uint8 chipid_value[1];  // Array to store values from register
    
    system_read_i2c(chipid_register, chipid_value, chipid_byte_count);    
    uint8 chipid = chipid_value[0];
    return chipid;
}

float guvb_c31sm_get_uv(void)
{
    float reg_cels_conv = 7812.5; //1 Register unit = 0.0078125 Celcius
    uint32 tmp116_gnd_add = 0x48; //Slave Address for TMP116, ADD0 = GND
    uint8 i2c_reg_counts[2];
    uint32 i2c_byte_count = 2; //Number of bytes of buffer to read
    uint32 i2c_mode = I2C_TMP116_I2C_MODE_COMPLETE_XFER; //Transfer Mode Possibilities
    uint32 i2c_error;

    do
    {
        i2c_error = I2C_TMP116_I2CMasterReadBuf(tmp116_gnd_add, i2c_reg_counts, i2c_byte_count, i2c_mode);
    }
    while(i2c_error != I2C_TMP116_I2C_MSTR_NO_ERROR);
   
    /* Wait for the data transfer to complete */   
    while(!(I2C_TMP116_I2CMasterStatus() & I2C_TMP116_I2C_MSTAT_RD_CMPLT)); //Wait until the Master has completed reading    
    /* Clear Read Complete Status bit */
    I2C_TMP116_I2CMasterClearStatus();
    I2C_TMP116_I2CMasterClearReadBuf();
 
    uint16 i2c_counts =  (i2c_reg_counts[0] << 8) | i2c_reg_counts[1];
    float celsius_counts = (float) i2c_counts;
    float tmp116_celsius = reg_cels_conv*celsius_counts/1000000;
    return tmp116_celsius;
}

float uv_get_pd(void)
{
    float uv_mv = uv_measure(); //Measure Raw ADC value from Port
//    float v_out = uv_mv - amp_iov[diode_num-1] - amp_ibc[diode_num-1]*uv_gain[diode_num-1]; //Get PhotoDiode Voltage, subtract Amplifier Noise
//    float uv_current = v_out/uv_gain[diode_num-1]; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_current = uv_mv/uv_gain; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_pd = uv_current/uv_respons; //Getting Power Density from PhotoDiode
    return (uv_mv/1000); //Returning UV Photodiode Power Density in mW/cm^2
}

float guvb_c31sm_get_index(void)
{
    float uv_pd = uv_get_pd();  // Getting UV Power Density
    float index = uv_pd / 26;    //Converting UV Power Density to UV Index
    return index;   //Returning UV index
}

void guvb_c31sm_get_pd_string(char *uv_pd_string)
{
    float uv_pd = uv_get_pd(); //Returns the Power Density of that PhotoDiode
    sprintf(uv_pd_string, "%.4f", uv_pd); //Places the Float Value of Power Density in String
}

void guvb_c31sm_get_uint8(uint8 *uv_uint8)
{
    char uv_pd_string[5]; //Initializes the Character Array
    uv_get_pd_string(uv_pd_string);
    for(uint8 i = 0; i<strlen(uv_pd_string); i++)
    {
        uv_uint8[i] = (uint8) uv_pd_string[i];
    }
}

void guvb_c31sm_uart(void)
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
        UART_UartPutChar(uv_uart_string[i]);           
    } 
}

//Reads the state of the LED and writes that value into the GATT Database
void guvb_c31sm_update_UV()
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