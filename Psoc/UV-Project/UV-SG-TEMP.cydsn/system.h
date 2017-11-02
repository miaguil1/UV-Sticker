#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <string.h>
#include <stdio.h>    
#include <project.h>   

extern const float vdd_calibration;    
extern const float uv_gain[];
extern const float uv_respons[];
extern const float amp_iov[];
extern const float amp_ibc[];
extern const float sg_resistors[];

void init_hardware(void);

void adc_conversion(void);

uint16 adc_acquire_channel(uint32);

void adc_wakeup(void);

void adc_wakeup(void);
    
void system_enable_interrupts(void);

void system_disable_interrupts(void);

void system_sleep(void);

void system_deepsleep(void);

void system_stop_eco(void);

void system_set_imo(int);

#endif // __SYSTEM_H

