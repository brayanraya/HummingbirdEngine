#ifndef _scene
#define _scene

#include "AzulCore.h"
#include "../Attributes/Drawable/drawableManager.h"
#include "../Attributes/Updateable/updateableManager.h"
#include "../Attributes/Alarmable/alarmableManager.h"
#include "../Attributes/Inputable/keyboardEventManager.h"
#include "../Attributes/Collidable/collideableManager.h"
#include "../Scene/sceneRegistrationBroker.h"
#include "../Game Objects/gameObjectsManager.h"
#include "../../Asset Manager/Terrain Manager/terrainManager.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Basic scene skeleton. The parent to all user derived scenes </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class scene
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	scene();
	virtual ~scene();
	scene(const scene&) = delete;
	scene& operator=(const scene&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Vitrual: Scene Initialization. To be Overwritten in user derived scene. 
	/// </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	virtual void initialize();
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Vitrual: Scene End. To be Overwritten in user derived scene. 
	/// </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	virtual void sceneEnd();

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Wrapper function for the Update Cycle of the Azul Core. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void update();
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Wrapper function for the Draw Cycle of the Azul Core. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void draw();
	
	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls register for Drawable.</summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	/// 
	/// <param name="up">	The drawable Object Pointer. </param>
	///-------------------------------------------------------------------------------------------------
	void registerDrawable(drawable* up);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls deregister for Drawable. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="up">	The drawable Object Pointer. </param>
	///-------------------------------------------------------------------------------------------------
	void deregisterDrawable(drawable* up);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls register for Updateable. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="up">	The Updateable Object Pointer. </param>
	///-------------------------------------------------------------------------------------------------
	void registerUpdateable(updateable * up);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls deregister for Updateable. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="up">	The Updateable Object Pointer. </param>
	///-------------------------------------------------------------------------------------------------
	void deregisterUpdateable(updateable * up);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls register for alarmable. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="time">	Time in the future. </param>
	/// <param name="up">  	The Alarmable event pair(pointer and alarm number). </param>
	///-------------------------------------------------------------------------------------------------
	void registerAlarmable(float time, alarmableManager::AlarmEvent up);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls deregister for alarmable. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="up">	The Alarmable Object Pointer. </param>
	/// <param name="id">	The Alarm number to be activated. </param>
	///-------------------------------------------------------------------------------------------------
	void deregisterAlarmable(alarmable* up, alarmableManager::ALARM_ID id);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls register for inputable. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="pInput">	The Alarmable Object Pointer. </param>
	/// <param name="inPair">	The Alarmable event pair(pointer and alarm number). </param>
	///-------------------------------------------------------------------------------------------------
	void registerInputable(inputable * pInput, std::pair<AZUL_KEY, inputable::INPUT_TYPE> inPair);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls deregisters the inputable. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="pInput"> 	The Inputable Object Pointer. </param>
	/// <param name="inKey">  	The Keyboard key to be registered. </param>
	/// <param name="inEvent">	The Input Type: press or release. </param>
	///-------------------------------------------------------------------------------------------------
	void deregisterInputable(inputable *pInput, AZUL_KEY inKey, inputable::INPUT_TYPE inEvent);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls register for Game Object. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="pObject"> The Game Object Pointer. </param>
	///-------------------------------------------------------------------------------------------------
	void registerGameObject(gameObjects *pObject);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Calls deregister for Game Object. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="pObject">	The Game Object Pointer. </param>
	///-------------------------------------------------------------------------------------------------
	void deregisterGameObject(gameObjects *pObject);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Submits command to the scene broker. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <param name="toAdd"> Any command to be added.  </param>
	///-------------------------------------------------------------------------------------------------
	void submitCommand(commandBase * toAdd);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Registers a collideable pair. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <typeparam name="C1">	Collidable TypeA. </typeparam>
	/// <typeparam name="C2">	Collidable TypeB. </typeparam>
	///-------------------------------------------------------------------------------------------------
	template<typename C1,typename C2>
	std::list<collisionTestCommandBase*>::iterator registerCollideablePair() { return myCollideableManager.SetCollisionPair<C1, C2>(); };

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Registers a collideable to itself. </summary>
	///
	/// <remarks>	Braya, 2/27/2017. </remarks>
	///
	/// <typeparam name="C1">	Collidable TypeA. </typeparam>
	///-------------------------------------------------------------------------------------------------
	template<typename C1>
	std::list<collisionTestCommandBase*>::iterator registerCollideableSelf() { myCollideableManager.SetCollisionSelf<C1>(); };


	void deregisterCollideableGroup(std::list<collisionTestCommandBase*>::iterator inIT) { return myCollideableManager.RemoveCollisionPair(inIT); };

	void SetTerrain(std::string userNameOfTerrain) { terrainManager::PutTerrainInScene(userNameOfTerrain); };

	void RemoveTerrain(std::string userNameOfTerrain) { terrainManager::RemoveTerrainInScene(userNameOfTerrain); };


	template<typename C1>
	std::list<collisionTestCommandBase*>::iterator SetCollisionTerrain() { return myCollideableManager.SetCollisionTerrain<C1>(); };

	void deregisterTerrainCollision(std::list<collisionTestCommandBase*>::iterator inIT) { return myCollideableManager.RemoveTerrainCollision(inIT); };

private:

	/// <summary>	Manager for registration broker. </summary>
	sceneRegistrationBroker myRegistrationBroker;

	/// <summary>	Manager for drawable. </summary>
	drawableManager myDrawableManager;

	/// <summary>	Manager for updateable. </summary>
	updateableManager myUpdateableManager;

	/// <summary>	Manager for alarmable. </summary>
	alarmableManager myAlarmableManager;

	/// <summary>	Manager for keyboard event. </summary>
	keyboardEventManager myKeyboardEventManager;

	/// <summary>	Manager for game objects. </summary>
	gameObjectsManager myGameObjectsManager;

	/// <summary>	Manager for collideable. </summary>
	collideableManager myCollideableManager;
	friend class sceneManager;
	/// <summary>	Check if scene has switch. </summary>
	bool prepareSwitch;
};

#endif // !_scene
