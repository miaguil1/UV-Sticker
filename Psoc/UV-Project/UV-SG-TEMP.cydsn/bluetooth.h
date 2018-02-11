#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H
#include "system.h"   

CYBLE_CONN_HANDLE_T BLE_Connection_Handle;  //Bluetooth Connection Handle for Stack

//static void BLE_Stack_Handler(uint32 eventCode, void *eventParam);
void bluetooth_start(void);
void bluetooth_process(void);
void bluetooth_stop(void);
    

#endif // __BLUETOOTH_H

