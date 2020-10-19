/*
 * CanSendManager.cpp
 *
 *  Created on: 26.03.2020
 *      Author: Igor
 */

#include "CanSendManager.h"

CanSendManager canSendManager;

void CanSendManager::init(){

	canMsgTx.header.RTR = CAN_RTR_DATA;
	canMsgTx.header.IDE  = CAN_ID_STD;
	canMsgTx.header.ExtId = 0x01;
	canMsgTx.header.TransmitGlobalTime = DISABLE;
	clearTxBuff();
}

void CanSendManager::clearTxBuff(){ for(uint8_t i = 0; i<8; i++) canMsgTx.data[i]=0;}


void CanSendManager::sendMsg(SEND_MODE mode){


	if (mode == TURN ){
		hal_can_send( VELOCITY_FRAME_ID, STEERING_FRAME_LENGTH );
	}
	else if (mode == VELOCITY) {
		hal_can_send( TURN_FRAME_ID,  STEERING_FRAME_LENGTH);
	}
	else if (mode == STATUS ){
		hal_can_send( STATUS_FRAME_ID,  STATUS_FRAME_LENGTH);
	}

	clearTxBuff();
}

uint8_t CanSendManager::getSign(float value){
	if (value >=0) return POSITIVE_SIGN;
	else return NEGATIVE_SIGN;
}

uint16_t CanSendManager::convertFloatToUint16t(float value){
	if( value > MAX_PERCANTAGE_VALUE){
		return (uint16_t)MAX_SENDVALUE;
	}
	return(uint16_t)((value * MAX_SENDVALUE)/MAX_PERCANTAGE_VALUE );
}
void CanSendManager::convertToFrame(uint8_t sign, uint16_t value){
	canMsgTx.data[0] = (uint8_t)(sign >> 8);
	canMsgTx.data[1] = (uint8_t) sign;
	canMsgTx.data[2] = (uint8_t)(value >> 8 );
	canMsgTx.data[3] = (uint8_t) value;
//	uint8_t data_to_encode[]={
//			(uint8_t)(sign >> 8),
//			(uint8_t) sign,
//			(uint8_t)(value >> 8 ),
//			(uint8_t) value,
//	};

	encode_frame_big_endian(STEERING_FRAME_LENGTH);


}

void CanSendManager::encode_frame_big_endian(uint8_t data_length){
	 //uint8_t* encoded_data = (uint8_t*)calloc(data_length, sizeof(uint8_t));
	 uint8_t* encoded_data = new uint8_t[data_length];
	 if (encoded_data != NULL){
		for( uint8_t i = 1 ; i <= data_length  ;i++){
			encoded_data[i-1] = canMsgTx.data[data_length-i];
		}
		for( uint8_t i = 0 ; i < data_length  ;i++) canMsgTx.data[i] = encoded_data[i];
	 }
	 delete[] encoded_data;
	 //free(encoded_data);

}


void CanSendManager::process(float maxvalue, float value,SEND_MODE mode){
	uint8_t sign = getSign(value) ;
	if (sign == NEGATIVE_SIGN){ value *= -1; } //Change sign to positive after check
	if (value > maxvalue) value = maxvalue;
	uint16_t convertedData = convertFloatToUint16t(value);
	//uint8_t * frameData = convertToFrame(sign, convertedData);
	canMsgTx.data[0] = (uint8_t)(sign >> 8);
	canMsgTx.data[1] = (uint8_t) sign;
	canMsgTx.data[2] = (uint8_t)(convertedData >> 8 );
	canMsgTx.data[3] = (uint8_t) (convertedData);

	encode_frame_big_endian(STEERING_FRAME_LENGTH);
	sendMsg(mode);
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

	canMsgTx.data[0] = 0;
	canMsgTx.data[1] = RCstatus;
	canMsgTx.data[2] = 0;
	canMsgTx.data[3] = driveStatus;
//	uint8_t data_to_encode[]={
//			(uint8_t) NULL,
//			(uint8_t) RCstatus,
//			(uint8_t) NULL,
//			(uint8_t) driveStatus };
	encode_frame_big_endian(STEERING_FRAME_LENGTH);
	sendMsg(STATUS);

}

void CanSendManager::hal_can_send(uint32_t frame_id, uint32_t dlc){

		canMsgTx.header.DLC = (uint32_t)dlc;
		canMsgTx.header.StdId = (uint32_t)frame_id;
		HAL_CAN_AddTxMessage(&hcan, &(canMsgTx.header),canMsgTx.data,&(canMsgTx.mailbox));


}
CanSendManager::CanSendManager() {
	// TODO Auto-generated constructor stub

}

CanSendManager::~CanSendManager() {
	// TODO Auto-generated destructor stub
}

