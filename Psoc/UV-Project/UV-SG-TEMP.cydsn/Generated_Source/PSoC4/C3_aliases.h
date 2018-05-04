/*******************************************************************************
* File Name: C3.h  
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

#if !defined(CY_PINS_C3_ALIASES_H) /* Pins C3_ALIASES_H */
#define CY_PINS_C3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define C3_0			(C3__0__PC)
#define C3_0_PS		(C3__0__PS)
#define C3_0_PC		(C3__0__PC)
#define C3_0_DR		(C3__0__DR)
#define C3_0_SHIFT	(C3__0__SHIFT)
#define C3_0_INTR	((uint16)((uint16)0x0003u << (C3__0__SHIFT*2u)))

#define C3_INTR_ALL	 ((uint16)(C3_0_INTR))


#endif /* End Pins C3_ALIASES_H */


/* [] END OF FILE */
