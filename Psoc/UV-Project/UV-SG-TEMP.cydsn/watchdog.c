#include "watchdog.h"
#include "uv.h"
#include "tmp116.h"
#include "battery.h"
#include "bluetooth.h"
#include "guvb_c31sm.h"
#include "adafruit_guva.h"

void WDT_ISR_Handler()
{
    uint32 reason = CySysWdtGetInterruptSource();
    // Update Gatt Database every 8 seconds
    if(reason & CY_SYS_WDT_COUNTER2_INT)
    {
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
//            system_wakeup();    // Waking up System from sleep to perform measurements
            update_tmp116();
//            update_UV();
//            update_battery();
        
//            guvb_c31sm_wakeup();
//            guvb_c31sm_range();
//            uint16 b_scale = guvb_c31sm_nvm();
//            CyDelay(200);
//            uint8 nvm_control = guvb_c31sm_read_register(0x30);
//            uint16 sensor_value = guvb_c31sm_get_uint16();
//            guvb_c31sm_shutdown();            
//            
//            uint8 lsb1 = sensor_value & 0xFF;
//            uint8 msb1 = sensor_value >> 8;
//            UART_UartPutChar(lsb1);
//            UART_UartPutChar(msb1);
            
//            uint8 lsb2 = b_scale & 0xFF;
//            uint8 msb2 = b_scale >> 8;
//            UART_UartPutChar(lsb2);
//            UART_UartPutChar(msb2);
//            
//            UART_UartPutChar(nvm_control);           
            
//            uint16 guva = (uint16) adc_acquire_channel(3);
//            uint8 lsb3 = guva & 0xFF;
//            uint8 msb3 = guva >> 8;
//            UART_UartPutChar(lsb3);
//            UART_UartPutChar(msb3);
            
//            system_sleep(); // Took Measurements, now going back into sleep mode.
        }
        
        system_red_led_blink(); //Blink LED 
    }
    CySysWdtClearInterrupt(reason); //Clear the WDT Interrupt
}

void update_timer0(void)
{
    CySysWdtUnlock();
    /* Update the WDT_MATCH counter with the current match value + desired match value */
    uint32 new_match_value0 = CySysWdtGetMatch(CY_SYS_WDT_COUNTER0) + 4096*wdt0_frequency;
    CySysWdtSetMatch(CY_SYS_WDT_COUNTER0, new_match_value0); //Updating the new match rate of the Watchdog Counter
    CySysWdtLock(); 
}

void update_timer1(void)
{
    CySysWdtUnlock();
    /* Update the WDT_MATCH counter with the current match value + desired match value */
    uint32 new_match_value1 = CySysWdtGetMatch(CY_SYS_WDT_COUNTER1) + 4096*wdt1_frequency;
//    uint32 new_match_value1 = CySysWdtGetMatch(CY_SYS_WDT_COUNTER1) + 51625;
    CySysWdtSetMatch(CY_SYS_WDT_COUNTER1, new_match_value1); //Updating the new match rate of the Watchdog Counter
    CySysWdtLock();
}

void watchdog_init(void)
{
    WDT_ISR_StartEx(WDT_ISR_Handler);    
}

void wdt1_enable(void)
{   
    CySysWdtUnlock(); 
    CySysWdtEnable(CY_SYS_WDT_COUNTER1_MASK);
    CyDelay(1);
    CySysWdtLock(); 
}

void wdt2_enable(void)
{
    CySysWdtUnlock(); 
    CySysWdtEnable(CY_SYS_WDT_COUNTER2_MASK);
    CyDelay(1);
    CySysWdtLock(); 
}

void wdt1_disable(void)
{   
    CySysWdtUnlock(); 
    CySysWdtDisable(CY_SYS_WDT_COUNTER1_MASK);
    CyDelay(1);
    CySysWdtLock(); 
}

void wdt2_disable(void)
{   
    CySysWdtUnlock(); 
    CySysWdtDisable(CY_SYS_WDT_COUNTER2_MASK);
    CyDelay(1);
    CySysWdtLock(); 
}

