#ifndef _updateable
#define _updateable

#include "../../Game Objects/gameObjects.h"
#include "../Shared Enum/regestrationState.h"
#include "../updateable/updateableManager.h"

//------------------------------------
// Forward Declarations
//------------------------------------
class updateableRegistratonCommand;
class updateableDeregistratonCommand;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Allows inherited class to register and deregister for the engines update cylce. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class updateable : public virtual gameObjects
{
public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	updateable();
	~updateable();
	updateable(const updateable&) = delete;
	updateable& operator=(const updateable&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Scene deregistraion. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void sceneDeregistraion();
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Scene registraion. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void sceneRegistraion();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Submit updateable deregistration. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------

	void submitUpdateableDeregistration();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Submit updateable registration. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------

	void submitUpdateableRegistration();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Virtual Function: What is done during update. 
	/// \code
	///	void userObject::sceneEntry()
	///	 {
	///		alarmable::submitAlarmableRegistration();
	///	 }
	///	* // ...
	///	void userObject::update()
	///	 {
	///		///Things that change on a frame to frame basis
	///	 }
	/// // ...
	///	\endcode
	/// </summary>
	///-------------------------------------------------------------------------------------------------
	virtual void update() {};

	updateableManager::updateableListRef myDeleteRef;
private:
	//------------------------------------
	//Private Variables 
	//------------------------------------
	registrationState currentState;
	updateableRegistratonCommand* pRegistrationCmd;
	updateableDeregistratonCommand* pDeregistrationCmd;

};

#endif // !_updateable