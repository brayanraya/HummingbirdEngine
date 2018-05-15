#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"

class toySoldierFactoryWithRecycling;
class player;

class toySoldierSpawnController: public alarmable
{

public:
	toySoldierSpawnController() = default;
	toySoldierSpawnController( player* inCot);
	~toySoldierSpawnController();

	virtual void alarm0() override;
	virtual void alarm1() override;

	player* currenttoySoldier;
	int numberOfEnemies = 2;
	bool checkForAlarm;
};

