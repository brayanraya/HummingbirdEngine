#pragma once

#include "../Hummingbird Engine/Scene Manager/Attributes/Drawable/drawable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Updateable/updateable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Collidable/collideable.h"
#include "../Hummingbird Engine/Scene Manager/Attributes/Alarmable/alarmable.h"

#include <list>

class frigate;
class EnemtBullet;
class bullet;
class Terrain;
class tank;

class EnemySoldier : public drawable, public updateable, public alarmable, public collideable
{
public:
	EnemySoldier();
	~EnemySoldier();

	void sceneEntry();
	void sceneExit();
	virtual void draw() override;
	virtual void update() override;
	virtual void alarm0()override;
	void collision(bullet*);
	void collision(Terrain*) {};
	void TerrainCollision()override;

	void FacePlayer(const Vect & playerPosition);

	void fromFactory();
	std::list<EnemySoldier*>::iterator quickRemovePos;
private:
	GraphicsObject_TextureLight *pToySoldier;
	Matrix world;
	const float myScale = 15.0f;
	Matrix myRotation;
	Vect myPosition;
	const float TransSpeed = 1.5f;
	const float ShipRotAng = .0125f;
	float health;
	int numberShot = 0;
	bool active;
	
};

