#include "system.h"
#include "bluetooth.h"
#include "uv.h"
#include "battery.h"
#include "tmp116.h"
#include "led.h"
#include "watchdog.h"
#include "guvb_c31sm.h"

int main()
{
    system_use_eco();   // Use External Fast frequency Clock
    system_use_wco();   // Use External Low frequency Clock
    system_enable_interrupts(); // Enabling Global Interrupts
    system_init_hardware(); // Starting all hardware modules: UART, I2C, SG-AMP, UV-AMP, ADC, GUVB-C31SM
    LED_BLUE_Write((uint8) 0); // Turn BLUE LED ON
    bluetooth_start(); // Starting CyBLE, Generic Event Handler 
    watchdog_start(); // Starting the Watchdog Timer
//    system_sleep(); // Telling System and Components to go into Sleep Mode
    // This function is only available with WCO not ILO
//    CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP); // Bluetooth Stack goes into Deep Sleep        
	while(1) 
    {   
        bluetooth_process(); //Process BLE Stack Events
        //system_deepsleep(); // Telling System to go into Deep Sleep
	}   
}

