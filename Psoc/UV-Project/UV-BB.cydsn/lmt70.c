#include "lmt70.h"
#include "system.h"

#define VOLTAGE_MINUS_55   (1375)
#define VOLTAGE_MINUS_50   (1350)
#define VOLTAGE_MINUS_40   (1301)
#define VOLTAGE_MINUS_30   (1250)
#define VOLTAGE_MINUS_20   (1200)
#define VOLTAGE_MINUS_10   (1149)
#define VOLTAGE_0          (1098)
#define VOLTAGE_10         (1047)
#define VOLTAGE_20         (995)
#define VOLTAGE_30         (943)
#define VOLTAGE_40         (891)
#define VOLTAGE_50         (839)
#define VOLTAGE_60         (786)
#define VOLTAGE_70         (734)
#define VOLTAGE_80         (681)
#define VOLTAGE_90         (627)
#define VOLTAGE_100        (574)
#define VOLTAGE_110        (521)
#define VOLTAGE_120        (467)
#define VOLTAGE_130        (413)
#define VOLTAGE_140        (358)
#define VOLTAGE_150        (303)


int int_slopes[21] = { 
	-201792,
	-200610,
	-199223,
	-197965,
	-196796,
	-195760,
	-194780,
	-193810,
	-192965,
	-192127,
	-191219,
	-190396,
	-189566,
	-188843,
	-188097,
	-187361,
	-186686,
	-185905,
	-185113,
	-183234,
	-180574,
};
int int_intercepts[21] = { 
	222508064,
	220911776,
	219108080,
	217534944,
	216132576,
	214941760,
	213865792,
	212850352,
	212009344,
	211219040,
	210410352,
	209720128,
	209067344,
	208536848,
	208029120,
	207566944,
	207179360,
	206772880,
	206403440,
	205627856,
	204675072,
};

