#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"

#include <list>
#include "Align16.h"

class frigate;
class bullet;

class cottage: public drawable, public collideable,public Align16
{
public:
	cottage();
	~cottage();

	void sceneEntry();
	void sceneExit();
	virtual void draw() override;
	void collision(frigate*);
	void collision(bullet*);

	void fromFactory(const Vect& inVec);

	void darkness(const Vect& inVec);

	void lightness();

	std::list<cottage*>::iterator quickRemovePos;
private:
	GraphicsObject_TextureFlat *pCottageTexture;
	Texture *pCottageTex[4];
	Matrix pos;
	float scaleFactor = 3.0f;
	float health;
	float level = 500;
	bool checkForReg = false;
};

