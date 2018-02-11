#ifndef __WATCHDOG_H
#define __WATCHDOG_H
#include "system.h"

void WDT_ISR_Handler(void);
void watchdog_start(void);
void update_timer0(void);
void update_timer1(void);
void wdt1_enable(void);
void wdt2_enable(void);
void wdt1_disable(void);
void wdt2_disable(void);
void watchdog_setup(void);
void watchdog_init(void);
void watchdog_enable(void);
void watchdog_disable(void);

#endif // __WATCHDOG_H
