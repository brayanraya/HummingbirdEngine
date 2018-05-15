#ifndef _cottageFactoryWithRecycling
#define _cottageFactoryWithRecycling

#include <queue>
#include <list>
#include "cottage.h"

class cottageFactoryWithRecycling
{
private:
	static cottageFactoryWithRecycling* ptrInstance;			// Game set up as a singleton

	cottageFactoryWithRecycling() = default;												// Private constructor
	cottageFactoryWithRecycling(const cottageFactoryWithRecycling&) = delete;				// Prevent copy-construction
	cottageFactoryWithRecycling& operator=(const cottageFactoryWithRecycling&) = delete;	// Prevent assignment
	~cottageFactoryWithRecycling();														// Only this class can delete

	static cottageFactoryWithRecycling& Instance()	    // Access reference (all public methods will be static)
	{
		if (!ptrInstance)
			ptrInstance = new cottageFactoryWithRecycling;
		return *ptrInstance;
	};

	std::queue<cottage*> recycledItems;  // Back to be a non-static member
	std::list<cottage*> onScreen;
										// Note: Some facctory designs also keep a list of 'currently active' objects
										// Often useful at cleanup time. Not needed for this demo however

										// Private methods to perform actual work on member var
	void privCreatecottage(const Vect& inVec);
	void privRecyclecottage(cottage* b);
	void privSetAllDarkness(const Vect& inVec);
	void privSetAllLightness();
	void privreturnAllObjects();
public:

	// Services/API
	static void Createcottage(const Vect& inVec) { Instance().privCreatecottage(inVec); };
	static void Recyclecottage(cottage* b) { Instance().privRecyclecottage(b); };
	static void SetAllDarkness(const Vect& inVec) { Instance().privSetAllDarkness(inVec); };
	static void SetAllLightness() { Instance().privSetAllLightness(); };

	static void Terminate();
	static void returnAllObjects() { Instance().privreturnAllObjects(); }
};


#endif _cottageFactoryWithRecycling