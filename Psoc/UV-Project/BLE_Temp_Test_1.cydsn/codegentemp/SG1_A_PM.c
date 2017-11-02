/*******************************************************************************
* File Name: SG1_A.c  
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
#include "SG1_A.h"

static SG1_A_BACKUP_STRUCT  SG1_A_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: SG1_A_Sleep
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
*  \snippet SG1_A_SUT.c usage_SG1_A_Sleep_Wakeup
*******************************************************************************/
void SG1_A_Sleep(void)
{
    #if defined(SG1_A__PC)
        SG1_A_backup.pcState = SG1_A_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            SG1_A_backup.usbState = SG1_A_CR1_REG;
            SG1_A_USB_POWER_REG |= SG1_A_USBIO_ENTER_SLEEP;
            SG1_A_CR1_REG &= SG1_A_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SG1_A__SIO)
        SG1_A_backup.sioState = SG1_A_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        SG1_A_SIO_REG &= (uint32)(~SG1_A_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: SG1_A_Wakeup
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
*  Refer to SG1_A_Sleep() for an example usage.
*******************************************************************************/
void SG1_A_Wakeup(void)
{
    #if defined(SG1_A__PC)
        SG1_A_PC = SG1_A_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            SG1_A_USB_POWER_REG &= SG1_A_USBIO_EXIT_SLEEP_PH1;
            SG1_A_CR1_REG = SG1_A_backup.usbState;
            SG1_A_USB_POWER_REG &= SG1_A_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(SG1_A__SIO)
        SG1_A_SIO_REG = SG1_A_backup.sioState;
    #endif
}


/* [] END OF FILE */
