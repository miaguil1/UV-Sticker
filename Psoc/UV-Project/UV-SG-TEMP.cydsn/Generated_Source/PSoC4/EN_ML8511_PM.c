/*******************************************************************************
* File Name: EN_ML8511.c  
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
#include "EN_ML8511.h"

static EN_ML8511_BACKUP_STRUCT  EN_ML8511_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: EN_ML8511_Sleep
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
*  \snippet EN_ML8511_SUT.c usage_EN_ML8511_Sleep_Wakeup
*******************************************************************************/
void EN_ML8511_Sleep(void)
{
    #if defined(EN_ML8511__PC)
        EN_ML8511_backup.pcState = EN_ML8511_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            EN_ML8511_backup.usbState = EN_ML8511_CR1_REG;
            EN_ML8511_USB_POWER_REG |= EN_ML8511_USBIO_ENTER_SLEEP;
            EN_ML8511_CR1_REG &= EN_ML8511_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(EN_ML8511__SIO)
        EN_ML8511_backup.sioState = EN_ML8511_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        EN_ML8511_SIO_REG &= (uint32)(~EN_ML8511_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: EN_ML8511_Wakeup
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
*  Refer to EN_ML8511_Sleep() for an example usage.
*******************************************************************************/
void EN_ML8511_Wakeup(void)
{
    #if defined(EN_ML8511__PC)
        EN_ML8511_PC = EN_ML8511_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            EN_ML8511_USB_POWER_REG &= EN_ML8511_USBIO_EXIT_SLEEP_PH1;
            EN_ML8511_CR1_REG = EN_ML8511_backup.usbState;
            EN_ML8511_USB_POWER_REG &= EN_ML8511_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(EN_ML8511__SIO)
        EN_ML8511_SIO_REG = EN_ML8511_backup.sioState;
    #endif
}


/* [] END OF FILE */
