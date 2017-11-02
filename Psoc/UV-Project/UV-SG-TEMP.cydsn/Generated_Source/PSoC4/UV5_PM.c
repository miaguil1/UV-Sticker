/*******************************************************************************
* File Name: UV5_PM.c
* Version 1.20
*
* Description:
*  This file provides the power management source code to the API for the
*  Opamp (Analog Buffer) component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UV5.h"

#if(!UV5_CHECK_DEEPSLEEP_SUPPORT)
    static UV5_BACKUP_STRUCT UV5_backup =
    {
        0u, /* enableState */
    };
#endif /* (UV5_CHECK_DEEPSLEEP_SUPPORT) */


/*******************************************************************************
* Function Name: UV5_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UV5_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: UV5_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UV5_RestoreConfig(void)
{
    
}


/*******************************************************************************
* Function Name: UV5_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The Sleep() API 
*  saves the current component state. Call the Sleep() function before calling the 
*  CySysPmDeepSleep() or the CySysPmHibernate() functions. The "Deep sleep operation" 
*  option has an influence on this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  UV5_backup: The structure field 'enableState' is modified
*  depending on the enable state of the block before entering the sleep mode.
*
*******************************************************************************/
void UV5_Sleep(void)
{
#if(!UV5_CHECK_DEEPSLEEP_SUPPORT)
    if(UV5_CHECK_PWR_MODE_OFF)
    {
        UV5_backup.enableState = 1u;
        UV5_Stop();
    }
    else /* The component is disabled */
    {
        UV5_backup.enableState = 0u;
    }
#endif /* (UV5_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: UV5_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when Sleep() 
*  is called. If the component has been enabled before the Sleep() function is 
*  called, the Wakeup() function will also re-enable the component.
*  The "Deep sleep operation" option has an influence on this function
*  implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  UV5_backup: The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void UV5_Wakeup(void)
{
#if(!UV5_CHECK_DEEPSLEEP_SUPPORT)
    if(0u != UV5_backup.enableState)
    {
        /* Enable Opamp's operation */
        UV5_Enable();
    } /* Do nothing if Opamp was disabled before */
#endif /* (UV5_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */
