#ifndef _toySoldierFactoryWithRecycling
#define _toySoldierFactoryWithRecycling

#include <queue>
#include <list>
#include "EnemySoldier.h"

class toySoldierFactoryWithRecycling
{
private:
	static toySoldierFactoryWithRecycling* ptrInstance;			// Game set up as a singleton

	toySoldierFactoryWithRecycling() = default;												// Private constructor
	toySoldierFactoryWithRecycling(const toySoldierFactoryWithRecycling&) = delete;				// Prevent copy-construction
	toySoldierFactoryWithRecycling& operator=(const toySoldierFactoryWithRecycling&) = delete;	// Prevent assignment
	~toySoldierFactoryWithRecycling();														// Only this class can delete

	static toySoldierFactoryWithRecycling& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new toySoldierFactoryWithRecycling;
		return *ptrInstance;
	};

	std::queue<EnemySoldier*> recycledItems;  // Back to be a non-static member
	std::list<EnemySoldier*> onScreen;
										// Note: Some facctory designs also keep a list of 'currently active' objects
										// Often useful at cleanup time. Not needed for this demo however

										// Private methods to perform actual work on member var
	void privCreatetoySoldier();
	void privRecycletoySoldier(EnemySoldier* b);
	void privreturnAllObjects();
	void privAllFace(const Vect& playerPos);

	void privTerminate();

public:

	// Services/API
	static void CreatetoySoldier() { Instance().privCreatetoySoldier();};
	static void RecycletoySoldier(EnemySoldier* b) { Instance().privRecycletoySoldier(b); };
	static void Terminate() { Instance().privTerminate(); };
	static int numberOnScreen() { return Instance().onScreen.size(); };
	static void returnAllObjects() { Instance().privreturnAllObjects(); }
	static void haveAllOnScreenFacePlayer(const Vect& posOfPlayer) { Instance().privAllFace(posOfPlayer); };
};


#endif _toySoldierFactoryWithRecycling