/*******************************************************************************
* File Name: E6.h  
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

#if !defined(CY_PINS_E6_ALIASES_H) /* Pins E6_ALIASES_H */
#define CY_PINS_E6_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define E6_0			(E6__0__PC)
#define E6_0_PS		(E6__0__PS)
#define E6_0_PC		(E6__0__PC)
#define E6_0_DR		(E6__0__DR)
#define E6_0_SHIFT	(E6__0__SHIFT)
#define E6_0_INTR	((uint16)((uint16)0x0003u << (E6__0__SHIFT*2u)))

#define E6_INTR_ALL	 ((uint16)(E6_0_INTR))


#endif /* End Pins E6_ALIASES_H */


/* [] END OF FILE */
