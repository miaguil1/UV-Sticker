#include "watchdog.h"


#define NOTIFY_EVERY_N_SECONDS 1800


static volatile int watchdog_get_up = 0;
static volatile unsigned int watchdog_counter = 0xFFFFFFE1;


CY_ISR(watchdog_interrupt_handler)
{
    //watchdog_interrupt_ClearPending();
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
    if ((watchdog_counter++ % (NOTIFY_EVERY_N_SECONDS/2)) == 0) { watchdog_get_up = 1; }
}


static void watchdog_init(void)
{
    //watchdog_interrupt_StartEx(watchdog_interrupt_handler);    
}


static void watchdog_start(void)
{
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
}


static void watchdog_stop(void)
{
    CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK);
}


static int watchdog_is_up(void)
{
    if (watchdog_get_up == 1) { watchdog_get_up = 0; return 1; }
    else { return 0; }
}


watchdog_t watchdog_table = {
	&watchdog_init, 
    &watchdog_start,
    &watchdog_stop, 
    &watchdog_is_up
};


watchdog_t * const watchdog = &watchdog_table;

