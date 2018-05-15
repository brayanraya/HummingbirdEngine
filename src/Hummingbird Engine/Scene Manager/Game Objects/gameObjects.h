#ifndef _gameObjects
#define _gameObjects

#include "AzulCore.h"
#include "../Attributes/Shared Enum/regestrationState.h"
#include <list>
#include "gameObjectsEntryCommand.h"
#include "gameObjectsExitCommand.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Basic game object skeleton. Inherited by every x-able. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class gameObjects: public Align16
{
public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	gameObjects();
	~gameObjects() = default;

	gameObjects(const gameObjects&) = default;
	gameObjects& operator=(const gameObjects&) = default;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Connects object to scene. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void connectToScene();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Disconnects object from scene. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void disconnectToScene();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Called after a gameObject has been submitted. This is where all registrations for Types go.
	/// \code
	///	userObject::userObject()
	///	 {
	///		///Do one time not changing info here
	///			pObject = new GraphicsObject...
	///		///Auto submit on creation with this line. Or do it later.... like in a factory?
	///			submitEntry();
	///	 }
	/// ...
	///	void userObject::sceneEntry()
	///	 {
	///		drawable::submitDrawableRegistration();
	///	 }
	/// ...
	///	\endcode
	/// </summary>
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void sceneEntry() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>
	/// Called after a gameObject has been called for an exit. This is where all deregistrations for Types go.
	/// \code
	///	void userObject::Foo()
	///	 {
	///			///call this if you want the item GONE. ie not for factory use.
	///			submitExit();
	///	 }
	/// ...
	///	void userObject::sceneExit()
	///	 {
	///		drawable::submitDrawableDeregistration();
	///	 }
	/// ...
	///	\endcode
	/// </summary>
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void sceneExit() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit entry. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void submitEntry();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit exit. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void submitExit();

	std::list<gameObjects*>::iterator myDeleteEnterRef;
	std::list<gameObjects*>::iterator myDeleteExitRef;	
	
private:
	registrationState currentState;
	gameObjectsExitCommand* pGameExitCommand;
	gameObjectsEntryCommand* pGameEntryCommand;
};

#endif // !_gameObjects