float lmt70_get_celsius(void)
{
    uint32 lmt70_channel = 3;
    float adc_counts = (float) adc_acquire_channel(lmt70_channel);
    float milli_volts = (adc_counts*vdd_calibration)/2048; 
    
    int case_number = -1; // Initializing case_number to a non-choosable case_number
	float celsius = -777; // Initializing celsius to a number
    
    if (milli_volts > VOLTAGE_MINUS_55)                                                 { case_number = 0; }
    else if ((milli_volts <= VOLTAGE_MINUS_55)  && (milli_volts > VOLTAGE_MINUS_50))    { case_number = 1; }
    else if ((milli_volts <= VOLTAGE_MINUS_50)  && (milli_volts > VOLTAGE_MINUS_40))    { case_number = 2; }
    else if ((milli_volts <= VOLTAGE_MINUS_40)  && (milli_volts > VOLTAGE_MINUS_30))    { case_number = 3; }
    else if ((milli_volts <= VOLTAGE_MINUS_30)  && (milli_volts > VOLTAGE_MINUS_20))    { case_number = 4; }
    else if ((milli_volts <= VOLTAGE_MINUS_20)  && (milli_volts > VOLTAGE_MINUS_10))    { case_number = 5; }
    else if ((milli_volts <= VOLTAGE_MINUS_10)  && (milli_volts > VOLTAGE_0))           { case_number = 6; }
    else if ((milli_volts <= VOLTAGE_0)         && (milli_volts > VOLTAGE_10))          { case_number = 7; }
    else if ((milli_volts <= VOLTAGE_10)        && (milli_volts > VOLTAGE_20))          { case_number = 8; }
    else if ((milli_volts <= VOLTAGE_20)        && (milli_volts > VOLTAGE_30))          { case_number = 9; }
    else if ((milli_volts <= VOLTAGE_30)        && (milli_volts > VOLTAGE_40))          { case_number = 10; }
    else if ((milli_volts <= VOLTAGE_40)        && (milli_volts > VOLTAGE_50))          { case_number = 11; }
    else if ((milli_volts <= VOLTAGE_50)        && (milli_volts > VOLTAGE_60))          { case_number = 12; }
    else if ((milli_volts <= VOLTAGE_60)        && (milli_volts > VOLTAGE_70))          { case_number = 13; }
    else if ((milli_volts <= VOLTAGE_70)        && (milli_volts > VOLTAGE_80))          { case_number = 14; }
    else if ((milli_volts <= VOLTAGE_80)        && (milli_volts > VOLTAGE_90))          { case_number = 15; }
    else if ((milli_volts <= VOLTAGE_90)        && (milli_volts > VOLTAGE_100))         { case_number = 16; }
    else if ((milli_volts <= VOLTAGE_100)       && (milli_volts > VOLTAGE_110))         { case_number = 17; }
    else if ((milli_volts <= VOLTAGE_110)       && (milli_volts > VOLTAGE_120))         { case_number = 18; }
    else if ((milli_volts <= VOLTAGE_120)       && (milli_volts > VOLTAGE_130))         { case_number = 19; }
    else if ((milli_volts <= VOLTAGE_130)       && (milli_volts > VOLTAGE_140))         { case_number = 20; }
    else if ((milli_volts <= VOLTAGE_140)       && (milli_volts > VOLTAGE_150))         { case_number = 21; }
    else if (milli_volts <= VOLTAGE_150)                                                { case_number = 22; }
    else                                                                                { case_number = 23; }
    
    switch(case_number)
    {
        case 0:  celsius = (int_slopes[0] *milli_volts+int_intercepts[0]) /1000000; break;
        case 1:  celsius = (int_slopes[0] *milli_volts+int_intercepts[0]) /1000000; break;
        case 2:  celsius = (int_slopes[1] *milli_volts+int_intercepts[1]) /1000000; break;
        case 3:  celsius = (int_slopes[2] *milli_volts+int_intercepts[2]) /1000000; break;
        case 4:  celsius = (int_slopes[3] *milli_volts+int_intercepts[3]) /1000000; break;
        case 5:  celsius = (int_slopes[4] *milli_volts+int_intercepts[4]) /1000000; break;
        case 6:  celsius = (int_slopes[5] *milli_volts+int_intercepts[5]) /1000000; break;
        case 7:  celsius = (int_slopes[6] *milli_volts+int_intercepts[6]) /1000000; break;
        case 8:  celsius = (int_slopes[7] *milli_volts+int_intercepts[7]) /1000000; break;
        case 9:  celsius = (int_slopes[8] *milli_volts+int_intercepts[8]) /1000000; break;
        case 10: celsius = (int_slopes[9] *milli_volts+int_intercepts[9]) /1000000; break;
        case 11: celsius = (int_slopes[10]*milli_volts+int_intercepts[10])/1000000; break;
        case 12: celsius = (int_slopes[11]*milli_volts+int_intercepts[11])/1000000; break;
        case 13: celsius = (int_slopes[12]*milli_volts+int_intercepts[12])/1000000; break;
        case 14: celsius = (int_slopes[13]*milli_volts+int_intercepts[13])/1000000; break;
        case 15: celsius = (int_slopes[14]*milli_volts+int_intercepts[14])/1000000; break;
        case 16: celsius = (int_slopes[15]*milli_volts+int_intercepts[15])/1000000; break;
        case 17: celsius = (int_slopes[16]*milli_volts+int_intercepts[16])/1000000; break;
        case 18: celsius = (int_slopes[17]*milli_volts+int_intercepts[17])/1000000; break;
        case 19: celsius = (int_slopes[18]*milli_volts+int_intercepts[18])/1000000; break;
        case 20: celsius = (int_slopes[19]*milli_volts+int_intercepts[19])/1000000; break;
        case 21: celsius = (int_slopes[20]*milli_volts+int_intercepts[20])/1000000; break;
        case 22: celsius = (int_slopes[20]*milli_volts+int_intercepts[20])/1000000; break;
        case 23: break;
        default: break;
    }
    return celsius;
}

unsigned int lmt70_string_celsius(char *lmt70_temperature)
{
    float int_temp = lmt70_get_celsius();
    sprintf(lmt70_temperature, "%.3f", int_temp);
    lmt70_temperature[5] = '\n';
    
    unsigned int temp_l = strlen(lmt70_temperature);
    return temp_l;
}

void lmt70_uart(void)
{
    char lmt70_temperature[6];
    unsigned int temp_lmt70_l = lmt70_string_celsius(lmt70_temperature);
    for(unsigned int i = 0; i<temp_lmt70_l; i++)
    {
        UART_UartPutChar(lmt70_temperature[i]);           
    }
}
