#ifndef _keyboardEventManager
#define _keyboardEventManager

#include "Keyboard.h"
#include "../../../Main Game/hummingbirdEngine.h"
#include "singleKeyEventManager.h"
#include "../inputable/inputable.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for an entire keyboard of key event. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class keyboardEventManager
{	
private:	
	inputable::keyboardMap keyboardEventManagerList;

friend class scene;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Process the elements. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void processElements();

public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	keyboardEventManager() = default;
	~keyboardEventManager();
	keyboardEventManager(const keyboardEventManager&) = delete;
	keyboardEventManager& operator=(const keyboardEventManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Register inputables. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="input"> 	[in,out] If non-null, the input. </param>
	/// <param name="inPair">	The in pair. </param>
	///-------------------------------------------------------------------------------------------------
	void registerinputable(inputable * input, std::pair<AZUL_KEY, inputable::INPUT_TYPE> inPair);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Deregister inputables. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="input"> 	[in,out] If non-null, the input. </param>
	/// <param name="inKey"> 	The in key. </param>
	/// <param name="inPair">	The in pair. </param>
	///-------------------------------------------------------------------------------------------------
	void deregisterinputable(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inPair);
};

#endif //!_keyboardEventManager