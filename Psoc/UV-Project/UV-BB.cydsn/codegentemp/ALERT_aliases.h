/*******************************************************************************
* File Name: ALERT.h  
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

#if !defined(CY_PINS_ALERT_ALIASES_H) /* Pins ALERT_ALIASES_H */
#define CY_PINS_ALERT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ALERT_0			(ALERT__0__PC)
#define ALERT_0_PS		(ALERT__0__PS)
#define ALERT_0_PC		(ALERT__0__PC)
#define ALERT_0_DR		(ALERT__0__DR)
#define ALERT_0_SHIFT	(ALERT__0__SHIFT)
#define ALERT_0_INTR	((uint16)((uint16)0x0003u << (ALERT__0__SHIFT*2u)))

#define ALERT_INTR_ALL	 ((uint16)(ALERT_0_INTR))


#endif /* End Pins ALERT_ALIASES_H */


/* [] END OF FILE */
