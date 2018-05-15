#ifndef _HUD
#define _HUD
#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"

#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"

class frigate;

class HUD: public drawable
{
public:
	HUD();
	~HUD();

	void sceneEntry();
	void sceneExit();
	virtual void drawHUD() override;


private:
	GraphicsObject_Sprite* pGObj_Crosshair;
	GraphicsObject_Sprite* pGObj_Bullet;
	GraphicsObject_Sprite* pGObj_Num1;

	float spin;
};

#endif //!_HUD
