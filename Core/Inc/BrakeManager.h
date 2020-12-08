/*
 * BrakeManager.h
 *
 *  Created on: 08.12.2020
 *      Author: Igor
 */

#ifndef INC_BRAKEMANAGER_H_
#define INC_BRAKEMANAGER_H_

#include "main.h"

#define DIR_UP_STATE 	GPIO_PIN_SET
#define DIR_DOWN_STATE 	GPIO_PIN_RESET

#define ENABLE_STATE 	GPIO_PIN_SET
#define DISABLE_STATE 	GPIO_PIN_RESET

class BrakeManager {
public:

	enum  Limit_switch_flag{
		RESET ,   /**< flag down - normal state*/
		SET /**< flag raised - piston reached switch*/
	};
	enum  Limit_switch{LOW,HIGH};


	void on();
	void off();
	void interrupt_update(); /**< update function to be called by EXTI interrupt*/


	BrakeManager();
	virtual ~BrakeManager();

private:
	enum Direction{ UP, DOWN};
	enum Enable_state{DISABLE, ENABLE};


	Limit_switch_flag min_flag;
	Limit_switch_flag max_flag;

	Enable_state en;
	Direction direction;

	void stop();
	void move( Direction dir);
	void writePins(GPIO_PinState dir, GPIO_PinState enable );
	Limit_switch_flag getState(Limit_switch);
	void update_piston_state();

};

extern BrakeManager brake_manager;
#endif /* INC_BRAKEMANAGER_H_ */
