/*******************************************************************************
* File Name: LOW_BATT_ALERT.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LOW_BATT_ALERT_ALIASES_H) /* Pins LOW_BATT_ALERT_ALIASES_H */
#define CY_PINS_LOW_BATT_ALERT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LOW_BATT_ALERT_0			(LOW_BATT_ALERT__0__PC)
#define LOW_BATT_ALERT_0_PS		(LOW_BATT_ALERT__0__PS)
#define LOW_BATT_ALERT_0_PC		(LOW_BATT_ALERT__0__PC)
#define LOW_BATT_ALERT_0_DR		(LOW_BATT_ALERT__0__DR)
#define LOW_BATT_ALERT_0_SHIFT	(LOW_BATT_ALERT__0__SHIFT)
#define LOW_BATT_ALERT_0_INTR	((uint16)((uint16)0x0003u << (LOW_BATT_ALERT__0__SHIFT*2u)))

#define LOW_BATT_ALERT_INTR_ALL	 ((uint16)(LOW_BATT_ALERT_0_INTR))


#endif /* End Pins LOW_BATT_ALERT_ALIASES_H */


/* [] END OF FILE */
