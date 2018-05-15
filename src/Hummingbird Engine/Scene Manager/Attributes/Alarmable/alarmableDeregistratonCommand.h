#pragma once

#include "../Command/commandBase.h"
#include "alarmableManager.h"


class alarmable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An alarmable deregistraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class alarmableDeregistratonCommand: public commandBase
{
public:
	alarmableDeregistratonCommand();
	~alarmableDeregistratonCommand();
	alarmableDeregistratonCommand(alarmable * up);
	alarmableDeregistratonCommand(const alarmableDeregistratonCommand& other) = default;
	alarmableDeregistratonCommand& operator=(const alarmableDeregistratonCommand&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void execute();	

	alarmableManager::ALARM_ID alarmId;
	float alarmTime;
private:
	alarmable* alarmablePointer;

};

