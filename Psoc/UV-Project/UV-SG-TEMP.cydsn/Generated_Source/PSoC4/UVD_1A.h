/*******************************************************************************
* File Name: UVD_1A.h  
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

#if !defined(CY_PINS_UVD_1A_H) /* Pins UVD_1A_H */
#define CY_PINS_UVD_1A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "UVD_1A_aliases.h"


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
} UVD_1A_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   UVD_1A_Read(void);
void    UVD_1A_Write(uint8 value);
uint8   UVD_1A_ReadDataReg(void);
#if defined(UVD_1A__PC) || (CY_PSOC4_4200L) 
    void    UVD_1A_SetDriveMode(uint8 mode);
#endif
void    UVD_1A_SetInterruptMode(uint16 position, uint16 mode);
uint8   UVD_1A_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void UVD_1A_Sleep(void); 
void UVD_1A_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(UVD_1A__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define UVD_1A_DRIVE_MODE_BITS        (3)
    #define UVD_1A_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - UVD_1A_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the UVD_1A_SetDriveMode() function.
         *  @{
         */
        #define UVD_1A_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define UVD_1A_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define UVD_1A_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define UVD_1A_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define UVD_1A_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define UVD_1A_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define UVD_1A_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define UVD_1A_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define UVD_1A_MASK               UVD_1A__MASK
#define UVD_1A_SHIFT              UVD_1A__SHIFT
#define UVD_1A_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in UVD_1A_SetInterruptMode() function.
     *  @{
     */
        #define UVD_1A_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define UVD_1A_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define UVD_1A_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define UVD_1A_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(UVD_1A__SIO)
    #define UVD_1A_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(UVD_1A__PC) && (CY_PSOC4_4200L)
    #define UVD_1A_USBIO_ENABLE               ((uint32)0x80000000u)
    #define UVD_1A_USBIO_DISABLE              ((uint32)(~UVD_1A_USBIO_ENABLE))
    #define UVD_1A_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define UVD_1A_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define UVD_1A_USBIO_ENTER_SLEEP          ((uint32)((1u << UVD_1A_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << UVD_1A_USBIO_SUSPEND_DEL_SHIFT)))
    #define UVD_1A_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << UVD_1A_USBIO_SUSPEND_SHIFT)))
    #define UVD_1A_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << UVD_1A_USBIO_SUSPEND_DEL_SHIFT)))
    #define UVD_1A_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(UVD_1A__PC)
    /* Port Configuration */
    #define UVD_1A_PC                 (* (reg32 *) UVD_1A__PC)
#endif
/* Pin State */
#define UVD_1A_PS                     (* (reg32 *) UVD_1A__PS)
/* Data Register */
#define UVD_1A_DR                     (* (reg32 *) UVD_1A__DR)
/* Input Buffer Disable Override */
#define UVD_1A_INP_DIS                (* (reg32 *) UVD_1A__PC2)

/* Interrupt configuration Registers */
#define UVD_1A_INTCFG                 (* (reg32 *) UVD_1A__INTCFG)
#define UVD_1A_INTSTAT                (* (reg32 *) UVD_1A__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define UVD_1A_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(UVD_1A__SIO)
    #define UVD_1A_SIO_REG            (* (reg32 *) UVD_1A__SIO)
#endif /* (UVD_1A__SIO_CFG) */

/* USBIO registers */
#if !defined(UVD_1A__PC) && (CY_PSOC4_4200L)
    #define UVD_1A_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define UVD_1A_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define UVD_1A_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define UVD_1A_DRIVE_MODE_SHIFT       (0x00u)
#define UVD_1A_DRIVE_MODE_MASK        (0x07u << UVD_1A_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins UVD_1A_H */


/* [] END OF FILE */
