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

/* Includes ------------------------------------------------------------------*/
#include "device.h"
#include "PinDevice.h"

extern GPIO_TypeDef *SetPortClock(uint32_t ulPortIdx);

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
static uint32_t GpioSet(PinName pin) {
    PinSetFunction(pin, STM_PIN_DATA(STM_MODE_OUTPUT_PP, GPIO_NOPULL, 0));

    return (uint32_t)(1 << ((uint32_t)pin & 0xF)); // Return the pin mask
}

static void GpioInitStruct(Gpio_t *pxGpio, GpioPin_t xName)
{
    if((xName != (PinName)NC) && (pxGpio != NULL)){
        pxGpio->xPinName = xName;
        uint32_t port_index = STM_PORT(xName);

        // Enable GPIO clock
        GPIO_TypeDef *gpio  = SetPortClock(port_index);
        // Fill GPIO object structure for future use
        pxGpio->ulMask      = GpioSet(xName);
        pxGpio->pvGpio      = gpio;
        pxGpio->ulLLPin     = LLPinDefines[STM_PIN(pxGpio->xPinName)];
        pxGpio->pulRegIn    = &gpio->IDR;
        pxGpio->pulRegSet   = &gpio->BSRR;
#ifdef GPIO_IP_WITHOUT_BRR
        pxGpio->pulRegClr   = &gpio->BSRR;
#else
        pxGpio->pulRegClr   = &gpio->BRR;
#endif
    }
}

void GpioInit(Gpio_t *pxGpio, GpioPin_t xName, GpioDir_t xDir, GpioMode_t xMode)
{
    if(xName != NC) {
        GpioInitStruct(pxGpio,xName);
        GpioSetDir(pxGpio,xDir);
        GpioSetMode(pxGpio,xMode);
    }
}

void GpioDeInit(Gpio_t *pxGpio)
{
    
}

void GpioSetMode(Gpio_t *pxGpio, GpioMode_t xMode)
{
    PinSetMode(pxGpio->xPinName,xMode);    
}

void GpioSetDir(Gpio_t *pxGpio, GpioDir_t xDir)
{
    if (xDir == PIN_INPUT) {
        LL_GPIO_SetPinMode(pxGpio->pvGpio, pxGpio->ulLLPin, LL_GPIO_MODE_INPUT);
    } else {
        LL_GPIO_SetPinMode(pxGpio->pvGpio, pxGpio->ulLLPin, LL_GPIO_MODE_OUTPUT);
    }
}

void GpioWrite(Gpio_t *pxGpio, GpioPinSta xSta)
{
    if(pxGpio != NULL) {
        if(xSta == GPIO_PIN_STA_RESET) {
#ifdef GPIO_IP_WITHOUT_BRR
            *pxGpio->pulRegClr = pxGpio->ulMask << 16;
#else
            *pxGpio->pulRegClr = pxGpio->ulMask;
#endif  //GPIO_IP_WITHOUT_BRR
        } else {
            *pxGpio->pulRegSet = pxGpio->ulMask;
        }
    }
}

void GpioToggle(Gpio_t *pxGpio)
{
    if(pxGpio != NULL) {
        GpioPinSta xSta = ((GpioRead(pxGpio) == GPIO_PIN_STA_RESET) ? GPIO_PIN_STA_SET : GPIO_PIN_STA_RESET);
        GpioWrite(pxGpio, xSta);
    }
}

GpioPinSta GpioRead(Gpio_t *pxGpio)
{
    GpioPinSta xSta = GPIO_PIN_STA_RESET;
    if(pxGpio != NULL) {
        xSta = ((*pxGpio->pulRegIn & pxGpio->ulMask) ? GPIO_PIN_STA_SET : GPIO_PIN_STA_RESET);
    }
    return xSta;
}
