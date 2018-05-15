#ifndef _collideableManager
#define _collideableManager

#include <list>
#include "collideableTestPairCommand.h"
#include "collideableTestSelfCommand.h"
#include "collideableTestTerrainCommand.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for collideables. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class collideableManager
{
private:
friend class scene;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Called by Scene to test collisions. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void processElements()	
	{
		for (auto it = groupList.begin(); it != groupList.end(); it++)
		{
			(*it)->execute();
		}
	};
	std::list<collisionTestCommandBase*> groupList;
	std::list<collisionTestCommandBase*>::iterator endPosition = groupList.end();
public:
	collideableManager() {};
	~collideableManager() 
	{
		for (auto it = groupList.begin(); it != groupList.end(); it++)
		{
			delete (*it);
			//DebugMsg::out("colideableManager list deleting \n", groupList.size());
		}
		//DebugMsg::out("colideableManager list = %d \n", groupList.size());
	};
	
	collideableManager(const collideableManager&) = delete;
	collideableManager& operator=(const collideableManager&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets collision with pair. Called by a scene wrapper function </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <typeparam name="C1">	Type of the c 1. </typeparam>
	/// <typeparam name="C2">	Type of the c 2. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename C1,typename C2>
	std::list<collisionTestCommandBase*>::iterator SetCollisionPair()
	{
		collisionTestCommandBase* temp = new collisionTestPairCommand<C1, C2>;
		return groupList.insert(endPosition, temp);
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Sets collision to self. Called by a scene wrapper function. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <typeparam name="C1">	Type of the c 1. </typeparam>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename C1>
	std::list<collisionTestCommandBase*>::iterator SetCollisionSelf()
	{
		collisionTestCommandBase* temp = new collisionTestSelfCommand<C1>;
		return groupList.insert(endPosition,temp);
	};


	template<typename C1>
	std::list<collisionTestCommandBase*>::iterator SetCollisionTerrain()
	{
		collisionTestCommandBase* temp = new collisionTestTerrainCommand<C1>;
		return groupList.insert(endPosition, temp);
	};

	void RemoveCollisionPair(std::list<collisionTestCommandBase*>::iterator inIT)
	{
		//delete *inIT;
		groupList.erase(inIT);
	}

	void RemoveTerrainCollision(std::list<collisionTestCommandBase*>::iterator inIT)
	{
		groupList.erase(inIT);
	}
};

#endif //!_collideableManager