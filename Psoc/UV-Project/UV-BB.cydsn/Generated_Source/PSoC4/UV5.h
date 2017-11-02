/*******************************************************************************
* File Name: UV5.h
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


#if !defined(CY_OPAMP_UV5_H)
#define CY_OPAMP_UV5_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} UV5_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void UV5_Init(void);
void UV5_Enable(void);
void UV5_Start(void);
void UV5_Stop(void);
void UV5_SetPower(uint32 power);
void UV5_PumpControl(uint32 onOff);
void UV5_Sleep(void);
void UV5_Wakeup(void);
void UV5_SaveConfig(void);
void UV5_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define UV5_LOW_POWER      (1u)
#define UV5_MED_POWER      (2u)
#define UV5_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define UV5_PUMP_ON        (1u)
#define UV5_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define UV5_OUTPUT_CURRENT         (1u)
#define UV5_POWER                  (2u)
#define UV5_MODE                   (0u)
#define UV5_OA_COMP_TRIM_VALUE     (3u)
#define UV5_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  UV5_initVar;


/**************************************
*             Registers
**************************************/

#ifdef CYIPBLOCK_m0s8pass4b_VERSION
    #define UV5_CTB_CTRL_REG       (*(reg32 *) UV5_cy_psoc4_abuf__CTB_CTB_CTRL)
    #define UV5_CTB_CTRL_PTR       ( (reg32 *) UV5_cy_psoc4_abuf__CTB_CTB_CTRL)
#else
    #define UV5_CTB_CTRL_REG       (*(reg32 *) UV5_cy_psoc4_abuf__CTBM_CTB_CTRL)
    #define UV5_CTB_CTRL_PTR       ( (reg32 *) UV5_cy_psoc4_abuf__CTBM_CTB_CTRL)
#endif /* CYIPBLOCK_m0s8pass4b_VERSION */

#define UV5_OA_RES_CTRL_REG    (*(reg32 *) UV5_cy_psoc4_abuf__OA_RES_CTRL)
#define UV5_OA_RES_CTRL_PTR    ( (reg32 *) UV5_cy_psoc4_abuf__OA_RES_CTRL)
#define UV5_OA_COMP_TRIM_REG   (*(reg32 *) UV5_cy_psoc4_abuf__OA_COMP_TRIM)
#define UV5_OA_COMP_TRIM_PTR   ( (reg32 *) UV5_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* UV5_CTB_CTRL_REG */
#define UV5_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define UV5_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define UV5_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << UV5_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define UV5_CTB_CTRL_ENABLED               ((uint32) 0x01u << UV5_CTB_CTRL_ENABLED_SHIFT)


/* UV5_OA_RES_CTRL_REG */
#define UV5_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define UV5_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define UV5_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define UV5_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define UV5_OA_PWR_MODE                ((uint32) 0x02u << UV5_OA_PWR_MODE_SHIFT)
#define UV5_OA_PWR_MODE_MASK           ((uint32) 0x03u << UV5_OA_PWR_MODE_SHIFT)
#define UV5_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << UV5_OA_DRIVE_STR_SEL_SHIFT)
#define UV5_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << UV5_OA_DRIVE_STR_SEL_SHIFT)
#define UV5_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << UV5_OA_DRIVE_STR_SEL_SHIFT)
#define UV5_OA_COMP_EN                 ((uint32) 0x00u << UV5_OA_COMP_EN_SHIFT)
#define UV5_OA_PUMP_EN                 ((uint32) 0x01u << UV5_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define UV5_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (UV5_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define UV5_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (UV5_OA_DRIVE_STR_SEL_10X) : \
                                                                             (UV5_OA_DRIVE_STR_SEL_1X))
#define UV5_GET_OA_PWR_MODE(mode)          ((mode) & UV5_OA_PWR_MODE_MASK)
#define UV5_CHECK_PWR_MODE_OFF             (0u != (UV5_OA_RES_CTRL_REG & \
                                                                UV5_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define UV5_CHECK_DEEPSLEEP_SUPPORT        (0u != UV5_DEEPSLEEP_SUPPORT) 

#define UV5_DEFAULT_CTB_CTRL (UV5_GET_DEEPSLEEP_ON(UV5_DEEPSLEEP_SUPPORT) | \
                                           UV5_CTB_CTRL_ENABLED)

#define UV5_DEFAULT_OA_RES_CTRL (UV5_OA_COMP_EN | \
                                              UV5_GET_OA_DRIVE_STR(UV5_OUTPUT_CURRENT))

#define UV5_DEFAULT_OA_COMP_TRIM_REG (UV5_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define UV5_LOWPOWER                   (UV5_LOW_POWER)
#define UV5_MEDPOWER                   (UV5_MED_POWER)
#define UV5_HIGHPOWER                  (UV5_HIGH_POWER)

/* PUMP ON/OFF defines */
#define UV5_PUMPON                     (UV5_PUMP_ON)
#define UV5_PUMPOFF                    (UV5_PUMP_OFF)

#define UV5_OA_CTRL                    (UV5_CTB_CTRL_REG)
#define UV5_OA_RES_CTRL                (UV5_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define UV5_OA_CTB_EN_SHIFT            (UV5_CTB_CTRL_ENABLED_SHIFT)
#define UV5_OA_PUMP_CTRL_SHIFT         (UV5_OA_PUMP_EN_SHIFT)
#define UV5_OA_PUMP_EN_MASK            (0x800u)
#define UV5_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_UV5_H */


/* [] END OF FILE */
