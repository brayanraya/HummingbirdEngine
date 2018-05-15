#include "alarmable.h"
#include "../../Scene/scene.h"
#include "../../Scene/sceneManager.h"
#include "../alarmable/alarmableRegistratonCommand.h"
#include "../alarmable/alarmableDeregistratonCommand.h"
#include "../../../Time/Time Manager/timeManager.h"

alarmable::alarmable()
{
	for (int i = 0; i < alarmableManager::ALARM_NUMBER; i++)
	{
		RegData[i].pRegistrationCmd = new alarmableRegistratonCommand(this);
		RegData[i].pDeregistrationCmd = new alarmableDeregistratonCommand(this);
		RegData[i].currentState = registrationState::currently_deregistered;
	}
}

alarmable::~alarmable()
{
	for (int i = 0; i < alarmableManager::ALARM_NUMBER; i++)
	{
		delete RegData[i].pRegistrationCmd;
		delete RegData[i].pDeregistrationCmd;
	}
}

void alarmable::sceneDeregistraion(alarmableManager::ALARM_ID id)
{
	assert(this->RegData[int(id)].currentState == registrationState::pending_deregistration);
	sceneManager::getCurrentScene()->deregisterAlarmable(this,id);
	this->RegData[int(id)].currentState = registrationState::currently_deregistered;
}

void alarmable::sceneRegistraion(float time, alarmableManager::ALARM_ID id)
{
	assert(this->RegData[int(id)].currentState == registrationState::pending_registration);
	alarmableManager::AlarmEvent temp;
	temp.first = this;
	temp.second = id;
	sceneManager::getCurrentScene()->registerAlarmable(time, temp);
	this->RegData[int(id)].currentState = registrationState::currently_registered;
}

void alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID id)
{
	assert(this->RegData[int(id)].currentState == registrationState::currently_registered);
	this->RegData[int(id)].pDeregistrationCmd->alarmId = this->RegData[int(id)].pRegistrationCmd->alarmId;
	sceneManager::getCurrentScene()->submitCommand(this->RegData[int(id)].pDeregistrationCmd);
 	this->RegData[int(id)].currentState = registrationState::pending_deregistration;

}

void alarmable::submitAlarmableRegistration(float time, alarmableManager::ALARM_ID id)
{
	assert(this->RegData[int(id)].currentState == registrationState::currently_deregistered);
	this->RegData[int(id)].pRegistrationCmd->alarmTime = time + timeManager::getCurrentTime();
	this->RegData[int(id)].pRegistrationCmd->alarmId = id;
	sceneManager::getCurrentScene()->submitCommand(this->RegData[int(id)].pRegistrationCmd);
	this->RegData[int(id)].currentState = registrationState::pending_registration;

}

void alarmable::triggerAlarm(alarmableManager::ALARM_ID id)
{
	this->RegData[int(id)].currentState = registrationState::currently_deregistered;
	switch (id)
	{
	case alarmableManager::ALARM_ID::ALARM0:
		this->alarm0();
		break;
	case alarmableManager::ALARM_ID::ALARM1:
		this->alarm1();
		break;
	case alarmableManager::ALARM_ID::ALARM2:
		this->alarm2();
		break;	
	case alarmableManager::ALARM_ID::ALARM3:
		this->alarm3();
		break;
	}
}
