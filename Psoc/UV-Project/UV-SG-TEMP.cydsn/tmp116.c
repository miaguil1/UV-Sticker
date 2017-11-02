#include "tmp116.h"
#include "system.h"

float tmp116_get_celsius(void)
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
    while(I2C_TMP116_I2CMasterStatus() & I2C_TMP116_I2C_MSTAT_XFER_INP);    
        
       
    /* Clear Read Complete Status bit */
    I2C_TMP116_I2CMasterClearStatus();
    I2C_TMP116_I2CMasterClearReadBuf();
    
    uint16 i2c_counts =  (i2c_reg_counts[0] << 8) | i2c_reg_counts[1];
    float celsius_counts = (float) i2c_counts;
    float tmp116_celsius = reg_cels_conv*celsius_counts/1000000;
    return tmp116_celsius;
}

unsigned int tmp116_string_celsius(char *tmp116_temperature)
{
    float int_temp = tmp116_get_celsius();
    sprintf(tmp116_temperature, "%.3f", int_temp);
    
    tmp116_temperature[5] = '\n';
    
    unsigned int temp_l = strlen(tmp116_temperature);
    return temp_l;
}

void tmp116_uart(void)
{
    char tmp116_temperature[6];
    unsigned int temp_tmp116_l = tmp116_string_celsius(tmp116_temperature);
    for(unsigned int i = 0; i<temp_tmp116_l; i++)
    {
        UART_UartPutChar(tmp116_temperature[i]);           
    }
}