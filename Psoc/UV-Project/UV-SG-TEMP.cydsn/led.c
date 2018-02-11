#include "led.h"

//Reads the state of the LED and writes that value into the GATT Database
void update_LED()
{
    CYBLE_GATTS_HANDLE_VALUE_NTF_T tempHandle; //Temporary BLE Handle
    int currentLed = (!LED_RED_Read());
    
    //If not connected, no need to update GATT Database/Server
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
    {
        return; //Leaves the function updateLED()
    }
    tempHandle.attrHandle = CYBLE_BATTERY_BATTERY_LEVEL_CHAR_HANDLE;
    // Casting the value to an unsigned 8 bit pointer
    tempHandle.value.val = (uint8 *)&currentLed; //Flipping LED light since GND is on
    tempHandle.value.len = 1;
    if(CYBLE_GATT_ERR_NONE == CyBle_GattsReadAttributeValue(&tempHandle, NULL, CYBLE_GATT_DB_LOCALLY_INITIATED))
    {
        CyBle_GattsWriteAttributeValue(&tempHandle, 0, &cyBle_connHandle, 0); //Writing new value to Gatt Server
    }
}