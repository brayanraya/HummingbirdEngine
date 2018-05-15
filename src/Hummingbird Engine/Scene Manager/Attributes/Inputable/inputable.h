#ifndef _inputable
#define _inputable

#include "../../Game Objects/gameObjects.h"
#include "../Shared Enum/regestrationState.h"
#include <map>
#include <list>
#include <vector>

//------------------------------------
// Forward Declarations
//------------------------------------
class inputableRegistratonCommand;
class inputableDeregistratonCommand;
class singleKeyEventManager;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Allows inherited class to register a key and 
/// 			triggers with Key Release/Press. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class inputable : public virtual gameObjects
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Values that represent input types. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	enum class INPUT_TYPE : char
	{
		PRESS,
		RELEASE,
	};

	//------------------------------------
	// Big 4. 
	//------------------------------------
	inputable();
	~inputable();
	inputable(const inputable&) = delete;
	inputable& operator=(const inputable&) = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Scene deregistraion. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="inKey"> 	The in key. </param>
	/// <param name="inType">	Type of the in. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void sceneDeregistraion(AZUL_KEY inKey, INPUT_TYPE inType);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Scene registraion. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="inKey"> 	The in key. </param>
	/// <param name="inType">	Type of the in. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void sceneRegistraion(AZUL_KEY inKey, INPUT_TYPE inType);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit inputable deregistration. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="inKey"> 	The in key. </param>
	/// <param name="inType">	Type of the in. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void submitInputableDeregistration(AZUL_KEY inKey, INPUT_TYPE inType);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Submit inputable registration. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///
	/// <param name="inKey"> 	The in key. </param>
	/// <param name="inType">	Type of the in. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void submitInputableRegistration(AZUL_KEY inKey, INPUT_TYPE inType);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Triggers code via a Switch when a key is pressed. 
	/// \code
	///	void userObject::sceneEntry()
	///	 {
	///		inputable::submitInputableRegistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::PRESS);
	///	 }
	///	* // ...
	///	void userObject::keyPress(AZUL_KEY k)
	///	 {
	///		if (k == AZUL_KEY::KEY_SPACE)
	///		{
	///			if (!numberShot)
	///			{
	///				alarm0();
	///			}
	///		}
	///	 }
	/// // ...
	///	\endcode
	///</summary>
	/// <param name="inKey">	The in key. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void keyPress(AZUL_KEY inKey) { inKey; };

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Triggers code via a Switch when a key is released. 
	/// \code
	///	void userObject::sceneEntry()
	///	 {
	///		inputable::submitInputableRegistration(AZUL_KEY::KEY_SPACE, INPUT_TYPE::RELEASE);
	///	 }
	///	* // ...
	///	void userObject::keyRelease(AZUL_KEY k)
	///	 {
	///		if (k == AZUL_KEY::KEY_SPACE)
	///		{
	///			if (!numberShot)
	///			{
	///				alarm0();
	///			}
	///		}
	///	 }
	/// // ...
	///	\endcode
	///</summary>
	/// <param name="inKey">	The in key. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void keyRelease(AZUL_KEY inKey) { inKey; };

	using keyboardMap = std::map<AZUL_KEY, singleKeyEventManager*>;
	using keyboardMapRef = keyboardMap::iterator;

	using keyList = std::list<inputable*>;
	using keyListRef = keyList::iterator;
	using KeyEvent = std::pair<AZUL_KEY, INPUT_TYPE>;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	A registration data. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	struct RegistrationData
	{
		registrationState				currentState;
		inputableRegistratonCommand*	pRegistrationCmd;
		inputableDeregistratonCommand*	pDeregistrationCmd;
		keyboardMapRef					mapDeleteRef;
		keyListRef						pressListDeleteRef;
		keyListRef						releaseListDeleteRef;
		KeyEvent						theEvent;
	};
	
	std::map<KeyEvent, RegistrationData*> inputableMapOfKeys;
	
};

#endif // !_inputable