#include "uv.h"
#include "system.h"

float uv_measure(unsigned int diode_num)
{
    uint32 pd_channel = diode_num + 3;

    float adc_counts_float = (float) adc_acquire_channel(pd_channel);
    float milli_volts = (adc_counts_float*vdd_calibration)/2048; 
    return milli_volts;
}

float uv_get_pd(unsigned int diode_num)
{
    float uv_mv = uv_measure(diode_num); //Measure Raw ADC value from Port
//    float v_out = uv_mv - amp_iov[diode_num-1] - amp_ibc[diode_num-1]*uv_gain[diode_num-1]; //Get PhotoDiode Voltage, subtract Amplifier Noise
//    float uv_current = v_out/uv_gain[diode_num-1]; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_current = uv_mv/uv_gain[diode_num-1]; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_pd = uv_current/uv_respons[diode_num-1]; //Getting Power Density from PhotoDiode
    return uv_pd; //Returning UV Photodiode Power Density in mW/cm^2
}

unsigned int uv_get_pd_string(char *uv_pd_string, unsigned int diode_num)
{
    float uv_pd = uv_get_pd(diode_num); //Returns the Power Density of that PhotoDiode
    sprintf(uv_pd_string, "%.4f", uv_pd); //Places the Float Value of Power Density in String
    unsigned int uv_l = strlen(uv_pd_string); //Gets the length of the Character Vector
    return uv_l; //Returns the Length of the Character Vector
}

void uv_uart(unsigned int diode_num)
{
    char uv_pd_string[5]; //Initializes the Character Array
    unsigned int uv_l = uv_get_pd_string(uv_pd_string, diode_num); //Places the power density of diode in Character Vector

    char uv_uart_string[7]; //
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
