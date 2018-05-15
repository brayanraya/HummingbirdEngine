#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"

#include "../Hummingbird Engine/Main Game/hummingbirdEngine.h"
#include "Align16.h"

class frigate;

class Alien: public drawable, public Align16
{
public:
	Alien();
	~Alien();

	void sceneEntry();
	void sceneExit();
	virtual void drawHUD() override;


private:
	GraphicsObject_Sprite* pGObj_Alien;
};

