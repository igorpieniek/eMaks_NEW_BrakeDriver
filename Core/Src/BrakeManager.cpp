/*
 * BrakeManager.cpp
 *
 *  Created on: 08.12.2020
 *      Author: Igor
 */

#include <BrakeManager.h>

BrakeManager::BrakeManager() {
	//update current brake state - initial position of piston
	update_piston_state();
	//zeroing pins

}

BrakeManager::~BrakeManager() {
	// TODO Auto-generated destructor stub
}

void BrakeManager::update_piston_state(){
	min_flag = getState(LOW);
	max_flag = getState(HIGH);

	if 		(min_flag == SET && max_flag == RESET) brake_state = ZERO;
	else if	(min_flag == RESET && max_flag == SET) brake_state = MAX;
	else if 	(min_flag == RESET && max_flag == RESET){
		off(); // back to ZERO state
	}
	else stop(); //something wrong


}

void BrakeManager::stop(){


}


BrakeManager::Limit_switch_flag BrakeManager::getState(Limit_switch sw){
	GPIO_PinState state = GPIO_PIN_RESET;
	if (sw == LOW){
		state = HAL_GPIO_ReadPin(LIMIT_SWITCH_LOW_GPIO_Port, LIMIT_SWITCH_LOW_Pin);
	}
	else if(sw == HIGH){
		state = HAL_GPIO_ReadPin(LIMIT_SWITCH_HIGH_GPIO_Port, LIMIT_SWITCH_HIGH_Pin);
	}

	if(state == GPIO_PIN_RESET) return RESET;
	else						return SET;



}
