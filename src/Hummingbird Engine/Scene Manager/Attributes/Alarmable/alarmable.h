#ifndef _alarmable
#define _alarmable

#include "../../Game Objects/gameObjects.h"
#include "../alarmable/alarmableManager.h"

//------------------------------------
//Forward Declarations
//------------------------------------
class alarmableRegistratonCommand;
class alarmableDeregistratonCommand;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Allows inherited class to Set seconds based Alarms. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class alarmable : public virtual gameObjects
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	alarmable();
	~alarmable();
	alarmable(const alarmable&) = delete;
	alarmable& operator=(const alarmable&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Scene deregistraion. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="id">	The identifier. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void sceneDeregistraion(alarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Scene registraion. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="time">	The time. </param>
	/// <param name="id">  	The identifier. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void sceneRegistraion(float time, alarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit alarmable deregistration. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="id">	The identifier. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void submitAlarmableDeregistration(alarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit alarmable registration. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="time">	The time. </param>
	/// <param name="id">  	The identifier. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void submitAlarmableRegistration(float time, alarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Trigger alarm. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="id">	The identifier. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void triggerAlarm(alarmableManager::ALARM_ID id);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Triggers code when alarm0 has been set and set time has elapsed. NOTE: Not all alarms
	///				have to be set.
	/// \code
	///	void userObject::sceneEntry()
	///	 {
	///		alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM0);
	///	 }
	///	* // ...
	///	void userObject::alarm0()
	///	 {
	///		//Do something!
	///		//If you want to trigger this code again. Reset Alarm
	///		alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM0);
	///	 }
	/// // ...
	///	\endcode
	///</summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void alarm0() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Triggers code when alarm0 has been set and set time has elapsed. NOTE: Not all alarms
	///				have to be set.
	/// \code
	///	void userObject::sceneEntry()
	///	 {
	///		alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM1);
	///	 }
	///	* // ...
	///	void userObject::alarm1()
	///	 {
	///		//Do something!
	///		//If you want to trigger this code again. Reset Alarm
	///		alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM1);
	///	 }
	/// // ...
	///	\endcode
	///</summary>
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void alarm1() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Triggers code when alarm2 has been set and set time has elapsed. NOTE: Not all alarms
	///				have to be set.
	/// \code
	///	void userObject::sceneEntry()
	///	 {
	///		alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM0);
	///	 }
	///	* // ...
	///	void userObject::alarm2()
	///	 {
	///		//Do something!
	///		//If you want to trigger this code again. Reset Alarm
	///		alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM0);
	///	 }
	/// // ...
	///	\endcode
	///</summary>
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void alarm2() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Triggers code when alarm3 has been set and set time has elapsed. NOTE: Not all alarms
	///				have to be set.
	/// \code
	///	void userObject::sceneEntry()
	///	 {
	///		alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM3);
	///	 }
	///	* // ...
	///	void userObject::alarm3()
	///	 {
	///		//Do something!
	///		//If you want to trigger this code again. Reset Alarm
	///		alarmable::submitAlarmableRegistration(3, alarmableManager::ALARM_ID::ALARM3);
	///	 }
	/// // ...
	///	\endcode
	///</summary>
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void alarm3() {};

	
	struct RegistrationData
	{
		registrationState currentState;
		alarmableRegistratonCommand* pRegistrationCmd;
		alarmableDeregistratonCommand* pDeregistrationCmd;
		alarmableManager::alarmableMapRef myDeleteRef;
	};
	RegistrationData RegData[alarmableManager::ALARM_NUMBER];
};

#endif // !_alarmable