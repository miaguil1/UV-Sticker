/*******************************************************************************
* File Name: SG_AMP.h
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


#if !defined(CY_OPAMP_SG_AMP_H)
#define CY_OPAMP_SG_AMP_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} SG_AMP_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void SG_AMP_Init(void);
void SG_AMP_Enable(void);
void SG_AMP_Start(void);
void SG_AMP_Stop(void);
void SG_AMP_SetPower(uint32 power);
void SG_AMP_PumpControl(uint32 onOff);
void SG_AMP_Sleep(void);
void SG_AMP_Wakeup(void);
void SG_AMP_SaveConfig(void);
void SG_AMP_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define SG_AMP_LOW_POWER      (1u)
#define SG_AMP_MED_POWER      (2u)
#define SG_AMP_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define SG_AMP_PUMP_ON        (1u)
#define SG_AMP_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define SG_AMP_OUTPUT_CURRENT         (1u)
#define SG_AMP_POWER                  (3u)
#define SG_AMP_MODE                   (0u)
#define SG_AMP_OA_COMP_TRIM_VALUE     (3u)
#define SG_AMP_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  SG_AMP_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define SG_AMP_CTB_CTRL_REG       (*(reg32 *) SG_AMP_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define SG_AMP_CTB_CTRL_PTR       ( (reg32 *) SG_AMP_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define SG_AMP_CTB_CTRL_REG       (*(reg32 *) SG_AMP_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define SG_AMP_CTB_CTRL_PTR       ( (reg32 *) SG_AMP_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define SG_AMP_OA_RES_CTRL_REG    (*(reg32 *) SG_AMP_cy_psoc4_abuf__OA_RES_CTRL)
#define SG_AMP_OA_RES_CTRL_PTR    ( (reg32 *) SG_AMP_cy_psoc4_abuf__OA_RES_CTRL)
#define SG_AMP_OA_COMP_TRIM_REG   (*(reg32 *) SG_AMP_cy_psoc4_abuf__OA_COMP_TRIM)
#define SG_AMP_OA_COMP_TRIM_PTR   ( (reg32 *) SG_AMP_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* SG_AMP_CTB_CTRL_REG */
#define SG_AMP_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define SG_AMP_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define SG_AMP_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << SG_AMP_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define SG_AMP_CTB_CTRL_ENABLED               ((uint32) 0x01u << SG_AMP_CTB_CTRL_ENABLED_SHIFT)


/* SG_AMP_OA_RES_CTRL_REG */
#define SG_AMP_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define SG_AMP_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define SG_AMP_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define SG_AMP_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define SG_AMP_OA_PWR_MODE                ((uint32) 0x02u << SG_AMP_OA_PWR_MODE_SHIFT)
#define SG_AMP_OA_PWR_MODE_MASK           ((uint32) 0x03u << SG_AMP_OA_PWR_MODE_SHIFT)
#define SG_AMP_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << SG_AMP_OA_DRIVE_STR_SEL_SHIFT)
#define SG_AMP_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << SG_AMP_OA_DRIVE_STR_SEL_SHIFT)
#define SG_AMP_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << SG_AMP_OA_DRIVE_STR_SEL_SHIFT)
#define SG_AMP_OA_COMP_EN                 ((uint32) 0x00u << SG_AMP_OA_COMP_EN_SHIFT)
#define SG_AMP_OA_PUMP_EN                 ((uint32) 0x01u << SG_AMP_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define SG_AMP_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (SG_AMP_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define SG_AMP_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (SG_AMP_OA_DRIVE_STR_SEL_10X) : \
                                                                             (SG_AMP_OA_DRIVE_STR_SEL_1X))
#define SG_AMP_GET_OA_PWR_MODE(mode)          ((mode) & SG_AMP_OA_PWR_MODE_MASK)
#define SG_AMP_CHECK_PWR_MODE_OFF             (0u != (SG_AMP_OA_RES_CTRL_REG & \
                                                                SG_AMP_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define SG_AMP_CHECK_DEEPSLEEP_SUPPORT        (0u != SG_AMP_DEEPSLEEP_SUPPORT) 

#define SG_AMP_DEFAULT_CTB_CTRL (SG_AMP_GET_DEEPSLEEP_ON(SG_AMP_DEEPSLEEP_SUPPORT) | \
                                           SG_AMP_CTB_CTRL_ENABLED)

#define SG_AMP_DEFAULT_OA_RES_CTRL (SG_AMP_OA_COMP_EN | \
                                              SG_AMP_GET_OA_DRIVE_STR(SG_AMP_OUTPUT_CURRENT))

#define SG_AMP_DEFAULT_OA_COMP_TRIM_REG (SG_AMP_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define SG_AMP_LOWPOWER                   (SG_AMP_LOW_POWER)
#define SG_AMP_MEDPOWER                   (SG_AMP_MED_POWER)
#define SG_AMP_HIGHPOWER                  (SG_AMP_HIGH_POWER)

/* PUMP ON/OFF defines */
#define SG_AMP_PUMPON                     (SG_AMP_PUMP_ON)
#define SG_AMP_PUMPOFF                    (SG_AMP_PUMP_OFF)

#define SG_AMP_OA_CTRL                    (SG_AMP_CTB_CTRL_REG)
#define SG_AMP_OA_RES_CTRL                (SG_AMP_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define SG_AMP_OA_CTB_EN_SHIFT            (SG_AMP_CTB_CTRL_ENABLED_SHIFT)
#define SG_AMP_OA_PUMP_CTRL_SHIFT         (SG_AMP_OA_PUMP_EN_SHIFT)
#define SG_AMP_OA_PUMP_EN_MASK            (0x800u)
#define SG_AMP_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_SG_AMP_H */


/* [] END OF FILE */
