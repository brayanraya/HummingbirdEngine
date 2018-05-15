#include "alarmableManager.h"
#include "../alarmable/alarmable.h"
#include "../../../Time/Time Manager/timeManager.h"

alarmableManager::~alarmableManager()
{
}

void alarmableManager::registerAlarmable(float time, AlarmEvent inEvent)
{
	inEvent.first->RegData[int(inEvent.second)].myDeleteRef = alarmableManagerList.insert(alarmableManagerList.begin(), std::pair<float, AlarmEvent>(time, inEvent));
}

void alarmableManager::deregisterAlarmable(alarmable* alarm, ALARM_ID id)
{
	alarmableManagerList.erase(alarm->RegData[int(id)].myDeleteRef);
}

void alarmableManager::processElements()
{
	alarmableMapRef it = alarmableManagerList.begin();
	float timeWhenTriggered = timeManager::getCurrentTime();
	while (it != alarmableManagerList.end())
	{
		if ((*it).first < timeWhenTriggered)
		{
			(*it).second.first->triggerAlarm((*it).second.second);
			alarmableMapRef tempIt(it);
			tempIt++;
			deregisterAlarmable((*it).second.first, (*it).second.second);
			it = tempIt;
		}
		else
		{
			break;
		}
	}
}
