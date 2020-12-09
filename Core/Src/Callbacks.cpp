
#include "main.h"
#include "AllTasks.h"
#include "Futaba.h"
#include "gpio.h"
#include "BrakeManager.h"
#include "can.h"

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
	if(GPIO_Pin == LIMIT_SWITCH_LOW_Pin ||
	   GPIO_Pin == LIMIT_SWITCH_HIGH_Pin	){
		brake_manager.interrupt_update();
	}

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan ){
	hal_can_messageRx  rx;
	HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,
			&rx.header,
			rx.data );

	if(BrakeManager::isBrakeFrameId(rx.header.StdId) ||
	   BrakeManager::isErrorFrameId(rx.header.StdId)) {

		if (BrakeManager::getFrameStatus(&rx.data)){
			brake_manager.on();
		}
		else brake_manager.off();

	}


}
