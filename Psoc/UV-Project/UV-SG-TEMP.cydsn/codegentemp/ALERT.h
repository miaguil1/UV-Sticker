/*******************************************************************************
* File Name: ALERT.h  
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

#if !defined(CY_PINS_ALERT_H) /* Pins ALERT_H */
#define CY_PINS_ALERT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ALERT_aliases.h"


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
} ALERT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ALERT_Read(void);
void    ALERT_Write(uint8 value);
uint8   ALERT_ReadDataReg(void);
#if defined(ALERT__PC) || (CY_PSOC4_4200L) 
    void    ALERT_SetDriveMode(uint8 mode);
#endif
void    ALERT_SetInterruptMode(uint16 position, uint16 mode);
uint8   ALERT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ALERT_Sleep(void); 
void ALERT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ALERT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ALERT_DRIVE_MODE_BITS        (3)
    #define ALERT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ALERT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ALERT_SetDriveMode() function.
         *  @{
         */
        #define ALERT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ALERT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ALERT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ALERT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ALERT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ALERT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ALERT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ALERT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ALERT_MASK               ALERT__MASK
#define ALERT_SHIFT              ALERT__SHIFT
#define ALERT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ALERT_SetInterruptMode() function.
     *  @{
     */
        #define ALERT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ALERT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ALERT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ALERT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ALERT__SIO)
    #define ALERT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ALERT__PC) && (CY_PSOC4_4200L)
    #define ALERT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ALERT_USBIO_DISABLE              ((uint32)(~ALERT_USBIO_ENABLE))
    #define ALERT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ALERT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ALERT_USBIO_ENTER_SLEEP          ((uint32)((1u << ALERT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ALERT_USBIO_SUSPEND_DEL_SHIFT)))
    #define ALERT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ALERT_USBIO_SUSPEND_SHIFT)))
    #define ALERT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ALERT_USBIO_SUSPEND_DEL_SHIFT)))
    #define ALERT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ALERT__PC)
    /* Port Configuration */
    #define ALERT_PC                 (* (reg32 *) ALERT__PC)
#endif
/* Pin State */
#define ALERT_PS                     (* (reg32 *) ALERT__PS)
/* Data Register */
#define ALERT_DR                     (* (reg32 *) ALERT__DR)
/* Input Buffer Disable Override */
#define ALERT_INP_DIS                (* (reg32 *) ALERT__PC2)

/* Interrupt configuration Registers */
#define ALERT_INTCFG                 (* (reg32 *) ALERT__INTCFG)
#define ALERT_INTSTAT                (* (reg32 *) ALERT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ALERT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ALERT__SIO)
    #define ALERT_SIO_REG            (* (reg32 *) ALERT__SIO)
#endif /* (ALERT__SIO_CFG) */

/* USBIO registers */
#if !defined(ALERT__PC) && (CY_PSOC4_4200L)
    #define ALERT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ALERT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ALERT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ALERT_DRIVE_MODE_SHIFT       (0x00u)
#define ALERT_DRIVE_MODE_MASK        (0x07u << ALERT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ALERT_H */


/* [] END OF FILE */
