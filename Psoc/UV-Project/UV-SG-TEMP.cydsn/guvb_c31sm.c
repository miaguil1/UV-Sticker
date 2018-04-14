#include "guvb_c31sm.h"

const uint32 guvb_c31sm_address = 0x39;   //Slave Device Address of GUVB_C31SM

// GUVB-C31SM Photodiodes
void guvb_c31sm_setup(void)
{
    uint32 register_byte_count = 2; //Slave Address + Register Write Value
    
    uint32 res_uv_register = 0x04;  //GUVB-C31SM Measuring Period & Sensor Resolution of Operation Register
    uint8 res_uv = 0b00000011;     //Setting Resolution to 16 bits and Sensor Measuring Time Period of 100ms, 011
    uint8 res_uv_register_value[2]= {0};
    res_uv_register_value[0] = res_uv_register;
    res_uv_register_value[1] = res_uv;
    uint8 *res_uv_register_value_pointer = res_uv_register_value;
    
    system_write_i2c(guvb_c31sm_address, res_uv_register_value_pointer, register_byte_count);   //sending Message via I2C
    
    uint32 range_uvb_register = 0x07;  //GUVB-C31SM UVB range of operation
    uint8 range_uvb = 0b00000000;     //Setting UVB range of operation to (x8), 011
    uint8 range_uvb_register_value[2]= {0};
    range_uvb_register_value[0] = range_uvb_register;
    range_uvb_register_value[1] = range_uvb;
    uint8 *range_uvb_register_value_pointer = range_uvb_register_value;
    
    system_write_i2c(guvb_c31sm_address, range_uvb_register_value_pointer, register_byte_count);   //sending Message via I2C

    uint32 mode_ctl_register = 0x0A;  //GUVB-C31SM Sleep Duration during low-power mode, based on measuring time of each operating mode
    uint8 mode_ctl = 0b00010000;     //Setting Sleep Duration to 4 times the measuring time, 001
    uint8 mode_ctl_register_value[2]= {0};
    mode_ctl_register_value[0] = mode_ctl_register;
    mode_ctl_register_value[1] = mode_ctl;
    uint8 *mode_ctl_register_value_pointer = mode_ctl_register_value;
    
    system_write_i2c(guvb_c31sm_address, mode_ctl_register_value_pointer, register_byte_count);   //sending Message via I2C
    
}

void soft_reset_guvb_c31sm(void)
{
    uint32 register_byte_count = 2;
    uint32 soft_reset_register = 0xB;  //GUVB-C31SM Soft Reset to Initialize Circuit. Power mode = Normal Mode (00)
    uint8 soft_reset = 0xA5;     //Soft Reset of UV sensor is Set, will autoclear once written to
    uint8 soft_reset_register_value[2]= {0};
    soft_reset_register_value[0] = soft_reset_register;
    soft_reset_register_value[1] = soft_reset;
    uint8 *soft_reset_register_value_pointer = soft_reset_register_value;

    system_write_i2c(guvb_c31sm_address, soft_reset_register_value_pointer, register_byte_count);   //sending Message via I2C
}

void guvb_c31sm_shutdown(void)
{
    uint32 register_byte_count = 2;
    uint32 mode_register = 0x01;  //GUVB-C31SM Mode Register
    uint8 mode = 0b00100011;   //Setting Operations mode to UVB Operation, 10 & Setting Power mode to Shutdown mode, 11  
    uint8 mode_register_value[2]= {0};
    mode_register_value[0] = mode_register;
    mode_register_value[1] = mode;   //Combining Power Management and Sensor Operations for 1 register
    uint8 *mode_register_value_pointer = mode_register_value;     
    
    system_write_i2c(guvb_c31sm_address, mode_register_value_pointer, register_byte_count); //sending Message via I2C 
}

void guvb_c31sm_wakeup(void)
{
    uint32 register_byte_count = 2;
    uint32 mode_register = 0x01;  //GUVB-C31SM Mode Register
    uint8 mode = 0b00100000;   //Setting Operations mode to UVB Operation, 10 & Setting Power mode to Normal mode, 00  
    uint8 mode_register_value[2]= {0};
    mode_register_value[0] = mode_register;
    mode_register_value[1] = mode;
    uint8 *mode_register_value_pointer = mode_register_value;     
    
    system_write_i2c(guvb_c31sm_address, mode_register_value_pointer, register_byte_count); //sending Message via I2C       
}

