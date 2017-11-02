/*******************************************************************************
* File Name: SG.h
* Version 1.20
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Opamp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_SG_H)
#define CY_OPAMP_SG_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} SG_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void SG_Init(void);
void SG_Enable(void);
void SG_Start(void);
void SG_Stop(void);
void SG_SetPower(uint32 power);
void SG_PumpControl(uint32 onOff);
void SG_Sleep(void);
void SG_Wakeup(void);
void SG_SaveConfig(void);
void SG_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define SG_LOW_POWER      (1u)
#define SG_MED_POWER      (2u)
#define SG_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define SG_PUMP_ON        (1u)
#define SG_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define SG_OUTPUT_CURRENT         (1u)
#define SG_POWER                  (3u)
#define SG_MODE                   (0u)
#define SG_OA_COMP_TRIM_VALUE     (3u)
#define SG_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  SG_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define SG_CTB_CTRL_REG       (*(reg32 *) SG_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define SG_CTB_CTRL_PTR       ( (reg32 *) SG_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define SG_CTB_CTRL_REG       (*(reg32 *) SG_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define SG_CTB_CTRL_PTR       ( (reg32 *) SG_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define SG_OA_RES_CTRL_REG    (*(reg32 *) SG_cy_psoc4_abuf__OA_RES_CTRL)
#define SG_OA_RES_CTRL_PTR    ( (reg32 *) SG_cy_psoc4_abuf__OA_RES_CTRL)
#define SG_OA_COMP_TRIM_REG   (*(reg32 *) SG_cy_psoc4_abuf__OA_COMP_TRIM)
#define SG_OA_COMP_TRIM_PTR   ( (reg32 *) SG_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* SG_CTB_CTRL_REG */
#define SG_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define SG_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define SG_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << SG_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define SG_CTB_CTRL_ENABLED               ((uint32) 0x01u << SG_CTB_CTRL_ENABLED_SHIFT)


/* SG_OA_RES_CTRL_REG */
#define SG_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define SG_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define SG_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define SG_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define SG_OA_PWR_MODE                ((uint32) 0x02u << SG_OA_PWR_MODE_SHIFT)
#define SG_OA_PWR_MODE_MASK           ((uint32) 0x03u << SG_OA_PWR_MODE_SHIFT)
#define SG_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << SG_OA_DRIVE_STR_SEL_SHIFT)
#define SG_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << SG_OA_DRIVE_STR_SEL_SHIFT)
#define SG_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << SG_OA_DRIVE_STR_SEL_SHIFT)
#define SG_OA_COMP_EN                 ((uint32) 0x00u << SG_OA_COMP_EN_SHIFT)
#define SG_OA_PUMP_EN                 ((uint32) 0x01u << SG_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define SG_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (SG_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define SG_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (SG_OA_DRIVE_STR_SEL_10X) : \
                                                                             (SG_OA_DRIVE_STR_SEL_1X))
#define SG_GET_OA_PWR_MODE(mode)          ((mode) & SG_OA_PWR_MODE_MASK)
#define SG_CHECK_PWR_MODE_OFF             (0u != (SG_OA_RES_CTRL_REG & \
                                                                SG_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define SG_CHECK_DEEPSLEEP_SUPPORT        (0u != SG_DEEPSLEEP_SUPPORT) 

#define SG_DEFAULT_CTB_CTRL (SG_GET_DEEPSLEEP_ON(SG_DEEPSLEEP_SUPPORT) | \
                                           SG_CTB_CTRL_ENABLED)

#define SG_DEFAULT_OA_RES_CTRL (SG_OA_COMP_EN | \
                                              SG_GET_OA_DRIVE_STR(SG_OUTPUT_CURRENT))

#define SG_DEFAULT_OA_COMP_TRIM_REG (SG_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define SG_LOWPOWER                   (SG_LOW_POWER)
#define SG_MEDPOWER                   (SG_MED_POWER)
#define SG_HIGHPOWER                  (SG_HIGH_POWER)

/* PUMP ON/OFF defines */
#define SG_PUMPON                     (SG_PUMP_ON)
#define SG_PUMPOFF                    (SG_PUMP_OFF)

#define SG_OA_CTRL                    (SG_CTB_CTRL_REG)
#define SG_OA_RES_CTRL                (SG_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define SG_OA_CTB_EN_SHIFT            (SG_CTB_CTRL_ENABLED_SHIFT)
#define SG_OA_PUMP_CTRL_SHIFT         (SG_OA_PUMP_EN_SHIFT)
#define SG_OA_PUMP_EN_MASK            (0x800u)
#define SG_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_SG_H */


/* [] END OF FILE */
