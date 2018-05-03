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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/********************     Form mbed gpio_api.c    *****************************/

// Enable GPIO clock and return GPIO base address
GPIO_TypeDef *SetPortClock(uint32_t ulPortIdx) {
    uint32_t gpio_add = 0;
    switch (ulPortIdx) {
        case PORT_A:
            gpio_add = GPIOA_BASE;
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case PORT_B:
            gpio_add = GPIOB_BASE;
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
#if defined(GPIOC_BASE)
        case PORT_C:
            gpio_add = GPIOC_BASE;
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
#endif
#if defined GPIOD_BASE
        case PORT_D:
            gpio_add = GPIOD_BASE;
            __HAL_RCC_GPIOD_CLK_ENABLE();
            break;
#endif
#if defined GPIOE_BASE
        case PORT_E:
            gpio_add = GPIOE_BASE;
            __HAL_RCC_GPIOE_CLK_ENABLE();
            break;
#endif
#if defined GPIOF_BASE
        case PORT_F:
            gpio_add = GPIOF_BASE;
            __HAL_RCC_GPIOF_CLK_ENABLE();
            break;
#endif
#if defined GPIOG_BASE
        case PORT_G:
#if defined TARGET_STM32L4
            __HAL_RCC_PWR_CLK_ENABLE();
            HAL_PWREx_EnableVddIO2();
#endif
            gpio_add = GPIOG_BASE;
            __HAL_RCC_GPIOG_CLK_ENABLE();
            break;
#endif
#if defined GPIOH_BASE
        case PORT_H:
            gpio_add = GPIOH_BASE;
            __HAL_RCC_GPIOH_CLK_ENABLE();
            break;
#endif
#if defined GPIOI_BASE
        case PORT_I:
            gpio_add = GPIOI_BASE;
            __HAL_RCC_GPIOI_CLK_ENABLE();
            break;
#endif
#if defined GPIOJ_BASE
        case PORT_J:
            gpio_add = GPIOJ_BASE;
            __HAL_RCC_GPIOJ_CLK_ENABLE();
            break;
#endif
#if defined GPIOK_BASE
        case PORT_K:
            gpio_add = GPIOK_BASE;
            __HAL_RCC_GPIOK_CLK_ENABLE();
            break;
#endif
        default:
//            error("Pinmap error: wrong port number.");
            break;
    }
    return (GPIO_TypeDef *) gpio_add;
}

const uint32_t LLPinDefines[16] = {
    LL_GPIO_PIN_0,
    LL_GPIO_PIN_1,
    LL_GPIO_PIN_2,
    LL_GPIO_PIN_3,
    LL_GPIO_PIN_4,
    LL_GPIO_PIN_5,
    LL_GPIO_PIN_6,
    LL_GPIO_PIN_7,
    LL_GPIO_PIN_8,
    LL_GPIO_PIN_9,
    LL_GPIO_PIN_10,
    LL_GPIO_PIN_11,
    LL_GPIO_PIN_12,
    LL_GPIO_PIN_13,
    LL_GPIO_PIN_14,
    LL_GPIO_PIN_15
};

void PinSetFunction(PinName xName, uint32_t ulFun)
{
    if(xName != NC) {
        // Get the pin informations
        uint32_t mode  = STM_PIN_FUNCTION(ulFun);
        uint32_t afnum = STM_PIN_AFNUM(ulFun);
        uint32_t port  = STM_PORT(xName);
        uint32_t ll_pin  = LLPinDefines[STM_PIN(xName)];
        uint32_t ll_mode = 0;

        // Enable GPIO clock
        GPIO_TypeDef *gpio = SetPortClock(port);

        /*  Set default speed to high.
         *  For most families there are dedicated registers so it is
         *  not so important, register can be set at any time.
         *  But for families like F1, speed only applies to output.
         */
#if defined (TARGET_STM32F1)
        if (mode == STM_PIN_OUTPUT) {
#endif
            LL_GPIO_SetPinSpeed(gpio, ll_pin, LL_GPIO_SPEED_FREQ_HIGH);
#if defined (TARGET_STM32F1)
        }
#endif

        switch (mode) {
            case STM_PIN_INPUT:
                ll_mode = LL_GPIO_MODE_INPUT;
                break;
            case STM_PIN_OUTPUT:
                ll_mode = LL_GPIO_MODE_OUTPUT;
                break;
            case STM_PIN_ALTERNATE:
                ll_mode = LL_GPIO_MODE_ALTERNATE;
                // In case of ALT function, also set he afnum
               PinSetAFPin(gpio, xName, afnum);
                break;
            case STM_PIN_ANALOG:
                ll_mode = LL_GPIO_MODE_ANALOG;
                break;
            default:
//                MBED_ASSERT(0);
                break;
        }
        LL_GPIO_SetPinMode(gpio, ll_pin, ll_mode);

#if defined(GPIO_ASCR_ASC0)
        /*  For families where Analog Control ASC0 register is present */
        if (STM_PIN_ANALOG_CONTROL(data)) {
            LL_GPIO_EnablePinAnalogControl(gpio, ll_pin);
        } else {
            LL_GPIO_DisablePinAnalogControl(gpio, ll_pin);
        }
#endif

        /*  For now by default use Speed HIGH for output or alt modes */
        if ((mode == STM_PIN_OUTPUT) ||(mode == STM_PIN_ALTERNATE)) {
            if (STM_PIN_OD(ulFun)) {
                LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_OPENDRAIN);
            } else {
                LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_PUSHPULL);
            }
        }

        PinPullConfig(gpio, ll_pin, STM_PIN_PUPD(ulFun));

        PinDisconnectDebug(xName);
    }
}

void PinSetMode(PinName xName, PinMode xMode)
{
    if(xName != NC) {
        uint32_t port_index = STM_PORT(xName);
        uint32_t ll_pin  = LLPinDefines[STM_PIN(xName)];
        // Enable GPIO clock
        GPIO_TypeDef *gpio = SetPortClock(port_index);
        uint32_t function = LL_GPIO_GetPinMode(gpio, ll_pin);

        if ((function == LL_GPIO_MODE_OUTPUT) || (function == LL_GPIO_MODE_ALTERNATE))
        {
            if ((xMode == OpenDrainNoPull) || (xMode == OpenDrainPullUp) || (xMode == OpenDrainPullDown)) {
                LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_OPENDRAIN);
            } else {
                LL_GPIO_SetPinOutputType(gpio, ll_pin, LL_GPIO_OUTPUT_PUSHPULL);
            }
        }

        if ((xMode == OpenDrainPullUp) || (xMode == PullUp)) {
            PinPullConfig(gpio, ll_pin, GPIO_PULLUP);
        } else if ((xMode == OpenDrainPullDown) || (xMode == PullDown)) {
            PinPullConfig(gpio, ll_pin, GPIO_PULLDOWN);
        } else {
            PinPullConfig(gpio, ll_pin, GPIO_NOPULL);
        }
    }
}
