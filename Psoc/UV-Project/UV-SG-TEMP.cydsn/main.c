#include "system.h"
#include "bluetooth.h"
#include "uv.h"
#include "battery.h"
#include "tmp116.h"
#include "led.h"
#include "watchdog.h"

// If no watchdog Timer possible, then use Time set by Timer component itself
//Timer_ISR_StartEx(Timer_ISR_Handler); //Starting the Timer ISR Handler Stack
//CY_ISR(Timer_ISR_Handler)
//{
//    LED_GREEN_Write(~LED_GREEN_Read()); //Turn GREEN LED the opposite State
//    
//    //Insert update functions for different components & sensors
//    update_tmp116();
//    //update_LED();
//    //update_battery();
//    //update_uv_density(); 
//    //update_uv_power(); 
//    
//    Timer_ClearInterrupt(Timer_INTR_MASK_TC); // Clear interrupt of Timer
//}

int main()
{
    system_enable_interrupts(); // Enabling Global Interrupts
    system_init_hardware(); // Starting all hardware modules: UART, I2C, SG-AMP, UV-AMP, ADC 
    LED_BLUE_Write((uint8) 0); // Turn BLUE LED ON
    bluetooth_start(); // Starting CyBLE, Generic Event Handler 
    watchdog_start(); // Starting the Watchdog Timer
    //system_sleep(); // Telling System and Components to go into Sleep Mode
    // This function is only available with WCO not ILO
//    CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP); // Bluetooth Stack goes into Deep Sleep        
	while(1) 
    {   
        bluetooth_process(); //Process BLE Stack Events
        //system_deepsleep(); // Telling System to go into Deep Sleep
	}   
}

