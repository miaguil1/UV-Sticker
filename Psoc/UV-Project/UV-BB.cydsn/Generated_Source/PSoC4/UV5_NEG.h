/*******************************************************************************
* File Name: UV5_NEG.h  
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

#if !defined(CY_PINS_UV5_NEG_H) /* Pins UV5_NEG_H */
#define CY_PINS_UV5_NEG_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UV5_NEG_aliases.h"


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
} UV5_NEG_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   UV5_NEG_Read(void);
void    UV5_NEG_Write(uint8 value);
uint8   UV5_NEG_ReadDataReg(void);
#if defined(UV5_NEG__PC) || (CY_PSOC4_4200L) 
    void    UV5_NEG_SetDriveMode(uint8 mode);
#endif
void    UV5_NEG_SetInterruptMode(uint16 position, uint16 mode);
uint8   UV5_NEG_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void UV5_NEG_Sleep(void); 
void UV5_NEG_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(UV5_NEG__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define UV5_NEG_DRIVE_MODE_BITS        (3)
    #define UV5_NEG_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UV5_NEG_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the UV5_NEG_SetDriveMode() function.
         *  @{
         */
        #define UV5_NEG_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define UV5_NEG_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define UV5_NEG_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define UV5_NEG_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define UV5_NEG_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define UV5_NEG_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define UV5_NEG_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define UV5_NEG_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define UV5_NEG_MASK               UV5_NEG__MASK
#define UV5_NEG_SHIFT              UV5_NEG__SHIFT
#define UV5_NEG_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in UV5_NEG_SetInterruptMode() function.
     *  @{
     */
        #define UV5_NEG_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define UV5_NEG_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define UV5_NEG_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define UV5_NEG_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(UV5_NEG__SIO)
    #define UV5_NEG_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(UV5_NEG__PC) && (CY_PSOC4_4200L)
    #define UV5_NEG_USBIO_ENABLE               ((uint32)0x80000000u)
    #define UV5_NEG_USBIO_DISABLE              ((uint32)(~UV5_NEG_USBIO_ENABLE))
    #define UV5_NEG_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define UV5_NEG_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define UV5_NEG_USBIO_ENTER_SLEEP          ((uint32)((1u << UV5_NEG_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << UV5_NEG_USBIO_SUSPEND_DEL_SHIFT)))
    #define UV5_NEG_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << UV5_NEG_USBIO_SUSPEND_SHIFT)))
    #define UV5_NEG_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << UV5_NEG_USBIO_SUSPEND_DEL_SHIFT)))
    #define UV5_NEG_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(UV5_NEG__PC)
    /* Port Configuration */
    #define UV5_NEG_PC                 (* (reg32 *) UV5_NEG__PC)
#endif
/* Pin State */
#define UV5_NEG_PS                     (* (reg32 *) UV5_NEG__PS)
/* Data Register */
#define UV5_NEG_DR                     (* (reg32 *) UV5_NEG__DR)
/* Input Buffer Disable Override */
#define UV5_NEG_INP_DIS                (* (reg32 *) UV5_NEG__PC2)

/* Interrupt configuration Registers */
#define UV5_NEG_INTCFG                 (* (reg32 *) UV5_NEG__INTCFG)
#define UV5_NEG_INTSTAT                (* (reg32 *) UV5_NEG__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define UV5_NEG_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(UV5_NEG__SIO)
    #define UV5_NEG_SIO_REG            (* (reg32 *) UV5_NEG__SIO)
#endif /* (UV5_NEG__SIO_CFG) */

/* USBIO registers */
#if !defined(UV5_NEG__PC) && (CY_PSOC4_4200L)
    #define UV5_NEG_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define UV5_NEG_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define UV5_NEG_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define UV5_NEG_DRIVE_MODE_SHIFT       (0x00u)
#define UV5_NEG_DRIVE_MODE_MASK        (0x07u << UV5_NEG_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins UV5_NEG_H */


/* [] END OF FILE */
