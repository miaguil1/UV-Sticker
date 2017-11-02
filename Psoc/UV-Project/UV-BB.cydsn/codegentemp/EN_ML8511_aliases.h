/*******************************************************************************
* File Name: EN_ML8511.h  
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

#if !defined(CY_PINS_EN_ML8511_ALIASES_H) /* Pins EN_ML8511_ALIASES_H */
#define CY_PINS_EN_ML8511_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define EN_ML8511_0			(EN_ML8511__0__PC)
#define EN_ML8511_0_PS		(EN_ML8511__0__PS)
#define EN_ML8511_0_PC		(EN_ML8511__0__PC)
#define EN_ML8511_0_DR		(EN_ML8511__0__DR)
#define EN_ML8511_0_SHIFT	(EN_ML8511__0__SHIFT)
#define EN_ML8511_0_INTR	((uint16)((uint16)0x0003u << (EN_ML8511__0__SHIFT*2u)))

#define EN_ML8511_INTR_ALL	 ((uint16)(EN_ML8511_0_INTR))


#endif /* End Pins EN_ML8511_ALIASES_H */


/* [] END OF FILE */
