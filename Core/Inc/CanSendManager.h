/*
 * CanSendManager.h
 *
 *  Created on: 26.03.2020
 *      Author: Igor
 */

#ifndef CAN_CANSENDMANAGER_H_
#define CAN_CANSENDMANAGER_H_

#include "ModeManager.h"
#include <malloc.h>
#include "can.h"

#define VELOCITY_FRAME_ID   0x23E //TODO
#define TURN_FRAME_ID  		0x24D  // SHOULD BE 0x24D
#define STATUS_FRAME_ID  	0x25D

#define JOYSTICK_MODE_MSG 	0x00
#define ACRO_MODE_MSG		0x01
#define SEMI_MODE_MSG		0x02
#define AUTONOMOUS_MODE_MSG 0x03

#define ENABLE_DRIVE_MSG  	0x01
#define DISABLE_DRIVE_MSG 	0x00

#define MAX_SENDVALUE 0xC800
#define POSITIVE_SIGN 1
#define NEGATIVE_SIGN 0
#define STEERING_FRAME_LENGTH 4
#define STATUS_FRAME_LENGTH 4

class CanSendManager {
private:


	enum SEND_MODE{
		TURN = 0,
		VELOCITY,
		STATUS
	};

	hal_can_messageTx canMsgTx;
	void clearTxBuff();

	void sendMsg(SEND_MODE mode);
	uint8_t getSign(float value);
	uint16_t convertFloatToUint16t(float value);
	void convertToFrame(uint8_t sign, uint16_t value);
	void encode_frame_big_endian( uint8_t data_length);
	void process(float maxvalue, float value,SEND_MODE mode);



public:
	void hal_can_send(uint32_t frame_id, uint32_t dlc);
	void init(void);
	void setVelocity(float maxVel,float vel);
	void setTurn(float maxAngle, float angle);
	void setStatus(ModeManager::RC_MODE, ModeManager::DRIVE_MODE);

	CanSendManager();
	virtual ~CanSendManager();
};

extern CanSendManager canSendManager;

#endif /* CAN_CANSENDMANAGER_H_ */
