#ifndef _updateableManager
#define _updateableManager

#include <list>

class updateable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for updateables. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class updateableManager
{
private:
	using updateableList = std::list<updateable*>;
	updateableList updateableManagerList;

friend class scene;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Process the elements of the Updatable list. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void processElements();

public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	updateableManager() = default;
	~updateableManager();
	updateableManager(const updateableManager&) = delete;
	updateableManager& operator=(const updateableManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Registers the updateable to the list. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="update">	[in,out] If non-null, the updateable. </param>
	///-------------------------------------------------------------------------------------------------
	void registerUpdateable(updateable * update);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Deregisters the updateable from the list. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="update">	[in,out] If non-null, the updateable. </param>
	///-------------------------------------------------------------------------------------------------
	void deregisterUpdateable(updateable * update);

	using updateableListRef = updateableList::iterator;
};

#endif //!_updateableManager