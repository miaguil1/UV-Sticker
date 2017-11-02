/*******************************************************************************
* File Name: VCC_Ref.h  
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

#if !defined(CY_PINS_VCC_Ref_ALIASES_H) /* Pins VCC_Ref_ALIASES_H */
#define CY_PINS_VCC_Ref_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define VCC_Ref_0			(VCC_Ref__0__PC)
#define VCC_Ref_0_PS		(VCC_Ref__0__PS)
#define VCC_Ref_0_PC		(VCC_Ref__0__PC)
#define VCC_Ref_0_DR		(VCC_Ref__0__DR)
#define VCC_Ref_0_SHIFT	(VCC_Ref__0__SHIFT)
#define VCC_Ref_0_INTR	((uint16)((uint16)0x0003u << (VCC_Ref__0__SHIFT*2u)))

#define VCC_Ref_INTR_ALL	 ((uint16)(VCC_Ref_0_INTR))


#endif /* End Pins VCC_Ref_ALIASES_H */


/* [] END OF FILE */
