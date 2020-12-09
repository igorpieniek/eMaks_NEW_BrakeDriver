/*
 * BrakeManager.cpp
 *
 *  Created on: 08.12.2020
 *      Author: Igor
 */

#include <BrakeManager.h>

BrakeManager brake_manager;

uint8_t BrakeManager::isErrorFrameId(uint32_t frame){
	uint32_t check_val = frame & 0xf ; //getting last 4 bits of frameID
	if(check_val == 0xe) return 1;
	else return 0;
}
uint8_t BrakeManager::isBrakeFrameId(uint32_t frame){
	if (frame == BRAKE_FRAME_ID) return 1;
	else return 0;
}
uint8_t BrakeManager::getFrameStatus(uint8_t* data){
	uint8_t sum =0;
	for(uint8_t i =0; i < 4; i++){sum += data[i];}

	if (sum == 1) return 1;
	else		  return 0;
}





BrakeManager::BrakeManager() {

}

BrakeManager::~BrakeManager() {
	// TODO Auto-generated destructor stub
}

void BrakeManager::init(){
	direction=DOWN;
	en = DISABLE;
	//update limit switches state
	update_piston_state();

	//Set to the initial position - min
	if 	(min_flag == RESET && max_flag == RESET){
		move(DOWN); // back to ZERO state
	}
}

void BrakeManager::on(){
	update_piston_state();
	if(max_flag == RESET) move(UP);
	else stop();
}

void BrakeManager::off(){
	update_piston_state();
	if(min_flag == RESET) move(DOWN);
	else stop();
}

void BrakeManager::interrupt_update(){
	update_piston_state();
	if (min_flag == SET || max_flag == SET) stop();
}

void BrakeManager::move(Direction dir){
	en = ENABLE;
	if (dir == UP){
		direction = UP;
		writePins(DIR_UP_STATE,ENABLE_STATE);
	}
	else if(dir==DOWN){
		direction = DOWN;
		writePins(DIR_DOWN_STATE,ENABLE_STATE);
	}
}

void BrakeManager::stop(){
	writePins(DIR_UP_STATE, DISABLE_STATE);
	en = DISABLE ;
}

void BrakeManager::writePins(GPIO_PinState dir, GPIO_PinState enable ){
	HAL_GPIO_WritePin(DIRECTION_GPIO_Port, DIRECTION_Pin, dir );
	HAL_GPIO_WritePin(ENABLE_GPIO_Port, ENABLE_Pin, enable );
}


void BrakeManager::update_piston_state(){
	min_flag = getState(LOW);
	max_flag = getState(HIGH);
}

BrakeManager::Limit_switch_flag BrakeManager::getState(Limit_switch sw){
	GPIO_PinState state;
	if (sw == LOW){
		state = HAL_GPIO_ReadPin(LIMIT_SWITCH_LOW_GPIO_Port, LIMIT_SWITCH_LOW_Pin);
	}
	else if(sw == HIGH){
		state = HAL_GPIO_ReadPin(LIMIT_SWITCH_HIGH_GPIO_Port, LIMIT_SWITCH_HIGH_Pin);
	}
	if(!IS_REVERSED_STATE){
		if(state == GPIO_PIN_RESET) return RESET; //TO REVERSE IF NEEDED
		else						return SET;
	}else{
		if(state == GPIO_PIN_RESET) return SET; //TO REVERSE IF NEEDED
		else						return RESET;
	}

}
