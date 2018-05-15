#ifndef _singleKeyEventManager
#define _singleKeyEventManager

#include "Keyboard.h"
#include "../../../Main Game/hummingbirdEngine.h"
#include "inputable.h"
#include <list>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Manager for a single key event. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class singleKeyEventManager
{
private:
	AZUL_KEY myKey;
	inputable::keyList keyPressCol;
	inputable::keyList keyReleasedCol;

	bool lastStateOfKey;
	bool currentlyDown;

	friend class keyboardEventManager;
	void processElements();

public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	singleKeyEventManager() = delete;
	singleKeyEventManager(AZUL_KEY inKey);
	~singleKeyEventManager();
	singleKeyEventManager(const singleKeyEventManager&) = delete;
	singleKeyEventManager& operator=(const singleKeyEventManager&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Register inputable from list. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="input"> 	[in,out] If non-null, the input. </param>
	/// <param name="inKey"> 	The in key. </param>
	/// <param name="inType">	Type of the in. </param>
	///-------------------------------------------------------------------------------------------------
	void registerinputable(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType);

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Deregister inputable from list. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="input"> 	[in,out] If non-null, the input. </param>
	/// <param name="inKey"> 	The in key. </param>
	/// <param name="inType">	Type of the in. </param>
	/// 
	///-------------------------------------------------------------------------------------------------
	void deregisterinputable(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType);
};

#endif //!_singleKeyEventManager