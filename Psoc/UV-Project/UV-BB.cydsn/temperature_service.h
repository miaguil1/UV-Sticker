#ifndef __TEMPERATURE_SERVICE_H
#define __TEMPERATURE_SERVICE_H

#include "system.h"
#include "lmt70.h"
#include "tmp116.h"
#include "bluetooth.h"
#include "uart.h"
    
#define HTS_TEMP_DATA_MIN_SIZE      (5u)

void HtsCallBack(uint32 event, void *eventParam);
void MeasureTemperature(char);

extern uint16 temperatureMeasure;
    
#endif // __TEMPERATURE_SERVICE_H