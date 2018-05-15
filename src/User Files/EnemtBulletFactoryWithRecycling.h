#ifndef _EnemtBulletFactoryWithRecycling
#define _EnemtBulletFactoryWithRecycling

#include <list>
#include <queue>
#include "EnemtBullet.h"

class EnemyBulletFactoryWithRecycling
{
private:
	static EnemyBulletFactoryWithRecycling* ptrInstance;			// Game set up as a singleton

	EnemyBulletFactoryWithRecycling() = default;												// Private constructor
	EnemyBulletFactoryWithRecycling(const EnemyBulletFactoryWithRecycling&) = delete;				// Prevent copy-construction
	EnemyBulletFactoryWithRecycling& operator=(const EnemyBulletFactoryWithRecycling&) = delete;	// Prevent assignment
	~EnemyBulletFactoryWithRecycling();														// Only this class can delete

	static EnemyBulletFactoryWithRecycling& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new EnemyBulletFactoryWithRecycling;
		return *ptrInstance;
	};

	std::queue<EnemyBullet*> recycledItems;  // Back to be a non-static member
	std::list<EnemyBullet*> onScreen;
										// Note: Some facctory designs also keep a list of 'currently active' objects
										// Often useful at cleanup time. Not needed for this demo however

										// Private methods to perform actual work on member var
	void privCreateEnemtBullet(const Vect& pos, const Matrix& rot);
	void privRecycleEnemtBullet(EnemyBullet* b);
	void privTerminate();
	void privreturnAllObjects();
public:

	// Services/API
	static void CreateEnemtBullet(const Vect& pos, const Matrix& rot) { Instance().privCreateEnemtBullet(pos, rot); };
	static void RecycleEnemtBullet(EnemyBullet* b) { Instance().privRecycleEnemtBullet(b); };

	static void Terminate() { Instance().privTerminate(); };
	static void returnAllObjects() { Instance().privreturnAllObjects(); }
};


#endif _EnemtBulletFactoryWithRecycling