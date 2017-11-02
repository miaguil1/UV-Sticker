/*******************************************************************************
* File Name: A_GND_REF.h  
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

#if !defined(CY_PINS_A_GND_REF_H) /* Pins A_GND_REF_H */
#define CY_PINS_A_GND_REF_H

#include "cytypes.h"
#include "cyfitter.h"
#include "A_GND_REF_aliases.h"


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
} A_GND_REF_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   A_GND_REF_Read(void);
void    A_GND_REF_Write(uint8 value);
uint8   A_GND_REF_ReadDataReg(void);
#if defined(A_GND_REF__PC) || (CY_PSOC4_4200L) 
    void    A_GND_REF_SetDriveMode(uint8 mode);
#endif
void    A_GND_REF_SetInterruptMode(uint16 position, uint16 mode);
uint8   A_GND_REF_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void A_GND_REF_Sleep(void); 
void A_GND_REF_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(A_GND_REF__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define A_GND_REF_DRIVE_MODE_BITS        (3)
    #define A_GND_REF_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - A_GND_REF_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the A_GND_REF_SetDriveMode() function.
         *  @{
         */
        #define A_GND_REF_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define A_GND_REF_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define A_GND_REF_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define A_GND_REF_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define A_GND_REF_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define A_GND_REF_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define A_GND_REF_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define A_GND_REF_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define A_GND_REF_MASK               A_GND_REF__MASK
#define A_GND_REF_SHIFT              A_GND_REF__SHIFT
#define A_GND_REF_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in A_GND_REF_SetInterruptMode() function.
     *  @{
     */
        #define A_GND_REF_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define A_GND_REF_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define A_GND_REF_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define A_GND_REF_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(A_GND_REF__SIO)
    #define A_GND_REF_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(A_GND_REF__PC) && (CY_PSOC4_4200L)
    #define A_GND_REF_USBIO_ENABLE               ((uint32)0x80000000u)
    #define A_GND_REF_USBIO_DISABLE              ((uint32)(~A_GND_REF_USBIO_ENABLE))
    #define A_GND_REF_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define A_GND_REF_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define A_GND_REF_USBIO_ENTER_SLEEP          ((uint32)((1u << A_GND_REF_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << A_GND_REF_USBIO_SUSPEND_DEL_SHIFT)))
    #define A_GND_REF_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << A_GND_REF_USBIO_SUSPEND_SHIFT)))
    #define A_GND_REF_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << A_GND_REF_USBIO_SUSPEND_DEL_SHIFT)))
    #define A_GND_REF_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(A_GND_REF__PC)
    /* Port Configuration */
    #define A_GND_REF_PC                 (* (reg32 *) A_GND_REF__PC)
#endif
/* Pin State */
#define A_GND_REF_PS                     (* (reg32 *) A_GND_REF__PS)
/* Data Register */
#define A_GND_REF_DR                     (* (reg32 *) A_GND_REF__DR)
/* Input Buffer Disable Override */
#define A_GND_REF_INP_DIS                (* (reg32 *) A_GND_REF__PC2)

/* Interrupt configuration Registers */
#define A_GND_REF_INTCFG                 (* (reg32 *) A_GND_REF__INTCFG)
#define A_GND_REF_INTSTAT                (* (reg32 *) A_GND_REF__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define A_GND_REF_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(A_GND_REF__SIO)
    #define A_GND_REF_SIO_REG            (* (reg32 *) A_GND_REF__SIO)
#endif /* (A_GND_REF__SIO_CFG) */

/* USBIO registers */
#if !defined(A_GND_REF__PC) && (CY_PSOC4_4200L)
    #define A_GND_REF_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define A_GND_REF_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define A_GND_REF_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define A_GND_REF_DRIVE_MODE_SHIFT       (0x00u)
#define A_GND_REF_DRIVE_MODE_MASK        (0x07u << A_GND_REF_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins A_GND_REF_H */


/* [] END OF FILE */
