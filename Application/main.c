/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Board.h"

/** @addtogroup STM32F1xx_HAL_Examples
  * @{
  */

/** @addtogroup Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    BoardIOConfig_t  xIOCfg;
    BoardAppConfig_t xAppCfg;
    
    xIOCfg.xPinLed = PB_5;
    xAppCfg.ulLedDelay = 500;   //ms
    /* Include System Clock Configuration */

    /* Initializate system clock and all the peripherals on and out of the chip */
    BoardInit(&xIOCfg, &xAppCfg);
    
    /* The function that need circular execution of system */
    BoardLoop();

    /* Infinite loop */
    while (1)
    {
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/**
  * @}
  */

/**
  * @}
  */
