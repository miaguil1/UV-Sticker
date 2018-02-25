#ifndef __SYSTEM_H
#define __SYSTEM_H

#include <string.h>
#include <stdio.h>    
#include <project.h>   
#include <stdlib.h>
#include <stdarg.h>
    
extern const float vdd_calibration;    
extern const float uv_gain;
extern const float uv_respons;
extern const float amp_iov[];
extern const float amp_ibc[];
extern const float sg_resistors[];
extern uint8 uv_Power_Notify; //Boolean to determine UV power notification is on
extern uint8 uv_Index_Notify; //Boolean to determine UV Index notification is on
extern uint8 temperature_Notify; //Boolean to determine Temperature notification is on
extern uint8 respiration_Notify; //Boolean to determine Respiration notification is on
extern uint8 battery_Notify; //Boolean to determine Battery notification is on
extern const uint32 wdt0_frequency;
extern const uint32 wdt1_frequency;
extern const uint32 timer2_toggle;

#define BATTERY_CHANNEL             (2u)        /* Battery channel used to measure the voltage of the battery */
#define UV_CHANNEL                  (1u)        /* UV channel used to measure the current through the photodiode */
#define GUVA_CHANNEL                (3u)        /* GUVA channel used to measure the current through the photodiode */

void system_init_hardware(void);

void system_enable_interrupts(void);

void system_disable_interrupts(void);

void system_red_led_blink(void);

void adc_conversion(void);

void system_read_i2c(uint32 register_address, uint8 *register_value, uint32 register_byte_count);

void system_write_i2c(uint32 register_address, uint8 register_value[], uint32 register_byte_count); 

uint16 adc_acquire_channel(uint32);

void adc_sleep(void);

void adc_wakeup(void);

void i2c_sleep(void);

void i2c_wakeup(void);

void uart_sleep(void);

void uart_wakeup(void);

void opamp_sleep(void);

void opamp_wakeup(void);

void system_sleep(void);

void system_deepsleep(void);

void system_wakeup(void); 

void system_stop_eco(void);

void system_use_wco(void);

void system_use_eco(void);

void system_set_imo(int);

void watchdog_init(void);

void watchdog_start(void);

void watchdog_stop(void);

void system_enable_wco(void);

#endif // __SYSTEM_H

