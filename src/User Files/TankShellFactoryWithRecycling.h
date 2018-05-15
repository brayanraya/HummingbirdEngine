#ifndef _TankShellFactoryWithRecycling
#define _TankShellFactoryWithRecycling

#include <list>
#include <queue>
#include "TankShell.h"

class TankShellFactoryWithRecycling
{
private:
	static TankShellFactoryWithRecycling* ptrInstance;			// Game set up as a singleton

	TankShellFactoryWithRecycling() = default;												// Private constructor
	TankShellFactoryWithRecycling(const TankShellFactoryWithRecycling&) = delete;				// Prevent copy-construction
	TankShellFactoryWithRecycling& operator=(const TankShellFactoryWithRecycling&) = delete;	// Prevent assignment
	~TankShellFactoryWithRecycling();														// Only this class can delete

	static TankShellFactoryWithRecycling& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new TankShellFactoryWithRecycling;
		return *ptrInstance;
	};

	std::queue<TankShell*> recycledItems;  // Back to be a non-static member
	std::list<TankShell*> onScreen;
										// Note: Some facctory designs also keep a list of 'currently active' objects
										// Often useful at cleanup time. Not needed for this demo however

										// Private methods to perform actual work on member var
	void privCreateTankShell(const Vect& pos, const Matrix& rot);
	void privRecycleTankShell(TankShell* b);
	void privTerminate();
	void privreturnAllObjects();
public:

	// Services/API
	static void CreateTankShell(const Vect& pos, const Matrix& rot) { Instance().privCreateTankShell(pos, rot); };
	static void RecycleTankShell(TankShell* b) { Instance().privRecycleTankShell(b); };

	static void Terminate() { Instance().privTerminate(); };
	static void returnAllObjects() { Instance().privreturnAllObjects(); }
};


#endif _TankShellFactoryWithRecycling