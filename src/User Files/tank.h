#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Updateable/updateable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"

#include <list>


class EnemySoldier;
class player; 
class EnemyBullet;
class tank: public drawable,public updateable, public alarmable, public inputable, public collideable
{
public:
	tank();
	~tank();

	void sceneEntry();
	void sceneExit();
	virtual void draw() override;
	virtual void update() override;
	virtual void keyPress(AZUL_KEY k) override;
	virtual void alarm0() override;
	void collision(player*);
	void collision(EnemyBullet*);


private:
	
	GraphicsObject_TextureFlat* pTankBodyTexture;
	GraphicsObject_TextureFlat* pTankTurretTexture;
	Matrix world;
	Matrix myScale;
	Matrix myRotation;
	Vect myBodyPosition;
	Vect myHeadPosition;
	player* exit = nullptr;
	const float TransSpeed = 1.5f;
	const float ShipRotAng = .0125f;
	float bodyScaleFactor = 3.0f;
	bool shot = false;
	bool active;
	int health = 50;
};

