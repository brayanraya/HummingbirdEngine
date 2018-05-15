#pragma once

#include "../Command/commandBase.h"
#include "alarmableManager.h"

class alarmable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An alarmable registraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class alarmableRegistratonCommand: public commandBase
{
public:
	alarmableRegistratonCommand();
	~alarmableRegistratonCommand();
	alarmableRegistratonCommand(alarmable * up);
	alarmableRegistratonCommand(const alarmableRegistratonCommand& other) = default;
	alarmableRegistratonCommand& operator=(const alarmableRegistratonCommand&) = delete;

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

