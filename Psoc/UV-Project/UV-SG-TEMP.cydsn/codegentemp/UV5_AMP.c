/*******************************************************************************
* File Name: UV5_AMP.c
* Version 1.20
*
* Description:
*  This file provides the source code to the API for the Opamp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UV5_AMP.h"

uint8 UV5_AMP_initVar = 0u; /* Defines if component was initialized */
static uint32 UV5_AMP_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: UV5_AMP_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UV5_AMP_Init(void)
{
    UV5_AMP_internalPower = UV5_AMP_POWER;
    UV5_AMP_CTB_CTRL_REG = UV5_AMP_DEFAULT_CTB_CTRL;
    UV5_AMP_OA_RES_CTRL_REG = UV5_AMP_DEFAULT_OA_RES_CTRL;
    UV5_AMP_OA_COMP_TRIM_REG = UV5_AMP_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: UV5_AMP_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UV5_AMP_Enable(void)
{
    UV5_AMP_OA_RES_CTRL_REG |= UV5_AMP_internalPower | \
                                        UV5_AMP_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: UV5_AMP_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables power 
*  to the block. The first time the routine is executed, the Power level, Mode, 
*  and Output mode are set. When called to restart the Opamp following a Stop() call, 
*  the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  UV5_AMP_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void UV5_AMP_Start(void)
{
    if( 0u == UV5_AMP_initVar)
    {
        UV5_AMP_Init();
        UV5_AMP_initVar = 1u;
    }
    UV5_AMP_Enable();
}


/*******************************************************************************
* Function Name: UV5_AMP_Stop
********************************************************************************
*
* Summary:
*  Turn off the Opamp block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void UV5_AMP_Stop(void)
{
    UV5_AMP_OA_RES_CTRL_REG &= ((uint32)~(UV5_AMP_OA_PWR_MODE_MASK | \
                                                   UV5_AMP_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: UV5_AMP_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   UV5_AMP_LOW_POWER - Lowest active power
*   UV5_AMP_MED_POWER - Medium power
*   UV5_AMP_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void UV5_AMP_SetPower(uint32 power)
{
    uint32 tmp;
    
    UV5_AMP_internalPower = UV5_AMP_GET_OA_PWR_MODE(power);
    tmp = UV5_AMP_OA_RES_CTRL_REG & \
           (uint32)~UV5_AMP_OA_PWR_MODE_MASK;
    UV5_AMP_OA_RES_CTRL_REG = tmp | UV5_AMP_internalPower;
}


/*******************************************************************************
* Function Name: UV5_AMP_PumpControl
********************************************************************************
*
* Summary:
*  Allows the user to turn the Opamp's boost pump on or off. By Default the Start() 
*  function turns on the pump. Use this API to turn it off. The boost must be 
*  turned on when the supply is less than 2.7 volts and off if the supply is more 
*  than 4 volts.
*
* Parameters:
*  onOff: Control the pump.
*   UV5_AMP_PUMP_OFF - Turn off the pump
*   UV5_AMP_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void UV5_AMP_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        UV5_AMP_OA_RES_CTRL |= UV5_AMP_OA_PUMP_EN;    
    }
    else
    {
        UV5_AMP_OA_RES_CTRL &= (uint32)~UV5_AMP_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
