#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"
#include "AzulCore.h"


class HUDSprites: public drawable, public Align16
{
public:
	HUDSprites();
	~HUDSprites();

	void sceneEntry();
	void sceneExit();
	virtual void drawHUD() override;
	
	int health = 10;
private:
	GraphicsObject_Sprite* pGObj_HUDSprites1;
	GraphicsObject_Sprite* pGObj_HUDSprites2;
	Matrix pos;
	Matrix rot;
	float angle = 0.0f;

};

