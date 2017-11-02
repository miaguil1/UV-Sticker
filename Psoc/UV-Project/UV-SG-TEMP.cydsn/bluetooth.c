#include "bluetooth.h"
#include "watchdog.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>


static CYBLE_CONN_HANDLE_T ble_connection_handle;
static volatile int bluetooth_indications = 0;


static void ble_stack_handler(uint32 event, void *event_parameter)
{
    switch(event)
    {
        case CYBLE_EVT_STACK_ON: 					
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:		
        case CYBLE_EVT_TIMEOUT:
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            bluetooth_indications = 0;
            //CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);	    
            break;
        case CYBLE_EVT_GATT_CONNECT_IND:
            ble_connection_handle = *(CYBLE_CONN_HANDLE_T *)event_parameter;
            break;

        default: break;
    } 
}


void health_thermometer_handler(uint32 event, void* event_parameter)
{
    (void)event_parameter;
    switch(event)
    {
        case CYBLE_EVT_HTSS_INDICATION_ENABLED: bluetooth_indications = 1; break;
        case CYBLE_EVT_HTSS_INDICATION_DISABLED: bluetooth_indications = 0; break;
        default: break;
    }
}


static void bluetooth_start(void)
{
    CyBle_Start(ble_stack_handler);
    //CyBle_HtsRegisterAttrCallback(health_thermometer_handler);
}


static void bluetooth_process(void)
{
    CyBle_ProcessEvents();
}


static void bluetooth_stop(void)
{
    CyBle_Stop();    
}


static void bluetooth_send(char *format, ...)
{
    va_list argptr;
    va_start(argptr, format);
    int length = vsnprintf(NULL, 0, format, argptr);
    ++length;
    char *out = (char *)malloc(length);
    vsnprintf(out, length, format, argptr); 
    va_end(argptr);
    //CyBle_HtssSendIndication(ble_connection_handle, CYBLE_HTS_TEMP_MEASURE, length, (uint8 *)out);  
    free(out);  
}


static int bluetooth_is_connected(void)
{
    return (CyBle_GetState() == CYBLE_STATE_CONNECTED);
}


static int bluetooth_is_advertising(void)
{
    //return (CyBle_GetState() == CYBLE_STATE_ADVERTISING);
    return 1;
}


static int bluetooth_is_initializing(void)
{
    return (CyBle_GetState() == CYBLE_STATE_INITIALIZING);
}


static int bluetooth_bless_in_deepsleep(void)
{
    return ((bless_t)CyBle_GetBleSsState() == bless_deepsleep);
}


static int bluetooth_bless_in_eco_on(void)
{
    return ((bless_t)CyBle_GetBleSsState() == bless_eco_on);
}


static int bluetooth_bless_in_event_close(void)
{
    return ((bless_t)CyBle_GetBleSsState() == bless_event_close);
}


static blpm_t bluetooth_enter_deepsleep(void)
{
    return ((blpm_t)CyBle_EnterLPM((CYBLE_LP_MODE_T)blpm_deepsleep));
}


static CYBLE_CONN_HANDLE_T bluetooth_get_connection_handle(void)
{
    return ble_connection_handle;
}


static int bluetooth_indications_enabled(void)
{
    return (bluetooth_indications == 1);
}


bluetooth_t bluetooth_table = { 
    &bluetooth_start,
    &bluetooth_process,
    &bluetooth_stop,
    &bluetooth_send,
    &bluetooth_is_connected,
    &bluetooth_is_advertising,
    &bluetooth_is_initializing,
    &bluetooth_bless_in_deepsleep,
    &bluetooth_bless_in_eco_on,
    &bluetooth_bless_in_event_close,
    &bluetooth_enter_deepsleep,
    &bluetooth_get_connection_handle,
    &bluetooth_indications_enabled
};


bluetooth_t * const bluetooth = &bluetooth_table;

