#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"

class cottageFactoryWithRecycling;
class worldPlane;
class frigate;

class cottageSpawnController: public alarmable
{

public:
	cottageSpawnController() = default;
	cottageSpawnController(worldPlane * inPlain, frigate* inCot);
	~cottageSpawnController();

	virtual void alarm0() override;
	virtual void alarm1() override;


	worldPlane* currentPlane;
	frigate* currentCottage;
	int numberOfEnemies = 3;
	bool checkForAlarm;
};

