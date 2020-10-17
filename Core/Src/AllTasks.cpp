/*
 * AllTasks.cpp
 *
 *  Created on: 16.03.2020
 *      Author: Igor
 */

#include <AllTasks.h>


AllTasks allTasks;

AllTasks::AllTasks() {
	// TODO Auto-generated constructor stub

}

void AllTasks::init(void){
//	init_latt_driver();
	tools.Init();
	futaba.Init();
	mode_manager.init();
	motor_manager.init();

}

void AllTasks::process(void){
	//futaba.Process();
	mode_manager.proccess();
	motor_manager.process();

}

AllTasks::~AllTasks() {
	// TODO Auto-generated destructor stub
}

