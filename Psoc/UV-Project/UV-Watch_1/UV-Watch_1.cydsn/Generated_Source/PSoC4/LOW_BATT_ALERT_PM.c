/*******************************************************************************
* File Name: LOW_BATT_ALERT.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LOW_BATT_ALERT.h"

static LOW_BATT_ALERT_BACKUP_STRUCT  LOW_BATT_ALERT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: LOW_BATT_ALERT_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet LOW_BATT_ALERT_SUT.c usage_LOW_BATT_ALERT_Sleep_Wakeup
*******************************************************************************/
void LOW_BATT_ALERT_Sleep(void)
{
    #if defined(LOW_BATT_ALERT__PC)
        LOW_BATT_ALERT_backup.pcState = LOW_BATT_ALERT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            LOW_BATT_ALERT_backup.usbState = LOW_BATT_ALERT_CR1_REG;
            LOW_BATT_ALERT_USB_POWER_REG |= LOW_BATT_ALERT_USBIO_ENTER_SLEEP;
            LOW_BATT_ALERT_CR1_REG &= LOW_BATT_ALERT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LOW_BATT_ALERT__SIO)
        LOW_BATT_ALERT_backup.sioState = LOW_BATT_ALERT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        LOW_BATT_ALERT_SIO_REG &= (uint32)(~LOW_BATT_ALERT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: LOW_BATT_ALERT_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to LOW_BATT_ALERT_Sleep() for an example usage.
*******************************************************************************/
void LOW_BATT_ALERT_Wakeup(void)
{
    #if defined(LOW_BATT_ALERT__PC)
        LOW_BATT_ALERT_PC = LOW_BATT_ALERT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            LOW_BATT_ALERT_USB_POWER_REG &= LOW_BATT_ALERT_USBIO_EXIT_SLEEP_PH1;
            LOW_BATT_ALERT_CR1_REG = LOW_BATT_ALERT_backup.usbState;
            LOW_BATT_ALERT_USB_POWER_REG &= LOW_BATT_ALERT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LOW_BATT_ALERT__SIO)
        LOW_BATT_ALERT_SIO_REG = LOW_BATT_ALERT_backup.sioState;
    #endif
}


/* [] END OF FILE */
