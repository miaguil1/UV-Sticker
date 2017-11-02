/*******************************************************************************
* File Name: TMP116_ALERT.c  
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
#include "TMP116_ALERT.h"

static TMP116_ALERT_BACKUP_STRUCT  TMP116_ALERT_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: TMP116_ALERT_Sleep
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
*  \snippet TMP116_ALERT_SUT.c usage_TMP116_ALERT_Sleep_Wakeup
*******************************************************************************/
void TMP116_ALERT_Sleep(void)
{
    #if defined(TMP116_ALERT__PC)
        TMP116_ALERT_backup.pcState = TMP116_ALERT_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            TMP116_ALERT_backup.usbState = TMP116_ALERT_CR1_REG;
            TMP116_ALERT_USB_POWER_REG |= TMP116_ALERT_USBIO_ENTER_SLEEP;
            TMP116_ALERT_CR1_REG &= TMP116_ALERT_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TMP116_ALERT__SIO)
        TMP116_ALERT_backup.sioState = TMP116_ALERT_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        TMP116_ALERT_SIO_REG &= (uint32)(~TMP116_ALERT_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: TMP116_ALERT_Wakeup
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
*  Refer to TMP116_ALERT_Sleep() for an example usage.
*******************************************************************************/
void TMP116_ALERT_Wakeup(void)
{
    #if defined(TMP116_ALERT__PC)
        TMP116_ALERT_PC = TMP116_ALERT_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            TMP116_ALERT_USB_POWER_REG &= TMP116_ALERT_USBIO_EXIT_SLEEP_PH1;
            TMP116_ALERT_CR1_REG = TMP116_ALERT_backup.usbState;
            TMP116_ALERT_USB_POWER_REG &= TMP116_ALERT_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(TMP116_ALERT__SIO)
        TMP116_ALERT_SIO_REG = TMP116_ALERT_backup.sioState;
    #endif
}


/* [] END OF FILE */
