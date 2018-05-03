/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  *          
  *          
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PIN_API_H__
#define __PIN_API_H__

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "PinTypes.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void PinSetFunction(PinName xName, uint32_t ulFun);
void PinSetMode(PinName xName, PinMode xMode);

#endif  //__PIN_API_H__
