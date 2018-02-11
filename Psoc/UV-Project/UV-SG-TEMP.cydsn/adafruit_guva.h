#ifndef __ADAFRUIT_GUVA_H
#define __ADAFRUIT_GUVA_H
#include "system.h"
    
float adafruit_guva_measure(void);
float adafruit_guva_get_pd(void);
void adafruit_guva_get_pd_string(char*);
void adafruit_guva_uart(void);

#endif // __ADAFRUIT_GUVA_H