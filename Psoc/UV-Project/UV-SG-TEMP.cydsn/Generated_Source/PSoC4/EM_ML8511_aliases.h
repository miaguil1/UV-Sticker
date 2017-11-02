/*******************************************************************************
* File Name: EM_ML8511.h  
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

#if !defined(CY_PINS_EM_ML8511_ALIASES_H) /* Pins EM_ML8511_ALIASES_H */
#define CY_PINS_EM_ML8511_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define EM_ML8511_0			(EM_ML8511__0__PC)
#define EM_ML8511_0_PS		(EM_ML8511__0__PS)
#define EM_ML8511_0_PC		(EM_ML8511__0__PC)
#define EM_ML8511_0_DR		(EM_ML8511__0__DR)
#define EM_ML8511_0_SHIFT	(EM_ML8511__0__SHIFT)
#define EM_ML8511_0_INTR	((uint16)((uint16)0x0003u << (EM_ML8511__0__SHIFT*2u)))

#define EM_ML8511_INTR_ALL	 ((uint16)(EM_ML8511_0_INTR))


#endif /* End Pins EM_ML8511_ALIASES_H */


/* [] END OF FILE */
