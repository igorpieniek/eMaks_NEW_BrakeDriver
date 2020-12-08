
#include "main.h"
#include "AllTasks.h"
#include "Futaba.h"
#include "gpio.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  if (htim->Instance == TIM3) {
    allTasks.process();

  }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2) futaba.RxCallback();

}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == LIMIT_SWITCH_LOW_Pin){
		//TODO
	}
	if(GPIO_Pin == LIMIT_SWITCH_HIGH_Pin){
		//TODO
	}


}
