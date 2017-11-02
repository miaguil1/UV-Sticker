#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <string.h>
#include <stdio.h>    
#include <project.h>   
#include <stdarg.h>
    
#define ENABLED                     (1u)
#define DISABLED                    (0u)

#define DEBUG_UART_ENABLED          ENABLED

#define LED_ON                      (0u)
#define LED_OFF                     (1u)

#define ADC_TEMPERATURE_CHANNEL     (0x00u)
#define ADC_BATTERY_CHANNEL         (0x01u)

#define WDT_COUNTER                                   (CY_SYS_WDT_COUNTER1)
#define WDT_COUNTER_MASK                              (CY_SYS_WDT_COUNTER1_MASK)
#define WDT_INTERRUPT_SOURCE                          (CY_SYS_WDT_COUNTER1_INT) 
#define WDT_COUNTER_ENABLE                            (1u)
#define WDT_1SEC                                      (32767u)    
    
extern const float vdd_calibration;    
extern const float uv_gain[];
extern const float uv_respons[];
extern const float amp_iov[];
extern const float amp_ibc[];
extern const float sg_resistors[];
extern volatile uint32 mainTimer;

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

void ShowValue(CYBLE_GATT_VALUE_T *value);

void Set32ByPtr(uint8 ptr[], uint32 value);

void AppCallBack(uint32 event, void* eventParam);

#endif // __SYSTEM_H