void watchdog_enable(void)
{
    /* Unlock the WDT registers for modification */
    CySysWdtUnlock(); 
    /* Enable the specified WDT counter */
    //CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK);
//    CySysWdtEnable(CY_SYS_WDT_COUNTER1_MASK);
    CySysWdtEnable(CY_SYS_WDT_COUNTER2_MASK);
//    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK | CY_SYS_WDT_COUNTER1_MASK); // used to cascade timer and get longer period of time
//    CySysWdtEnable(CY_SYS_WDT_COUNTER1_MASK | CY_SYS_WDT_COUNTER2_MASK); // used to cascade timer and get longer period of time

    //    /* check if counter 1 is enabled, otherwise keep looping here */
//    while(!CySysWdtReadEnabledStatus(CY_SYS_WDT_COUNTER1));
//    /* check if counter 2 is enabled, otherwise keep looping here */
//    while(!CySysWdtReadEnabledStatus(CY_SYS_WDT_COUNTER2));
        
    /* Locks out configuration changes to the Watchdog timer registers */
    CySysWdtLock(); 
}

void watchdog_disable(void)
{
    /* Unlock the WDT registers for modification */
    CySysWdtUnlock(); 
    /* Disable the specified WDT counter */
//    CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK);  // Disabling Counter #0
    CySysWdtDisable(CY_SYS_WDT_COUNTER1_MASK);  // Disabling Counter #1
    CySysWdtDisable(CY_SYS_WDT_COUNTER2_MASK);  // Disabling Counter #2
    /* Locks out configuration changes to the Watchdog timer registers */
    CySysWdtLock(); 
}

void watchdog_start(void)
{
    watchdog_init(); //Initializing the Watchdog Timer
    watchdog_setup(); //Setuping the Watchdog Timer
    watchdog_enable(); //Enabling the Watchdog Timer
}

/* Setup the Watchdog Timer Configuration */
void watchdog_setup(void)
{     
//    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER0); // Clear WDT 0 interrupt
//    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER1); // Clear WDT 1 interrupt
    CySysWdtClearInterrupt(CY_SYS_WDT_COUNTER2); // Clear WDT 2 interrupt
    
    CySysWdtUnlock(); // Enable modification of the WDT Timers
    
    //system_enable_wco(); //Enable WCO Crystal Oscillator
    //CySysClkSetLfclkSource(CY_SYS_CLK_LFCLK_SRC_WCO); // Setting Low-Frequency Clock to 32.768 kHz Watch Crystal Oscillator
    //CySysClkWcoSetPowerMode(CY_SYS_CLK_WCO_LPM); // Settting the WCO to low power mode 
    //CySysClkIloStop(); // Disabling the ILO since we are using the ILO
    
    // Turn off the WDTs (all three of them)
//    CySysWdtDisable(CY_SYS_WDT_COUNTER0_MASK); 
//    CySysWdtDisable(CY_SYS_WDT_COUNTER1_MASK);
    CySysWdtDisable(CY_SYS_WDT_COUNTER2_MASK);
    
    CyDelay(1); // Waiting for the system to disable the counters and wait for them to stop
    
//    CySysWdtSetMode(CY_SYS_WDT_COUNTER0,CY_SYS_WDT_MODE_INT); // Make Timer 0 cause an interrupt on match
//    uint32 match_rate0 = wdt0_frequency * 4096; // Setting Match rate for the period of WDT #0 based on Desired frequency
//    CySysWdtSetMatch(CY_SYS_WDT_COUNTER0, match_rate0);  // Setting the Match Rate counter of Timer #0
//
//    CySysWdtSetCascade(CY_SYS_WDT_CASCADE_01);  // Setting the cascade to trigger both Timer 1 and Timer 2    
    
//    CySysWdtSetMode(CY_SYS_WDT_COUNTER1,CY_SYS_WDT_MODE_INT); // Make Timer 1 cause an interrupt on match
//    uint32 match_rate1 = wdt1_frequency * 4096; // Setting Match rate for the period of WDT #1 based on Desired frequency
//    CySysWdtSetMatch(CY_SYS_WDT_COUNTER1, match_rate1);  // Setting the Match Rate counter of Timer #1
    
    //CySysWdtSetCascade(CY_SYS_WDT_CASCADE_12);  // Setting the cascade to trigger both Timer 1 and Timer 2
    
    CySysWdtSetMode(CY_SYS_WDT_COUNTER2,CY_SYS_WDT_MODE_INT); // Make Timer 2 cause an interrupt on a bit toggle
    CySysWdtSetToggleBit(timer2_toggle);   //   When the bit toggles, an interrupt is generated
    
    CySysWdtLock(); // Disable modification of the WDT Timers 
}
