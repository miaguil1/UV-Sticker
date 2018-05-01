/*******************************************************************************
* File Name: C6.c  
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
#include "C6.h"

static C6_BACKUP_STRUCT  C6_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: C6_Sleep
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
*  \snippet C6_SUT.c usage_C6_Sleep_Wakeup
*******************************************************************************/
void C6_Sleep(void)
{
    #if defined(C6__PC)
        C6_backup.pcState = C6_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            C6_backup.usbState = C6_CR1_REG;
            C6_USB_POWER_REG |= C6_USBIO_ENTER_SLEEP;
            C6_CR1_REG &= C6_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(C6__SIO)
        C6_backup.sioState = C6_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        C6_SIO_REG &= (uint32)(~C6_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: C6_Wakeup
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
*  Refer to C6_Sleep() for an example usage.
*******************************************************************************/
void C6_Wakeup(void)
{
    #if defined(C6__PC)
        C6_PC = C6_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            C6_USB_POWER_REG &= C6_USBIO_EXIT_SLEEP_PH1;
            C6_CR1_REG = C6_backup.usbState;
            C6_USB_POWER_REG &= C6_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(C6__SIO)
        C6_SIO_REG = C6_backup.sioState;
    #endif
}


/* [] END OF FILE */