uint8 guvb_c31sm_chipid(void)
{
    uint32 chipid_register = 0x00;  //ChipID Register    
    uint32 chipid_byte_count = 1;    //Number of bytes to read from ChipID
    uint8 chipid_value[1] = {0};  // Array to store values from register
    uint8 *chipid_value_pointer = chipid_value; //Pointer to array that stores value from targeted register
    
    system_read_i2c(guvb_c31sm_address, chipid_register, chipid_value_pointer, chipid_byte_count);

    return chipid_value[0];
}

void guvb_c31sm_range(void)
{
    uint32 register_byte_count = 1;    //Number of bytes to read from ChipID
    uint32 range_uvb_register = 0x07;  //GUVB-C31SM UVB range of operation
    uint8 range_uvb = 0b00000000;     //Setting UVB range of operation to (x1), 0
    uint8 range_uvb_register_value[2]= {0};
    range_uvb_register_value[0] = range_uvb_register;
    range_uvb_register_value[1] = range_uvb;
    uint8 *range_uvb_register_value_pointer = range_uvb_register_value;
    
    system_write_i2c(guvb_c31sm_address, range_uvb_register_value_pointer, register_byte_count);   //sending Message via I2C            
}

uint8 guvb_c31sm_read_register(uint32 register_address)
{
    uint32 read_register_address = register_address;  //ChipID Register    
    uint32 register_byte_count = 1;    //Number of bytes to read from ChipID
    uint8 register_value[1] = {0};  // Array to store values from register
    uint8 *register_value_pointer = register_value; //Pointer to array that stores value from targeted register
    
    system_read_i2c(guvb_c31sm_address, read_register_address, register_value_pointer, register_byte_count);

    return register_value[0];
}

uint16 guvb_c31sm_get_uint16(void)
{
    uint32 guvb_c31sm_lsb_register = 0x17;  //UVB_LSB Register 
    uint32 guvb_c31sm_msb_register = 0x18;  //UVB_MSB Register 
    uint32 i2c_byte_count = 1; //Number of bytes of buffer to read per register
    uint8 guvb_c31sm_lsb_value[1]={0};  //UVB_LSB Value Array to store buffer in register
    uint8 guvb_c31sm_msb_value[1]={0};  //UVB_MSB Value Array to store buffer in register
    uint8 *guvb_c31sm_lsb_value_pointer = guvb_c31sm_lsb_value; //UVB_LSB Pointer to Value Array
    uint8 *guvb_c31sm_msb_value_pointer = guvb_c31sm_msb_value; //UVB_MSB Pointer to Value Array
    
    system_read_i2c(guvb_c31sm_address, guvb_c31sm_lsb_register, guvb_c31sm_lsb_value_pointer, i2c_byte_count); // Read LSB
    system_read_i2c(guvb_c31sm_address, guvb_c31sm_msb_register, guvb_c31sm_msb_value_pointer, i2c_byte_count); // Read MSB
    
    uint16 i2c_counts =  (guvb_c31sm_msb_value[0] << 8) | guvb_c31sm_lsb_value[0]; // Combine LSB and MSB into 1 uint16 value
    return i2c_counts;
}

