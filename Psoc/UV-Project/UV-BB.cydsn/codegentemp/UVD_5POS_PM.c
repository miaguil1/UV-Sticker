/*******************************************************************************
* File Name: UVD_5POS.c  
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
#include "UVD_5POS.h"

static UVD_5POS_BACKUP_STRUCT  UVD_5POS_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: UVD_5POS_Sleep
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
*  \snippet UVD_5POS_SUT.c usage_UVD_5POS_Sleep_Wakeup
*******************************************************************************/
void UVD_5POS_Sleep(void)
{
    #if defined(UVD_5POS__PC)
        UVD_5POS_backup.pcState = UVD_5POS_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            UVD_5POS_backup.usbState = UVD_5POS_CR1_REG;
            UVD_5POS_USB_POWER_REG |= UVD_5POS_USBIO_ENTER_SLEEP;
            UVD_5POS_CR1_REG &= UVD_5POS_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UVD_5POS__SIO)
        UVD_5POS_backup.sioState = UVD_5POS_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        UVD_5POS_SIO_REG &= (uint32)(~UVD_5POS_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: UVD_5POS_Wakeup
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
*  Refer to UVD_5POS_Sleep() for an example usage.
*******************************************************************************/
void UVD_5POS_Wakeup(void)
{
    #if defined(UVD_5POS__PC)
        UVD_5POS_PC = UVD_5POS_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            UVD_5POS_USB_POWER_REG &= UVD_5POS_USBIO_EXIT_SLEEP_PH1;
            UVD_5POS_CR1_REG = UVD_5POS_backup.usbState;
            UVD_5POS_USB_POWER_REG &= UVD_5POS_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(UVD_5POS__SIO)
        UVD_5POS_SIO_REG = UVD_5POS_backup.sioState;
    #endif
}


/* [] END OF FILE */
