#ifndef _startHUD
#define _startHUD

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"

class startHUD: public drawable
{
public:
	startHUD();
	~startHUD();

	void sceneEntry();
	void sceneExit();

	virtual void drawHUD() override;

	void switchScreen();

	bool currentScreen();


private:
	GraphicsObject_Sprite* pGObj_Splash;
	GraphicsObject_Sprite* pGObj_Letter;

	bool isSplash;
};

#endif //!_startHUD
