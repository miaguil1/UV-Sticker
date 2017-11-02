#include "uv.h"
#include "system.h"

float uv_measure(uint8 diode_num)
{
    uint32 pd_channel = diode_num + 3;

    float adc_counts_float = (float) adc_acquire_channel(pd_channel);
    float milli_volts = (adc_counts_float*vdd_calibration)/2048; 
    return milli_volts;
}

float uv_get_pd(uint8 diode_num)
{
    float uv_mv = uv_measure(diode_num); //Measure Raw ADC value from Port
//    float v_out = uv_mv - amp_iov[diode_num-1] - amp_ibc[diode_num-1]*uv_gain[diode_num-1]; //Get PhotoDiode Voltage, subtract Amplifier Noise
//    float uv_current = v_out/uv_gain[diode_num-1]; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_current = uv_mv/uv_gain[diode_num-1]; //Getting PhotoDiode Current from PhotoDiode Voltage
    float uv_pd = uv_current/uv_respons[diode_num-1]; //Getting Power Density from PhotoDiode
    return uv_pd; //Returning UV Photodiode Power Density in mW/cm^2
}

void uv_get_pd_string(char *uv_pd_string, uint8 diode_num)
{
    float uv_pd = uv_get_pd(diode_num); //Returns the Power Density of that PhotoDiode
    sprintf(uv_pd_string, "%.4f", uv_pd); //Places the Float Value of Power Density in String
}

void uv_uart(uint8 diode_num)
{
    char uv_pd_string[5]; //Initializes the Character Array
    uv_get_pd_string(uv_pd_string, diode_num); //Places the power density of diode in Character Vector
    send_string(uv_pd_string);
}
