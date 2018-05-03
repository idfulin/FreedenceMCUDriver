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
#ifndef __GPIO_API_H__
#define __GPIO_API_H__

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "PinTypes.h"

/* Exported types ------------------------------------------------------------*/
/*
 * Note: reg_clr might actually be same as reg_set.
 * Depends on family whether BRR is available on top of BSRR
 * if BRR does not exist, family shall define GPIO_IP_WITHOUT_BRR
 */
typedef struct {
    uint32_t ulMask;
//    __IO uint32_t *reg_in;
//    __IO uint32_t *reg_set;
//    __IO uint32_t *reg_clr;
    volatile uint32_t *pulRegIn;
    volatile uint32_t *pulRegSet;
    volatile uint32_t *pulRegClr;
    PinName  xPinName;    
//    GPIO_TypeDef *gpio;
    void     *pvGpio;
    uint32_t ulLLPin;
} Gpio_t;

typedef enum {
    GPIO_PIN_STA_RESET = 0,
    GPIO_PIN_STA_SET,
}GpioPinSta;

typedef PinName      GpioPin_t;
typedef PinDirection GpioDir_t;
typedef PinMode      GpioMode_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void GpioInit(Gpio_t *pxGpio, GpioPin_t xName, GpioDir_t xDir, GpioMode_t xMode);
void GpioDeInit(Gpio_t *pxGpio);

void GpioSetMode(Gpio_t *pxGpio, GpioMode_t xMode);
void GpioSetDir(Gpio_t *pxGpio, GpioDir_t xDir);

void GpioWrite(Gpio_t *pxGpio, GpioPinSta xSta);
void GpioToggle(Gpio_t *pxGpio);
GpioPinSta GpioRead(Gpio_t *pxGpio);

#endif //__GPIO_API_H__
