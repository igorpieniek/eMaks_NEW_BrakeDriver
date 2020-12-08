/*
 * BrakeManager.h
 *
 *  Created on: 08.12.2020
 *      Author: Igor
 */

#ifndef INC_BRAKEMANAGER_H_
#define INC_BRAKEMANAGER_H_

#include "main.h"


class BrakeManager {
public:

	enum  Limit_switch_flag{
		RESET ,   /**< flag down - normal state*/
		SET /**< flag raised - piston reached switch*/
	};
	enum  Limit_switch{LOW,HIGH};

	enum  Brake_state{
		ZERO, 		/**< piston in minimum position*/
		RELEASING, 	/**< piston is returning - releasing brake, temporary state*/
		BRAKING,	/**< piston is moving - braking process, temporary state */
		MAX			/**< piston in maximum position - full braking power */
	};

	void on();
	void off();
	void interrupt_update(Limit_switch sw); /**< update function to be called by EXTI interrupt*/


	BrakeManager();
	virtual ~BrakeManager();

private:
	enum Direction{ UP, DOWN};
	enum Enable{OFF, ON};

	Limit_switch_flag min_flag;
	Limit_switch_flag max_flag;
	Brake_state brake_state;

	void stop();
	Limit_switch_flag getState(Limit_switch);
	void update_piston_state();

};

#endif /* INC_BRAKEMANAGER_H_ */
