/*
 * CanSendManager.cpp
 *
 *  Created on: 26.03.2020
 *      Author: Igor
 */

#include "CanSendManager.h"

CanSendManager canSendManager;

void CanSendManager::sendMsg(SEND_MODE mode, uint8_t * msgData){


	if (mode == TURN ){
		hal_can_send( VELOCITY_FRAME_ID, STEERING_FRAME_LENGTH ,msgData);
	}
	else if (mode == VELOCITY) {
		hal_can_send( TURN_FRAME_ID,  STEERING_FRAME_LENGTH , msgData);
	}
	else if (mode == STATUS ){
		hal_can_send( STATUS_FRAME_ID,  STATUS_FRAME_LENGTH ,msgData);
	}

}

uint8_t CanSendManager::getSign(float value){
	if (value >=0) return POSITIVE_SIGN;
	else return NEGATIVE_SIGN;
}

uint16_t CanSendManager::convertFloatToUint16t(float value){
	float range = 128;
	if( value > range){
		return range;
	}
	return(uint16_t)(value * pow(2, 16) /range);
}
uint8_t * CanSendManager::convertToFrame(uint8_t sign, uint16_t value){
	uint8_t data_to_encode[]={
			(uint8_t)(sign >> 8),
			(uint8_t) sign,
			(uint8_t)(value >> 8 ),
			(uint8_t) value,
	};

	return encode_frame_big_endian(data_to_encode,STEERING_FRAME_LENGTH);


}

uint8_t* CanSendManager::encode_frame_big_endian(uint8_t* data , uint8_t data_length){
	 uint8_t* encoded_data = (uint8_t*)calloc(data_length, sizeof(uint8_t));
	 if (encoded_data != NULL){
		for( uint8_t i = 1 ; i <= data_length  ;i++){
			encoded_data[i-1] = data[data_length-i];
		}
	 }
	return encoded_data;
}


void CanSendManager::process(float maxvalue, float value,SEND_MODE mode){
	uint8_t sign = getSign(value) ;
	if (sign == NEGATIVE_SIGN){ value *= -1; } //Change sign to positive after check
	uint16_t convertedData = convertFloatToUint16t(value);
	uint8_t * frameData = convertToFrame(sign, convertedData);
	sendMsg(mode, frameData );
	free(frameData);
}

void CanSendManager::setVelocity(float maxVel,float vel){
	process(maxVel, vel, VELOCITY);
}

void CanSendManager::setTurn(float maxAngle, float angle){
	process(maxAngle, angle, TURN);
}
void CanSendManager::setStatus(ModeManager::RC_MODE RCmode, ModeManager::DRIVE_MODE drive_mode){
	uint8_t RCstatus, driveStatus;
	if 		(RCmode == ModeManager::DISARMED)  		 RCstatus =  JOYSTICK_MODE_MSG;
	else if (RCmode == ModeManager::MODE_ACRO) 		 RCstatus =  ACRO_MODE_MSG;
	else if (RCmode == ModeManager::MODE_SEMI) 		 RCstatus =  SEMI_MODE_MSG;
	else if (RCmode == ModeManager::MODE_AUTONOMOUS) RCstatus =  AUTONOMOUS_MODE_MSG;

	if 		(drive_mode == ModeManager::ENABLE)  	 driveStatus =  ENABLE_DRIVE_MSG;
	else if (drive_mode == ModeManager::DISABLE)     driveStatus =  DISABLE_DRIVE_MSG;

	uint8_t data_to_encode[]={
			(uint8_t) NULL,
			(uint8_t) RCstatus,
			(uint8_t) NULL,
			(uint8_t) driveStatus };
	uint8_t * msgData = encode_frame_big_endian(data_to_encode,STEERING_FRAME_LENGTH);
	sendMsg(STATUS, msgData);

}

CanSendManager::CanSendManager() {
	// TODO Auto-generated constructor stub

}

CanSendManager::~CanSendManager() {
	// TODO Auto-generated destructor stub
}

