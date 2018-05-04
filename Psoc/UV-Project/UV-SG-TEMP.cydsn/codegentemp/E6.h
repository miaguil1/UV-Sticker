/*******************************************************************************
* File Name: E6.h  
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

#if !defined(CY_PINS_E6_H) /* Pins E6_H */
#define CY_PINS_E6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "E6_aliases.h"


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
} E6_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   E6_Read(void);
void    E6_Write(uint8 value);
uint8   E6_ReadDataReg(void);
#if defined(E6__PC) || (CY_PSOC4_4200L) 
    void    E6_SetDriveMode(uint8 mode);
#endif
void    E6_SetInterruptMode(uint16 position, uint16 mode);
uint8   E6_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void E6_Sleep(void); 
void E6_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(E6__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define E6_DRIVE_MODE_BITS        (3)
    #define E6_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - E6_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the E6_SetDriveMode() function.
         *  @{
         */
        #define E6_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define E6_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define E6_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define E6_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define E6_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define E6_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define E6_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define E6_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define E6_MASK               E6__MASK
#define E6_SHIFT              E6__SHIFT
#define E6_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in E6_SetInterruptMode() function.
     *  @{
     */
        #define E6_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define E6_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define E6_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define E6_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(E6__SIO)
    #define E6_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(E6__PC) && (CY_PSOC4_4200L)
    #define E6_USBIO_ENABLE               ((uint32)0x80000000u)
    #define E6_USBIO_DISABLE              ((uint32)(~E6_USBIO_ENABLE))
    #define E6_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define E6_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define E6_USBIO_ENTER_SLEEP          ((uint32)((1u << E6_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << E6_USBIO_SUSPEND_DEL_SHIFT)))
    #define E6_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << E6_USBIO_SUSPEND_SHIFT)))
    #define E6_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << E6_USBIO_SUSPEND_DEL_SHIFT)))
    #define E6_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(E6__PC)
    /* Port Configuration */
    #define E6_PC                 (* (reg32 *) E6__PC)
#endif
/* Pin State */
#define E6_PS                     (* (reg32 *) E6__PS)
/* Data Register */
#define E6_DR                     (* (reg32 *) E6__DR)
/* Input Buffer Disable Override */
#define E6_INP_DIS                (* (reg32 *) E6__PC2)

/* Interrupt configuration Registers */
#define E6_INTCFG                 (* (reg32 *) E6__INTCFG)
#define E6_INTSTAT                (* (reg32 *) E6__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define E6_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(E6__SIO)
    #define E6_SIO_REG            (* (reg32 *) E6__SIO)
#endif /* (E6__SIO_CFG) */

/* USBIO registers */
#if !defined(E6__PC) && (CY_PSOC4_4200L)
    #define E6_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define E6_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define E6_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define E6_DRIVE_MODE_SHIFT       (0x00u)
#define E6_DRIVE_MODE_MASK        (0x07u << E6_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins E6_H */


/* [] END OF FILE */
