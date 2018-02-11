#ifndef __BATTERY_H
#define __BATTERY_H
    
#include "system.h"

/***************************************
*          Constants
***************************************/

                         

#define MEASURE_BATTERY_MAX         (3000)      /* Use 3V as battery voltage starting */
#define MEASURE_BATTERY_MID         (2800)      /* Use 2.8V as a knee point of discharge curve @ 29% */
#define MEASURE_BATTERY_MID_PERCENT (29)        
#define MEASURE_BATTERY_MIN         (2000)      /* Use 2V as a cut-off of battery life */
#define LOW_BATTERY_LIMIT           (10)        /* Low level limit in percent to switch on LED */

#define ADC_VREF_MASK               (0x000000F0Lu)
    
    
/***************************************
*       Function Prototypes
***************************************/
uint8 measure_battery(void);
void update_battery(void);

#endif // __BATTERY_H
