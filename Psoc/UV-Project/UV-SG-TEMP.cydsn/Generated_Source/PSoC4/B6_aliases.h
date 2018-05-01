/*******************************************************************************
* File Name: B6.h  
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

#if !defined(CY_PINS_B6_ALIASES_H) /* Pins B6_ALIASES_H */
#define CY_PINS_B6_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define B6_0			(B6__0__PC)
#define B6_0_PS		(B6__0__PS)
#define B6_0_PC		(B6__0__PC)
#define B6_0_DR		(B6__0__DR)
#define B6_0_SHIFT	(B6__0__SHIFT)
#define B6_0_INTR	((uint16)((uint16)0x0003u << (B6__0__SHIFT*2u)))

#define B6_INTR_ALL	 ((uint16)(B6_0_INTR))


#endif /* End Pins B6_ALIASES_H */


/* [] END OF FILE */
