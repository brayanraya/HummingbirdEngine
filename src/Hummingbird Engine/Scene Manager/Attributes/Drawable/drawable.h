#ifndef _drawable
#define _drawable

#include "../../Game Objects/gameObjects.h"
#include "../Shared Enum/regestrationState.h"
#include "../Drawable/drawableManager.h"

class drawableRegistratonCommand;
class drawableDeregistratonCommand;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Allows inherited class to register and deregister for the engines draw cycle. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class drawable : public virtual gameObjects
{
public:
	drawable();
	~drawable();
	drawable(const drawable&) = delete;
	drawable& operator=(const drawable&) = delete;

	void sceneDeregistraion();
	void sceneRegistraion();
	void submitDrawableDeregistration();
	void submitDrawableRegistration();

	/// <summary>
	/// Renders the game object to the screen. This will be overloaded in the user defined game class. This is for 3D Models
	/// \code
	///	userObject::userObject()
	///	 {
	///		pObject = new GraphicsObject...
	///	 }
	///	* // ...
	///	void userObject::sceneEntry()
	///	 {
	///		drawable::submitDrawableRegistration();
	///	 }
	///	* // ...
	///	void userObject::draw()
	///	 {
	///		pplayer->Render(cameraManager::currentCam()); //3D Models
	///	 }
	/// // ...
	///	\endcode
	/// </summary>
	virtual void draw() {};
	/// <summary>
	/// Renders the game object to the screen. This will be overloaded in the user defined game class. This is for 2D Sprites
	/// \code
	///	userObject::userObject()
	///	 {
	///		pObject = new GraphicsObject...
	///	 }
	///	* // ...
	///	void userObject::sceneEntry()
	///	 {
	///		drawable::submitDrawableRegistration();
	///	 }
	///	* // ...
	///	void userObject::drawHUD()
	///	 {
	///		pplayer->Render(cameraManager::currentHUD()); //2D Sprites
	///	 }
	/// // ...
	///	\endcode
	/// </summary>
	virtual void drawHUD() {};
	drawableManager::drawableListRef myDeleteRef;
private:
	registrationState currentState;
	drawableRegistratonCommand* pRegistrationCmd;
	drawableDeregistratonCommand* pDeregistrationCmd;

};

#endif // !_drawable