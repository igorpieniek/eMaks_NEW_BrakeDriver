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

	enum class Limit_switch_flag{
		RAISED, /**< flag raised - piston reached switch*/
		DOWN    /**< flag down - normal state*/
	};
	enum Limit_switch{LOW,HIGH};

	enum class Brake_state{
		ZERO, 		/**< piston in minimum position*/
		RELEASING, 	/**< piston is returning - releasing brake, temporary state*/
		BRAKING,	/**< piston is moving - braking process, temporary state */
		MAX			/**< piston in maximum position - full braking power */
	};

	void on();
	void off();


	BrakeManager();
	virtual ~BrakeManager();

private:
	Limit_switch_flag min_flag;
	Limit_switch_flag max_flag;
	Brake_state brake_state;

	void stop();

};

#endif /* INC_BRAKEMANAGER_H_ */
