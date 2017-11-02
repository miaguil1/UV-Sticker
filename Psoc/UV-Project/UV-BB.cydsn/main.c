
#include "lmt70.h"
#include "system.h"
#include "tmp116.h"
#include "uv.h"
#include "adafruit_guva.h"
#include "temperature_service.h"

/* Macro definitions */
#define LOW                 (0u)
#define HIGH                (1u)
#define D1                  (1u)
#define D2                  (2u)
#define D3                  (3u)
#define D4                  (4u)
#define D5                  (5u)
#define NO_OF_CHANNELS      (4u)
#define CLEAR_SCREEN        (0x0C)
#define CONVERT_TO_ASCII    (0x30u)

//char lmt70_temperature[6];
uint8 busStatus = CYBLE_STACK_STATE_FREE;           /* Status of stack queue */

volatile uint32 mainTimer = 0;

CY_ISR(Pin_SW2_Handler)
{
    RED_LED_Write(~RED_LED_Read()); //Blinks On
    CyDelay(500); //Waits half a second
    RED_LED_Write(~RED_LED_Read()); //Blinks Off
    Pin_SW2_ClearInterrupt(); //Clears the interrupt on the pin
}

int main(void)
{    
    system_enable_interrupts(); /* Enable global interrupts. */
        CyGlobalIntEnable;  

    Disconnect_LED_Write(LED_OFF);
    Advertising_LED_Write(LED_OFF);
    LowPower_LED_Write(LED_OFF);

    
    /* Start CYBLE component and register generic event handler */
    CyBle_Start(AppCallBack);
    /* Register service specific callback functions */
    CyBle_BasRegisterAttrCallback(BasCallBack);
    CyBle_HtsRegisterAttrCallback(HtsCallBack);
    
	ADC_Start();
    WDT_Start();
    init_hardware(); //Initializing All Internal Hardware Components
    
    Wakeup_Interrupt_StartEx(Pin_SW2_Handler); //Initialize Internal Interrupt on SW2 Pin
    
    for(;;)
    {   


    }
}
