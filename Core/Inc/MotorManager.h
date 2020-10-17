/*
 * MotorManager.h
 *
 *  Created on: Jan 12, 2020
 *      Author: rvbc-
 */

#ifndef CLASSES_MOTOR_MOTORMANAGER_H_
#define CLASSES_MOTOR_MOTORMANAGER_H_

#include "main.h"

#include "ModeManager.h"
#include "futaba.h"
#include "CanSendManager.h"




#define SERVICE_MAX_VELOCITY 95.f

#define ACRO_MAX_VELOCITY 95.f
#define SEMI_MAX_VELOCITY 80.f
#define AUTONOMOUS_MAX_VELOCITY 80.f

#define MAX_TURN_ANGLE 45.f



class MotorManager {
public:
	void init();
	void process();
	MotorManager();
	virtual ~MotorManager();

private:
	ModeManager::DRIVE_MODE driveMode = ModeManager::DISABLE;
	float maxVelocity;
	void DriveModeCheck();
	void RCModeCheck();
	void setMaxVelocity();
	float getMaxVelocity();

};

extern MotorManager motor_manager;

#endif /* CLASSES_MOTOR_MOTORMANAGER_H_ */
