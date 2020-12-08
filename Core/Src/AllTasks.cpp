/*
 * AllTasks.cpp
 *
 *  Created on: 16.03.2020
 *      Author: Igor
 */

#include <AllTasks.h>


AllTasks allTasks;

AllTasks::AllTasks() {
	// TODO Auto-generated constructor stub

}

void AllTasks::init(void){
	  hal_can_filter_init();

	  HAL_CAN_Start(&hcan);
	  if (HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING) == HAL_OK){
		  //HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	  }

	  HAL_TIM_Base_Start_IT(&htim3);

	  tools.Init();
	  futaba.Init();
	  mode_manager.init();
	  motor_manager.init();
	  canSendManager.init();

}

void AllTasks::process(void){


	mode_manager.proccess();
	motor_manager.process();

}

AllTasks::~AllTasks() {
	// TODO Auto-generated destructor stub
}

