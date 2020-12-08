
#include "main.h"
#include "AllTasks.h"
#include "Futaba.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
  if (htim->Instance == TIM3) {
    allTasks.process();

  }
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART2) futaba.RxCallback();

}
