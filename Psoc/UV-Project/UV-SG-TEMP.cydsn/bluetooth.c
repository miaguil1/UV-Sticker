#include "bluetooth.h"
#include "led.h"
#include "tmp116.h"
#include "battery.h"
#include "uv.h"

//Stack Handler to react to GAP events and the GATT Database Access Events
/* Start CYBLE component and register generic event handler */
static void BLE_Stack_Handler(uint32 eventCode, void *eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReq;
    switch(eventCode)
    {
        /**********************************************************
        *                       General Events
        ***********************************************************/
		case CYBLE_EVT_STACK_ON: /* This event received when component is Started */
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            LED_BLUE_Write((uint8) 0); //Turn BLUE LED ON
            break;
		case CYBLE_EVT_TIMEOUT: 
			break;
		case CYBLE_EVT_HARDWARE_ERROR:    
            /* This event indicates that some internal HW error has occurred. */
			break;
        case CYBLE_EVT_HCI_STATUS:
			break;
        /**********************************************************
        *                       GAP Events
        ***********************************************************/
        case CYBLE_EVT_GAP_AUTH_REQ:
            break;
        case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
            break;
        case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
            break;
        case CYBLE_EVT_GAP_AUTH_COMPLETE:
            break;
        case CYBLE_EVT_GAP_AUTH_FAILED:
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if(CYBLE_STATE_DISCONNECTED == CyBle_GetState())
            {   
                /* Fast and slow advertising period complete, go to low power  
                 * mode (Hibernate mode) and wait for an external
                 * user event to wake up the device again */
                //CySysPmHibernate();
            }
            break;
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            LED_BLUE_Write((uint8) 255); //Turn BLUE LED OFF
            break;
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            /* Put the device to discoverable mode so that remote can search it. */
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            temperature_Notify = 0;
            uv_Power_Notify = 0;
            LED_BLUE_Write((uint8) 0); //Turn BLUE LED ON
            break;
        case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
            break;
        case CYBLE_EVT_GAPC_CONNECTION_UPDATE_COMPLETE:
            break;
        case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
            break;

        /**********************************************************
        *                       GATT Events
        ***********************************************************/
        case CYBLE_EVT_GATT_CONNECT_IND:
            BLE_Connection_Handle = *(CYBLE_CONN_HANDLE_T *)eventParam;
            //update_UV(); //Update the GATT database the current value of the LED
            //update_tmp116(); //Update the GATT database with the current Temperature
            //update_battery(); //Update the GATT database with the current Battery Level
            //LED_BLUE_Write((uint8) 0); //Turn BLUE LED OFF
            break;
        case CYBLE_EVT_GATT_DISCONNECT_IND:
            break;
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReq = (CYBLE_GATTS_WRITE_REQ_PARAM_T *)eventParam;
            if(wrReq->handleValPair.attrHandle == CYBLE_UV_MEASUREMENT_POWER_DENSITY_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReq->handleValPair, 0, &BLE_Connection_Handle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                uv_Power_Notify = wrReq->handleValPair.value.val[0];
            }
            if(wrReq->handleValPair.attrHandle == CYBLE_UV_MEASUREMENT_UV_INDEX_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReq->handleValPair, 0, &BLE_Connection_Handle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                uv_Index_Notify = wrReq->handleValPair.value.val[0];
            }
            if(wrReq->handleValPair.attrHandle == CYBLE_BODY_TEMPERATURE_TEMPERATURE_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReq->handleValPair, 0, &BLE_Connection_Handle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                temperature_Notify = wrReq->handleValPair.value.val[0];
            }
            if(wrReq->handleValPair.attrHandle == CYBLE_BATTERY_BATTERY_LEVEL_CLIENT_CHARACTERISTIC_CONFIGURATION_DESC_HANDLE)
            {
                CyBle_GattsWriteAttributeValue(&wrReq->handleValPair, 0, &BLE_Connection_Handle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                battery_Notify = wrReq->handleValPair.value.val[0];
            }          

            CyBle_GattsWriteRsp(BLE_Connection_Handle);
            break;
        case CYBLE_EVT_GATTS_INDICATION_ENABLED:
            break;
        case CYBLE_EVT_GATTS_INDICATION_DISABLED:
            break;
        case CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
            /* Triggered on server side when client sends read request and when
            * characteristic has CYBLE_GATT_DB_ATTR_CHAR_VAL_RD_EVENT property set.
            * This event could be ignored by application unless it need to response
            * by error response which needs to be set in gattErrorCode field of
            * event parameter. */
            break;

		/**********************************************************
        *                       Other Events
        ***********************************************************/
        case CYBLE_EVT_PENDING_FLASH_WRITE:
            /* Inform application that flash write is pending. Stack internal data 
            * structures are modified and require to be stored in Flash using 
            * CyBle_StoreBondingData() */
            break;
        default:
			break;       
    }
}

void bluetooth_start(void)
{
    CyBle_Start(BLE_Stack_Handler); //Declares the BLE stack handler and begins processing through
    /* Register service specific callback functions */
}

void bluetooth_process(void)
{
    CyBle_ProcessEvents(); //Allows BLE stack to process pending 
}

void bluetooth_stop(void)
{
    CyBle_Stop();    
}

