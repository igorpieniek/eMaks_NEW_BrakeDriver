/*
 * AllTasks.h
 *
 *  Created on: 16.03.2020
 *      Author: Igor
 */

#ifndef INC_ALLTASKS_H_
#define INC_ALLTASKS_H_

#include "main.h"
#include "ModeManager.h"
#include "MotorManager.h"
#include "futaba.h"
#include "Tools.h"
#include "tim.h"



class AllTasks {
public:
	AllTasks();
	void init(void);
	void process(void);

	virtual ~AllTasks();
};

extern AllTasks allTasks;

#endif /* INC_ALLTASKS_H_ */
