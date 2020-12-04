/*
 * MotorManager.cpp
 *
 *  Created on: Jan 12, 2020
 *      Author: rvbc-
 */

#include <MotorManager.h>

MotorManager motor_manager;

void MotorManager::init(){
//	motor.SetPassthroughState(false);
	//motor.setMaxVelocity(3500.f);
	maxVelocity = ACRO_MAX_VELOCITY;
}

void MotorManager::process(){
	setMaxVelocity();
	DriveModeCheck();
	RCModeCheck();
}

void MotorManager::DriveModeCheck(){
		driveMode = mode_manager.getDriveMode();
}
void MotorManager::RCModeCheck(){
	switch(mode_manager.getRCmode()){

		case ModeManager::DISARMED:
			// TO TEST
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
//			canSendManager.setStatus(ModeManager::MODE_ACRO, driveMode);
//			canSendManager.setVelocity(getMaxVelocity(), getMaxVelocity() * futaba.SmoothDeflection[PITCH]);
//			canSendManager.setTurn(MAX_TURN_ANGLE , futaba.SmoothDeflection[YAW] * MAX_TURN_ANGLE) ;
			break;
		case ModeManager::MODE_ACRO:
//			control_brakes(getMaxVelocity() * futaba.SmoothDeflection[PITCH]);
//			setVelocity(getMaxVelocity() * futaba.SmoothDeflection[PITCH]);
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
			canSendManager.setStatus(ModeManager::MODE_ACRO, driveMode);
			canSendManager.setVelocity(getMaxVelocity(), 100.f * futaba.SmoothDeflection[PITCH]);
			canSendManager.setTurn(MAX_TURN_ANGLE ,      100.f * futaba.SmoothDeflection[YAW] ) ;
			break;
		case ModeManager::MODE_SEMI:
//			control_brakes(getMaxVelocity() * futaba.SmoothDeflection[PITCH]);
//			setVelocity(getMaxVelocity() * futaba.SmoothDeflection[PITCH]);
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
			canSendManager.setStatus(ModeManager::MODE_SEMI, driveMode);
			canSendManager.setVelocity(getMaxVelocity(), 100.f * futaba.SmoothDeflection[PITCH]);

			break;
		case ModeManager::MODE_AUTONOMOUS:
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
			canSendManager.setStatus(ModeManager::MODE_AUTONOMOUS, driveMode);
			break;
		}
}
void MotorManager::setMaxVelocity(){
	if(mode_manager.getRideMode() == ModeManager::COMPETITION){
		switch(mode_manager.getRCmode()){
		case ModeManager::DISARMED:
			break;
		case ModeManager::MODE_ACRO:
			maxVelocity = ACRO_MAX_VELOCITY;
			break;
		case ModeManager::MODE_SEMI:
			maxVelocity = SEMI_MAX_VELOCITY;
			break;
		case ModeManager::MODE_AUTONOMOUS:
			maxVelocity = AUTONOMOUS_MAX_VELOCITY;
			break;
		}
	}else{
		maxVelocity = SERVICE_MAX_VELOCITY;
	}
}

float MotorManager::getMaxVelocity(){
	return maxVelocity;
}
MotorManager::MotorManager() {
	// TODO Auto-generated constructor stub

}

MotorManager::~MotorManager() {
	// TODO Auto-generated destructor stub
}

