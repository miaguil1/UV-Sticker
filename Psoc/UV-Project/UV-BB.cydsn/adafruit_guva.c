#include "adafruit_guva.h"
#include "system.h"

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

unsigned int adafruit_guva_get_pd_string(char *adafruit_guva_pd_string)
{
    float adafruit_guva_pd = adafruit_guva_get_pd(); //Returns the Power Density of that Adafruit GUVA PhotoDiode
    sprintf(adafruit_guva_pd_string, "%.4f", adafruit_guva_pd); //Places the Float Value of Power Density in String
    unsigned int adafruit_guva_l = strlen(adafruit_guva_pd_string); //Gets the length of the Character Vector
    return adafruit_guva_l; //Returns the Length of the Character Vector
}

void adafruit_guva_uart()
{
    char uv_pd_string[5]; //Initializes the Character Array for where the value will be stored
    unsigned int uv_l = adafruit_guva_get_pd_string(uv_pd_string); //Places the power density of diode in Character Vector

    char uv_uart_string[7];
    uv_uart_string[0] = 's'; //Places an s as the first element in the arrray
    uv_uart_string[6] = '\n'; //Places a new line character in the last spot in the array
    unsigned int uv_uart_l = strlen(uv_uart_string);
    
    //Placing Value in Packet between new message carrier and last message carrier
    for(unsigned int j = 1; j<uv_l; j++)
    {
        uv_uart_string[j] = uv_pd_string[j-1];    
    }
    
    //Sends the Value over UART
    for(unsigned int i = 0; i<uv_uart_l; i++)
    {
        UART_UartPutChar(uv_uart_string[i]);           
    } 
}
