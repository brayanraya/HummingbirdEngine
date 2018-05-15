#include "cottageSpawnController.h"
#include "cottageFactoryWithRecycling.h"
#include "worldPlane.h"
#include "frigate.h"
#include "../Hummingbird Engine/CollisionSystem/Tools/Color.h"
#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"

cottageSpawnController::cottageSpawnController(worldPlane* inPlain, frigate* inCot)
{
	currentPlane = inPlain;
	currentCottage = inCot;
	alarmable::submitAlarmableRegistration(8.0f, alarmableManager::ALARM_ID::ALARM0);
}


cottageSpawnController::~cottageSpawnController()
{
	if (checkForAlarm)
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM0);
	}
	else
	{
		alarmable::submitAlarmableDeregistration(alarmableManager::ALARM_ID::ALARM1);
	}
}

void cottageSpawnController::alarm0()
{
	hummingbirdEngine::setClearColor(Color::Black);
	currentPlane->darkness();
	cottageFactoryWithRecycling::SetAllDarkness(currentCottage->ShipPos);
	alarmable::submitAlarmableRegistration(2.0f, alarmableManager::ALARM_ID::ALARM1);
	checkForAlarm = false;
}

void cottageSpawnController::alarm1()
{
	hummingbirdEngine::setClearColor(Color::DeepSkyBlue);
	currentPlane->lightness();
	cottageFactoryWithRecycling::SetAllLightness();
	for (int i = 0; i < numberOfEnemies; i++)
	{
		cottageFactoryWithRecycling::Createcottage(currentCottage->ShipPos);
	}
	alarmable::submitAlarmableRegistration(8.0f, alarmableManager::ALARM_ID::ALARM0);
	checkForAlarm = true;
}
