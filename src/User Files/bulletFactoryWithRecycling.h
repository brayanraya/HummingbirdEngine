#ifndef _bulletFactoryWithRecycling
#define _bulletFactoryWithRecycling

#include <list>
#include <queue>
#include "bullet.h"

class bulletFactoryWithRecycling
{
private:
	static bulletFactoryWithRecycling* ptrInstance;			// Game set up as a singleton

	bulletFactoryWithRecycling() = default;												// Private constructor
	bulletFactoryWithRecycling(const bulletFactoryWithRecycling&) = delete;				// Prevent copy-construction
	bulletFactoryWithRecycling& operator=(const bulletFactoryWithRecycling&) = delete;	// Prevent assignment
	~bulletFactoryWithRecycling();														// Only this class can delete

	static bulletFactoryWithRecycling& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new bulletFactoryWithRecycling;
		return *ptrInstance;
	};

	std::queue<bullet*> recycledItems;  // Back to be a non-static member
	std::list<bullet*> onScreen;
										// Note: Some facctory designs also keep a list of 'currently active' objects
										// Often useful at cleanup time. Not needed for this demo however

										// Private methods to perform actual work on member var
	void privCreatebullet(const Vect& pos, const Matrix& rot);
	void privRecyclebullet(bullet* b);
	void privTerminate();
	void privreturnAllObjects();
public:

	// Services/API
	static void Createbullet(const Vect& pos, const Matrix& rot) { Instance().privCreatebullet(pos, rot); };
	static void Recyclebullet(bullet* b) { Instance().privRecyclebullet(b); };

	static void Terminate() { Instance().privTerminate(); };
	static void returnAllObjects() { Instance().privreturnAllObjects(); }
};


#endif _bulletFactoryWithRecycling