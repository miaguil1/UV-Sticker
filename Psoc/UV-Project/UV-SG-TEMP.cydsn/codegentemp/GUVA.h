/*******************************************************************************
* File Name: GUVA.h  
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

#if !defined(CY_PINS_GUVA_H) /* Pins GUVA_H */
#define CY_PINS_GUVA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GUVA_aliases.h"


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
} GUVA_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   GUVA_Read(void);
void    GUVA_Write(uint8 value);
uint8   GUVA_ReadDataReg(void);
#if defined(GUVA__PC) || (CY_PSOC4_4200L) 
    void    GUVA_SetDriveMode(uint8 mode);
#endif
void    GUVA_SetInterruptMode(uint16 position, uint16 mode);
uint8   GUVA_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void GUVA_Sleep(void); 
void GUVA_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(GUVA__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define GUVA_DRIVE_MODE_BITS        (3)
    #define GUVA_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GUVA_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the GUVA_SetDriveMode() function.
         *  @{
         */
        #define GUVA_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define GUVA_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define GUVA_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define GUVA_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define GUVA_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define GUVA_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define GUVA_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define GUVA_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define GUVA_MASK               GUVA__MASK
#define GUVA_SHIFT              GUVA__SHIFT
#define GUVA_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in GUVA_SetInterruptMode() function.
     *  @{
     */
        #define GUVA_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define GUVA_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define GUVA_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define GUVA_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(GUVA__SIO)
    #define GUVA_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(GUVA__PC) && (CY_PSOC4_4200L)
    #define GUVA_USBIO_ENABLE               ((uint32)0x80000000u)
    #define GUVA_USBIO_DISABLE              ((uint32)(~GUVA_USBIO_ENABLE))
    #define GUVA_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define GUVA_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define GUVA_USBIO_ENTER_SLEEP          ((uint32)((1u << GUVA_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << GUVA_USBIO_SUSPEND_DEL_SHIFT)))
    #define GUVA_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << GUVA_USBIO_SUSPEND_SHIFT)))
    #define GUVA_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << GUVA_USBIO_SUSPEND_DEL_SHIFT)))
    #define GUVA_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(GUVA__PC)
    /* Port Configuration */
    #define GUVA_PC                 (* (reg32 *) GUVA__PC)
#endif
/* Pin State */
#define GUVA_PS                     (* (reg32 *) GUVA__PS)
/* Data Register */
#define GUVA_DR                     (* (reg32 *) GUVA__DR)
/* Input Buffer Disable Override */
#define GUVA_INP_DIS                (* (reg32 *) GUVA__PC2)

/* Interrupt configuration Registers */
#define GUVA_INTCFG                 (* (reg32 *) GUVA__INTCFG)
#define GUVA_INTSTAT                (* (reg32 *) GUVA__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define GUVA_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(GUVA__SIO)
    #define GUVA_SIO_REG            (* (reg32 *) GUVA__SIO)
#endif /* (GUVA__SIO_CFG) */

/* USBIO registers */
#if !defined(GUVA__PC) && (CY_PSOC4_4200L)
    #define GUVA_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define GUVA_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define GUVA_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define GUVA_DRIVE_MODE_SHIFT       (0x00u)
#define GUVA_DRIVE_MODE_MASK        (0x07u << GUVA_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins GUVA_H */


/* [] END OF FILE */