uint16 guvb_c31sm_nvm(void)
{
    uint32 register_byte_count = 1;    //Number of bytes to read from register
    uint32 nvm_register = 0x30;  //GUVB-C31SM NVM Read Control
    uint8 nvm_value = 0x0C;     //Setting NVM Read Control to B_Scale 
    uint8 nvm_register_value[2]= {0};
    nvm_register_value[0] = nvm_register;
    nvm_register_value[1] = nvm_value;
    uint8 *nvm_register_value_pointer = nvm_register_value;
    
    system_write_i2c(guvb_c31sm_address, nvm_register_value_pointer, register_byte_count);   //sending Message via I2C 
    
    uint32 guvb_c31sm_lsb_nvm_register = 0x32;  //UVB_LSB B_Scale Register 
    uint32 guvb_c31sm_msb_nvm_register = 0x31;  //UVB_MSB B_Scale Register 
    uint32 i2c_byte_count = 1; //Number of bytes of buffer to read per register
    uint8 guvb_c31sm_lsb_nvm_value[1]={0};  //UVB_LSB B_Scale Value Array to store buffer in register
    uint8 guvb_c31sm_msb_nvm_value[1]={0};  //UVB_MSB B_Scale Value Array to store buffer in register
    uint8 *guvb_c31sm_lsb_nvm_value_pointer = guvb_c31sm_lsb_nvm_value; //UVB_LSB Pointer to Value Array
    uint8 *guvb_c31sm_msb_nvm_value_pointer = guvb_c31sm_msb_nvm_value; //UVB_MSB Pointer to Value Array
    
    system_read_i2c(guvb_c31sm_address, guvb_c31sm_lsb_nvm_register, guvb_c31sm_lsb_nvm_value_pointer, i2c_byte_count); // Read LSB
    system_read_i2c(guvb_c31sm_address, guvb_c31sm_msb_nvm_register, guvb_c31sm_msb_nvm_value_pointer, i2c_byte_count); // Read MSB
    
    uint16 b_scale =  (guvb_c31sm_msb_nvm_value[0] << 8) | guvb_c31sm_lsb_nvm_value[0]; // Combine LSB and MSB into 1 uint16 value
    return b_scale;
}

uint16 guvb_c31sm_read_sensor(void)
{
    guvb_c31sm_wakeup();
    guvb_c31sm_range();
    uint16 b_scale = guvb_c31sm_nvm();
    uint16 sensor_value = guvb_c31sm_get_uint16();
    guvb_c31sm_shutdown();
    return sensor_value;    
}

float guvb_c31sm_get_uv(void)
{
    float i2c_uv_pd_conv = 0.8/128;
    float i2c_float_counts = (float) guvb_c31sm_get_uint16();
    float uv_counts = i2c_float_counts*i2c_uv_pd_conv;
    return uv_counts;
}


float guvb_c31sm_get_pd(void)
{
    float uv_units = guvb_c31sm_get_uv(); //Measure Raw ADC value from Port
//    float uv_current = uv_mv/uv_gain; //Getting PhotoDiode Current from PhotoDiode Voltage
//    float uv_pd = uv_current/uv_respons; //Getting Power Density from PhotoDiode
    return uv_units; //Returning UV Photodiode Power Density in mW/cm^2
}

float guvb_c31sm_get_index(void)
{
    float uv_pd = guvb_c31sm_get_pd();  // Getting UV Power Density
    float index = uv_pd / 26;    //Converting UV Power Density to UV Index
    return index;   //Returning UV index
}

void guvb_c31sm_get_pd_string(char *uv_pd_string)
{
    float uv_pd = guvb_c31sm_get_pd(); //Returns the Power Density of that PhotoDiode
    sprintf(uv_pd_string, "%.4f", uv_pd); //Places the Float Value of Power Density in String
}

void guvb_c31sm_get_uint8(uint8 *uv_uint8)
{
    char uv_pd_string[5]; //Initializes the Character Array
    guvb_c31sm_get_pd_string(uv_pd_string);
    for(uint8 i = 0; i<strlen(uv_pd_string); i++)
    {
        uv_uint8[i] = (uint8) uv_pd_string[i];
    }
}

void guvb_c31sm_uart(void)
{
    char uv_pd_string[5]; //Initializes the Character Array
    guvb_c31sm_get_pd_string(uv_pd_string); //Places the power density of diode in Character Vector

    char uv_uart_string[7] = {'0','0','0','0','0','0','0'};; //Stores UV Photodiode Power Density in Message
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
    guvb_c31sm_get_uint8(uv_pd);    //Getting UV power Density as an uint8 array
    guvb_c31sm_uart();
    
    tempHandle.attrHandle = CYBLE_UV_MEASUREMENT_POWER_DENSITY_CHAR_HANDLE;
    //Cast it into a 8 bit integer pointer
    tempHandle.value.val = uv_pd; 
    tempHandle.value.len = 5; //Uint16 value is stored as 2 8 bit integer
    CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0); //Writing new value to Gatt Server    
    CyBle_GattsNotification(cyBle_connHandle, &tempHandle); //Sends out Notification to Gatt Central
    
}