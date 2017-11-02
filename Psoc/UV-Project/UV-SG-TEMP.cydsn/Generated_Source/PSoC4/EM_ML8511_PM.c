/*******************************************************************************
* File Name: EM_ML8511.c  
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
#include "EM_ML8511.h"

static EM_ML8511_BACKUP_STRUCT  EM_ML8511_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: EM_ML8511_Sleep
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
*  \snippet EM_ML8511_SUT.c usage_EM_ML8511_Sleep_Wakeup
*******************************************************************************/
void EM_ML8511_Sleep(void)
{
    #if defined(EM_ML8511__PC)
        EM_ML8511_backup.pcState = EM_ML8511_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            EM_ML8511_backup.usbState = EM_ML8511_CR1_REG;
            EM_ML8511_USB_POWER_REG |= EM_ML8511_USBIO_ENTER_SLEEP;
            EM_ML8511_CR1_REG &= EM_ML8511_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(EM_ML8511__SIO)
        EM_ML8511_backup.sioState = EM_ML8511_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        EM_ML8511_SIO_REG &= (uint32)(~EM_ML8511_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: EM_ML8511_Wakeup
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
*  Refer to EM_ML8511_Sleep() for an example usage.
*******************************************************************************/
void EM_ML8511_Wakeup(void)
{
    #if defined(EM_ML8511__PC)
        EM_ML8511_PC = EM_ML8511_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            EM_ML8511_USB_POWER_REG &= EM_ML8511_USBIO_EXIT_SLEEP_PH1;
            EM_ML8511_CR1_REG = EM_ML8511_backup.usbState;
            EM_ML8511_USB_POWER_REG &= EM_ML8511_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(EM_ML8511__SIO)
        EM_ML8511_SIO_REG = EM_ML8511_backup.sioState;
    #endif
}


/* [] END OF FILE */
