#include "toySoldierSpawnController.h"
#include "toySoldierFactoryWithRecycling.h"

#include "player.h"

#include "../Hummingbird Engine/CollisionSystem/Tools/Color.h"
#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"

toySoldierSpawnController::toySoldierSpawnController(player* inCot)
{
	currenttoySoldier = inCot;
	alarmable::submitAlarmableRegistration(3.0f, alarmableManager::ALARM_ID::ALARM1);
}


toySoldierSpawnController::~toySoldierSpawnController()
{
	if (checkForAlarm)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
	}
	else
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM1);
	}
	toySoldierFactoryWithRecycling::returnAllObjects();
	toySoldierFactoryWithRecycling::Terminate();
}

void toySoldierSpawnController::alarm0()
{
	toySoldierFactoryWithRecycling::haveAllOnScreenFacePlayer(currenttoySoldier->getPos());
	alarmable::submitAlarmableRegistration(2.0f, alarmableManager::ALARM_ID::ALARM1);
	checkForAlarm = false;
}

void toySoldierSpawnController::alarm1()
{
	int i = toySoldierFactoryWithRecycling::numberOnScreen();
	for (i; i < numberOfEnemies; i++)
	{
		toySoldierFactoryWithRecycling::CreatetoySoldier();
	}
	alarmable::submitAlarmableRegistration(5.0f, alarmableManager::ALARM_ID::ALARM0);
	checkForAlarm = true;
}
