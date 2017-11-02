/*******************************************************************************
* File Name: SG.c
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

#include "SG.h"

uint8 SG_initVar = 0u; /* Defines if component was initialized */
static uint32 SG_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: SG_Init
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
void SG_Init(void)
{
    SG_internalPower = SG_POWER;
    SG_CTB_CTRL_REG = SG_DEFAULT_CTB_CTRL;
    SG_OA_RES_CTRL_REG = SG_DEFAULT_OA_RES_CTRL;
    SG_OA_COMP_TRIM_REG = SG_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: SG_Enable
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
void SG_Enable(void)
{
    SG_OA_RES_CTRL_REG |= SG_internalPower | \
                                        SG_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: SG_Start
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
*  SG_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void SG_Start(void)
{
    if( 0u == SG_initVar)
    {
        SG_Init();
        SG_initVar = 1u;
    }
    SG_Enable();
}


/*******************************************************************************
* Function Name: SG_Stop
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
void SG_Stop(void)
{
    SG_OA_RES_CTRL_REG &= ((uint32)~(SG_OA_PWR_MODE_MASK | \
                                                   SG_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: SG_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   SG_LOW_POWER - Lowest active power
*   SG_MED_POWER - Medium power
*   SG_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void SG_SetPower(uint32 power)
{
    uint32 tmp;
    
    SG_internalPower = SG_GET_OA_PWR_MODE(power);
    tmp = SG_OA_RES_CTRL_REG & \
           (uint32)~SG_OA_PWR_MODE_MASK;
    SG_OA_RES_CTRL_REG = tmp | SG_internalPower;
}


/*******************************************************************************
* Function Name: SG_PumpControl
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
*   SG_PUMP_OFF - Turn off the pump
*   SG_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void SG_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        SG_OA_RES_CTRL |= SG_OA_PUMP_EN;    
    }
    else
    {
        SG_OA_RES_CTRL &= (uint32)~SG_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
