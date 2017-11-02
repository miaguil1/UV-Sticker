#include "sg.h"
#include "system.h"

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
    float sg_strain = sg_current/sg_resistors[3]; //Getting Power Density from PhotoDiode
    return sg_strain; //Returning Strain Guage Percent Change(%)
}

unsigned int sg_get_strain_string(char *sg_strain_string)
{
    float sg_strain = sg_get_strain(); //Returns the Strain Guage Percent Change
    sprintf(sg_strain_string, "%.3f", sg_strain); //Places the Float Value of Strain Guage in String
    sg_strain_string[5] = '\n'; //Places a new line character in the last spot in the array
    
    unsigned int sg_l = strlen(sg_strain_string); //Gets the length of the Character Vector
    return sg_l; //Returns the Length of the Character Vector
    
}

void sg_uart()
{
    char sg_strain_string[6]; //Initializes the Character Array
    unsigned int sg_l = sg_get_strain_string(sg_strain_string); //Places the strain guage percent change in Character Vector
    //Sends the Value over UART
    for(unsigned int i = 0; i<sg_l; i++)
    {
        UART_UartPutChar(sg_strain_string[i]);           
    }
}

