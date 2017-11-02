
#include "lmt70.h"
#include "system.h"
#include "tmp116.h"
#include "uv.h"
#include "adafruit_guva.h"

/* Macro definitions */
#define LOW                 (0u)
#define HIGH                (1u)
#define D1                  (1u)
#define SG1                 (2u)
#define NO_OF_CHANNELS      (4u)
#define CLEAR_SCREEN        (0x0C)
#define CONVERT_TO_ASCII    (0x30u)

//char lmt70_temperature[6];


int main(void)
{    
    system_enable_interrupts(); /* Enable global interrupts. */
    
    init_hardware(); //Initializing All Internal Hardware Components
    
    for(;;)
    {   
//        UART_UartPutChar('s'); //Just Sending the Letter 's' to break up UART communication
//        lmt70_uart(); //Sending the value of the LMT70 over UART
//               
//        UART_UartPutChar('s'); //Just Sending the Letter 's' to break up UART communication
//        tmp116_uart();
//        for(unsigned int i=1; i<=5;i++)
//        {
////            unsigned int bb1 = adc_acquire_channel(3+i);
////            char part1 = bb1 & 0xFF;
////            char part2 = (bb1 >> 8) & 0xFF;
////            UART_UartPutChar(part1);
////            UART_UartPutChar(part2);
//            uv_uart(i);
//        }

        unsigned int bb1 = adc_acquire_channel(8);
        char part1 = bb1 & 0xFF;
        char part2 = (bb1 >> 8) & 0xFF;
        UART_UartPutChar(part1);
        UART_UartPutChar(part2);
        uv_uart(5);
        //adafruit_guva_uart();
        CyDelay(500); //Delay by half a second 

    }
}

/* [] END OF FILE */
