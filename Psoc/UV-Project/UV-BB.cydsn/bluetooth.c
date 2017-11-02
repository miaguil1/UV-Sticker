#include "bluetooth.h"
#include "watchdog.h"

static CYBLE_CONN_HANDLE_T ble_connection_handle;
static volatile int bluetooth_indications = 0;

void AppCallBack(uint32 event, void* eventParam)
{
    CYBLE_API_RESULT_T apiResult;
    CYBLE_GAP_BD_ADDR_T localAddr;
    CYBLE_GAP_AUTH_INFO_T *authInfo;
    uint8 i;

    switch (event)
	{
        /**********************************************************
        *                       General Events
        ***********************************************************/
		case CYBLE_EVT_STACK_ON: /* This event received when component is Started */
            /* Enter in to discoverable mode so that remote can search it. */
            apiResult = CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            if(apiResult != CYBLE_ERROR_OK)
            {
                //DBG_PRINTF("StartAdvertisement API Error: %d \r\n", apiResult);
            }
            //DBG_PRINTF("Bluetooth On, StartAdvertisement with addr: ");
            localAddr.type = 0u;
            CyBle_GetDeviceAddress(&localAddr);
            for(i = CYBLE_GAP_BD_ADDR_SIZE; i > 0u; i--)
            {
                //DBG_PRINTF("%2.2x", localAddr.bdAddr[i-1]);
            }
            //DBG_PRINTF("\r\n");
            break;
		case CYBLE_EVT_TIMEOUT: 
        	/* CYBLE_GAP_ADV_MODE_TO - Advertisement time set by application is expired */
    	    /* CYBLE_GAP_AUTH_TO - Authentication procedure timeout */
            /* CYBLE_GAP_SCAN_TO - Scan time set by application is expired */
            /* CYBLE_GATT_RSP_TO - GATT procedure timeout */
            //DBG_PRINTF("CYBLE_EVT_TIMEOUT: %x \r\n", *(uint8 *)eventParam);
			break;
		case CYBLE_EVT_HARDWARE_ERROR:    /* This event indicates that some internal HW error has occurred. */
            //DBG_PRINTF("Hardware Error \r\n");
			break;
        case CYBLE_EVT_HCI_STATUS:
            //DBG_PRINTF("CYBLE_EVT_HCI_STATUS: %x \r\n", *(uint8 *)eventParam);
			break;

        /**********************************************************
        *                       GAP Events
        ***********************************************************/
        case CYBLE_EVT_GAP_AUTH_REQ:
//            DBG_PRINTF("CYBLE_EVT_AUTH_REQ: security=%x, bonding=%x, ekeySize=%x, err=%x \r\n", 
//                (*(CYBLE_GAP_AUTH_INFO_T *)eventParam).security, 
//                (*(CYBLE_GAP_AUTH_INFO_T *)eventParam).bonding, 
//                (*(CYBLE_GAP_AUTH_INFO_T *)eventParam).ekeySize, 
//                (*(CYBLE_GAP_AUTH_INFO_T *)eventParam).authErr);
            break;
        case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
            //DBG_PRINTF("CYBLE_EVT_PASSKEY_ENTRY_REQUEST \r\n");
            break;
        case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
            //DBG_PRINTF("CYBLE_EVT_PASSKEY_DISPLAY_REQUEST %6.6ld \r\n", *(uint32 *)eventParam);
            break;
        case CYBLE_EVT_GAP_AUTH_COMPLETE:
            authInfo = (CYBLE_GAP_AUTH_INFO_T *)eventParam;
            (void)authInfo;
//            DBG_PRINTF("AUTH_COMPLETE: security:%x, bonding:%x, ekeySize:%x, authErr %x \r\n", 
//                                    authInfo->security, authInfo->bonding, authInfo->ekeySize, authInfo->authErr);
            break;
        case CYBLE_EVT_GAP_AUTH_FAILED:
            //DBG_PRINTF("CYBLE_EVT_AUTH_FAILED: %x \r\n", *(uint8 *)eventParam);
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            //DBG_PRINTF("CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP, state: %x\r\n", CyBle_GetState());
            if(CYBLE_STATE_DISCONNECTED == CyBle_GetState())
            {   
                /* Fast and slow advertising period complete, go to low power  
                 * mode (Hibernate mode) and wait for an external
                 * user event to wake up the device again */
                //DBG_PRINTF("Hibernate \r\n");
                Advertising_LED_Write(LED_OFF);
                Disconnect_LED_Write(LED_ON);
                LowPower_LED_Write(LED_OFF);
            #if (DEBUG_UART_ENABLED == ENABLED)
                //while((UART_DEB_SpiUartGetTxBufferSize() + UART_DEB_GET_TX_FIFO_SR_VALID) != 0);
            #endif /* (DEBUG_UART_ENABLED == ENABLED) */
                SW2_ClearInterrupt();
                Wakeup_Interrupt_ClearPending();
                Wakeup_Interrupt_Start();
                CySysPmHibernate();
            }
            break;
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
//            DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_CONNECTED: %x \r\n", *(uint8 *)eventParam);
            Advertising_LED_Write(LED_OFF);
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
//            DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_DISCONNECTED\r\n");
            LowPower_LED_Write(LED_OFF);
            /* Put the device to discoverable mode so that remote can search it. */
            apiResult = CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            if(apiResult != CYBLE_ERROR_OK)
            {
//                DBG_PRINTF("StartAdvertisement API Error: %x \r\n", apiResult);
            }
            break;
        case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
//            DBG_PRINTF("ENCRYPT_CHANGE: %x \r\n", *(uint8 *)eventParam);
            break;
        case CYBLE_EVT_GAPC_CONNECTION_UPDATE_COMPLETE:
//            DBG_PRINTF("CYBLE_EVT_CONNECTION_UPDATE_COMPLETE: %x \r\n", *(uint8 *)eventParam);
            break;
        case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
//            DBG_PRINTF("CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT \r\n");
            break;

        /**********************************************************
        *                       GATT Events
        ***********************************************************/
        case CYBLE_EVT_GATT_CONNECT_IND:
//            DBG_PRINTF("CYBLE_EVT_GATT_CONNECT_IND: %x, %x \r\n", cyBle_connHandle.attId, cyBle_connHandle.bdHandle);
            break;
        case CYBLE_EVT_GATT_DISCONNECT_IND:
//            DBG_PRINTF("CYBLE_EVT_GATT_DISCONNECT_IND \r\n");
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
//            DBG_PRINTF("CYBLE_EVT_GATT_WRITE_REQ: %x = ",((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam)->handleValPair.attrHandle);
            ShowValue(&((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam)->handleValPair.value);
            (void)CyBle_GattsWriteRsp(((CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam)->connHandle);
            break;
        case CYBLE_EVT_GATTS_INDICATION_ENABLED:
//            DBG_PRINTF("CYBLE_EVT_GATTS_INDICATION_ENABLED \r\n");
            break;
        case CYBLE_EVT_GATTS_INDICATION_DISABLED:
//            DBG_PRINTF("CYBLE_EVT_GATTS_INDICATION_DISABLED \r\n");
            break;
        case CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
            /* Triggered on server side when client sends read request and when
            * characteristic has CYBLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT property set.
            * This event could be ignored by application unless it need to response
            * by error response which needs to be set in gattErrorCode field of
            * event parameter. */
//            DBG_PRINTF("CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ: handle: %x \r\n", 
//                ((CYBLE_GATTS_CHAR_VAL_READ_REQ_T *)eventParam)->attrHandle);
            break;

		/**********************************************************
        *                       Other Events
        ***********************************************************/
        case CYBLE_EVT_PENDING_FLASH_WRITE:
            /* Inform application that flash write is pending. Stack internal data 
            * structures are modified and require to be stored in Flash using 
            * CyBle_StoreBondingData() */
//            DBG_PRINTF("CYBLE_EVT_PENDING_FLASH_WRITE\r\n");
            break;

        default:
//            DBG_PRINTF("OTHER event: %lx \r\n", event);
			break;
	}
}

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
        case CYBLE_EVT_HTSS_INDICATION_ENABLED: 
            bluetooth_indications = 1; 
            break;
        case CYBLE_EVT_HTSS_INDICATION_DISABLED: 
            bluetooth_indications = 0; 
            break;
        default: 
            break;
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


