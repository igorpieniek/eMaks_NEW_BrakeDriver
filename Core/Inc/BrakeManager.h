/*
 * BrakeManager.h
 *
 *  Created on: 08.12.2020
 *      Author: Igor
 */

#ifndef INC_BRAKEMANAGER_H_
#define INC_BRAKEMANAGER_H_

#include "main.h"

#define DIR_UP_STATE 	GPIO_PIN_RESET
#define DIR_DOWN_STATE 	GPIO_PIN_SET

#define ENABLE_STATE 	GPIO_PIN_RESET
#define DISABLE_STATE 	GPIO_PIN_SET

#define IS_REVERSED_STATE 0 /** 0 - switch pin SET state mean flag was set
 	 	 	 	 	 	 	 	1 - switch pin SET state mean flag was reset*/

#define BRAKE_FRAME_ID 0x19D



class BrakeManager {
public:

	uint8_t isErrorFrameId(uint32_t frame);
	uint8_t isBrakeFrameId(uint32_t frame);
	uint8_t getFrameStatus(uint8_t* data);

	enum  Limit_switch_flag{
		SWITCH_RESET ,   	/**< flag down - normal state*/
		SWITCH_SET 			/**< flag raised - piston reached switch*/
	};
	enum  Limit_switch{LOW,HIGH};

	void init();

	void on();
	void off();
	void interrupt_update(); /**< update function to be called by EXTI interrupt*/


	BrakeManager();
	virtual ~BrakeManager();

private:
	enum Direction{ DOWN, UP};

	Limit_switch_flag min_flag;
	Limit_switch_flag max_flag;

	void stop();
	void move( Direction dir);
	void writePins(GPIO_PinState dir, GPIO_PinState enable );
	Limit_switch_flag getState(Limit_switch);
	void update_switch_flags();

};

extern BrakeManager brake_manager;
#endif /* INC_BRAKEMANAGER_H_ */
