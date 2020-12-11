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
	//update limit switches state
	update_switch_flags();

	//Set to the initial position - min if both flag are in reset state
	if 	(min_flag == SWITCH_RESET && max_flag == SWITCH_RESET){
		move(DOWN); // back to ZERO state
	}
}

void BrakeManager::on(){
	update_switch_flags();
	if(max_flag == SWITCH_RESET) move(UP);
	else stop();
}

void BrakeManager::off(){
	update_switch_flags();
	if(min_flag == SWITCH_RESET) move(DOWN);
	else stop();
}

void BrakeManager::interrupt_update(){
	update_switch_flags();
	if (min_flag == SWITCH_SET || max_flag == SWITCH_SET) stop();
}

void BrakeManager::move(Direction dir){
	if 	   (dir == UP)	writePins(DIR_UP_STATE,		ENABLE_STATE);
	else if(dir==DOWN)	writePins(DIR_DOWN_STATE,	ENABLE_STATE);
}

void BrakeManager::stop(){
	writePins(DIR_UP_STATE, DISABLE_STATE);
}

void BrakeManager::writePins(GPIO_PinState dir, GPIO_PinState enable ){
	HAL_GPIO_WritePin(DIRECTION_GPIO_Port, DIRECTION_Pin, dir );
	HAL_GPIO_WritePin(ENABLE_GPIO_Port,    ENABLE_Pin,    enable );
}


void BrakeManager::update_switch_flags(){
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
		if(state == GPIO_PIN_RESET) return SWITCH_RESET; //TO REVERSE IF NEEDED
		else						return SWITCH_SET;
	}else{
		if(state == GPIO_PIN_RESET) return SWITCH_SET; //TO REVERSE IF NEEDED
		else						return SWITCH_RESET;
	}

}
