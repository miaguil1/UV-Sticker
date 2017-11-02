/*
File Name: bas.h
Battery Management Service
Measures the Percent of the Battery Life
*/
#include <project.h>

/***************************************
*          Constants
***************************************/

#define BATTERY_MAX         (3000)      /* Use 3V as battery voltage starting */
#define BATTERY_MID         (2800)      /* Use 2.8V as a knee point of discharge curve @ 29% */      
#define BATTERY_MIN         (2000)      /* Use 2V as a cut-off of battery life */
    
#define BAS_SERVICE_MEASURE         (1u)        /* First BAS service to measure actual battery level */  

#define ADC_VREF_MASK               (0x000000F0Lu)  // ADC VREF Register Mask

/***************************************
*       Function Prototypes
***************************************/
void BasCallBack(uint32 event, void *eventParam);
void MeasureBattery(void);

/***************************************
* External data references
***************************************/
extern uint16 batteryMeasureNotify;
