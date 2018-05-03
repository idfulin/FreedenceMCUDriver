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
#ifndef __BOARD_H__
#define __BOARD_H__

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "PinTypes.h"

typedef struct structBoardIOConfig
{
    PinName xPinLed;
}BoardIOConfig_t;

typedef struct structBoardAppConfig
{
    uint32_t ulLedDelay;
}BoardAppConfig_t;

void BoardInit(BoardIOConfig_t *pxIOCfg, BoardAppConfig_t *pxAppCfg);
void BoardLoop(void);


#endif
