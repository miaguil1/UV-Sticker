/*******************************************************************************
* File Name: LOW_BATT_ALERT.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LOW_BATT_ALERT_H) /* Pins LOW_BATT_ALERT_H */
#define CY_PINS_LOW_BATT_ALERT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LOW_BATT_ALERT_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} LOW_BATT_ALERT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   LOW_BATT_ALERT_Read(void);
void    LOW_BATT_ALERT_Write(uint8 value);
uint8   LOW_BATT_ALERT_ReadDataReg(void);
#if defined(LOW_BATT_ALERT__PC) || (CY_PSOC4_4200L) 
    void    LOW_BATT_ALERT_SetDriveMode(uint8 mode);
#endif
void    LOW_BATT_ALERT_SetInterruptMode(uint16 position, uint16 mode);
uint8   LOW_BATT_ALERT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void LOW_BATT_ALERT_Sleep(void); 
void LOW_BATT_ALERT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(LOW_BATT_ALERT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define LOW_BATT_ALERT_DRIVE_MODE_BITS        (3)
    #define LOW_BATT_ALERT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LOW_BATT_ALERT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the LOW_BATT_ALERT_SetDriveMode() function.
         *  @{
         */
        #define LOW_BATT_ALERT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define LOW_BATT_ALERT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define LOW_BATT_ALERT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define LOW_BATT_ALERT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define LOW_BATT_ALERT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define LOW_BATT_ALERT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define LOW_BATT_ALERT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define LOW_BATT_ALERT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define LOW_BATT_ALERT_MASK               LOW_BATT_ALERT__MASK
#define LOW_BATT_ALERT_SHIFT              LOW_BATT_ALERT__SHIFT
#define LOW_BATT_ALERT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LOW_BATT_ALERT_SetInterruptMode() function.
     *  @{
     */
        #define LOW_BATT_ALERT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define LOW_BATT_ALERT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define LOW_BATT_ALERT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define LOW_BATT_ALERT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(LOW_BATT_ALERT__SIO)
    #define LOW_BATT_ALERT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(LOW_BATT_ALERT__PC) && (CY_PSOC4_4200L)
    #define LOW_BATT_ALERT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define LOW_BATT_ALERT_USBIO_DISABLE              ((uint32)(~LOW_BATT_ALERT_USBIO_ENABLE))
    #define LOW_BATT_ALERT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define LOW_BATT_ALERT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define LOW_BATT_ALERT_USBIO_ENTER_SLEEP          ((uint32)((1u << LOW_BATT_ALERT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << LOW_BATT_ALERT_USBIO_SUSPEND_DEL_SHIFT)))
    #define LOW_BATT_ALERT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << LOW_BATT_ALERT_USBIO_SUSPEND_SHIFT)))
    #define LOW_BATT_ALERT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << LOW_BATT_ALERT_USBIO_SUSPEND_DEL_SHIFT)))
    #define LOW_BATT_ALERT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(LOW_BATT_ALERT__PC)
    /* Port Configuration */
    #define LOW_BATT_ALERT_PC                 (* (reg32 *) LOW_BATT_ALERT__PC)
#endif
/* Pin State */
#define LOW_BATT_ALERT_PS                     (* (reg32 *) LOW_BATT_ALERT__PS)
/* Data Register */
#define LOW_BATT_ALERT_DR                     (* (reg32 *) LOW_BATT_ALERT__DR)
/* Input Buffer Disable Override */
#define LOW_BATT_ALERT_INP_DIS                (* (reg32 *) LOW_BATT_ALERT__PC2)

/* Interrupt configuration Registers */
#define LOW_BATT_ALERT_INTCFG                 (* (reg32 *) LOW_BATT_ALERT__INTCFG)
#define LOW_BATT_ALERT_INTSTAT                (* (reg32 *) LOW_BATT_ALERT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define LOW_BATT_ALERT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(LOW_BATT_ALERT__SIO)
    #define LOW_BATT_ALERT_SIO_REG            (* (reg32 *) LOW_BATT_ALERT__SIO)
#endif /* (LOW_BATT_ALERT__SIO_CFG) */

/* USBIO registers */
#if !defined(LOW_BATT_ALERT__PC) && (CY_PSOC4_4200L)
    #define LOW_BATT_ALERT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define LOW_BATT_ALERT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define LOW_BATT_ALERT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define LOW_BATT_ALERT_DRIVE_MODE_SHIFT       (0x00u)
#define LOW_BATT_ALERT_DRIVE_MODE_MASK        (0x07u << LOW_BATT_ALERT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins LOW_BATT_ALERT_H */


/* [] END OF FILE */
