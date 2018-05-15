#ifndef _drawableManager
#define _drawableManager

#include <list>

class drawable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for drawables. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class drawableManager
{
private:
	using drawableList = std::list<drawable*>;
	drawableList drawableManagerList;

friend class scene;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Process the elements. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void processElements();

public:
	drawableManager() = default;
	~drawableManager();
	
	drawableManager(const drawableManager&) = delete;
	drawableManager& operator=(const drawableManager&) = delete;
	
	void registerDrawable(drawable * draw);
	void deregisterDrawable(drawable * draw);

	using drawableListRef = drawableList::iterator;
};

#endif //!_drawableManager