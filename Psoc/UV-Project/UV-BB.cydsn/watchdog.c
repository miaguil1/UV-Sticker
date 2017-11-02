#include "watchdog.h"


#define NOTIFY_EVERY_N_SECONDS 1800


static volatile int watchdog_get_up = 0;
static volatile unsigned int watchdog_counter = 0xFFFFFFE1;


CY_ISR(watchdog_interrupt_handler)
{
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0_INT);
    if ((watchdog_counter++ % (NOTIFY_EVERY_N_SECONDS/2)) == 0)
    { 
        watchdog_get_up = 1; 
    }
}

/*******************************************************************************
* Function Name: Timer_Interrupt
********************************************************************************
*
* Summary:
*  Handles the Interrupt Service Routine for the WDT timer.
*
*******************************************************************************/
CY_ISR(Timer_Interrupt)
{
    if(CySysWdtGetInterruptSource() & WDT_INTERRUPT_SOURCE)
    {
        static uint8 led = LED_OFF;
        
        /* Blink LED to indicate that device advertises */
        if(CYBLE_STATE_ADVERTISING == CyBle_GetState())
        {
            led ^= LED_OFF;
            Advertising_LED_Write(led);
        }
        
        /* Indicate that timer is raised to the main loop */
        mainTimer++;
        
        /* Clears interrupt request  */
        CySysWdtClearInterrupt(WDT_INTERRUPT_SOURCE);
    }
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
    if (watchdog_get_up == 1)
    { 
        watchdog_get_up = 0; return 1;
    }
    else 
    { 
        return 0; 
    }
}

/*******************************************************************************
* Function Name: WDT_Start
********************************************************************************
*
* Summary:
*  Configures WDT to trigger an interrupt every second.
*
*******************************************************************************/

void WDT_Start(void)
{
    /* Unlock the WDT registers for modification */
    CySysWdtUnlock(); 
    /* Setup ISR */
    WDT_Interrupt_StartEx(&Timer_Interrupt);
    /* Write the mode to generate interrupt on match */
    CySysWdtWriteMode(WDT_COUNTER, CY_SYS_WDT_MODE_INT);
    /* Configure the WDT counter clear on a match setting */
    CySysWdtWriteClearOnMatch(WDT_COUNTER, WDT_COUNTER_ENABLE);
    /* Configure the WDT counter match comparison value */
    CySysWdtWriteMatch(WDT_COUNTER, WDT_1SEC);
    /* Reset WDT counter */
    CySysWdtResetCounters(WDT_COUNTER);
    /* Enable the specified WDT counter */
    CySysWdtEnable(WDT_COUNTER_MASK);
    /* Lock out configuration changes to the Watchdog timer registers */
    CySysWdtLock();    
}


/*******************************************************************************
* Function Name: WDT_Stop
********************************************************************************
*
* Summary:
*  This API stops the WDT timer.
*
*******************************************************************************/
void WDT_Stop(void)
{
    /* Unlock the WDT registers for modification */
    CySysWdtUnlock(); 
    /* Disable the specified WDT counter */
    CySysWdtDisable(WDT_COUNTER_MASK);
    /* Locks out configuration changes to the Watchdog timer registers */
    CySysWdtLock();    
}

