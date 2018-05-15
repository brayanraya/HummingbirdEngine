#pragma once

#include "../Hummingbird Engine/Scene Manager/Scene/scene.h"

class ground;
class frigate;
class bullet;
class player;
class HUD;
class tank;
class Terrain;
class toySoldierSpawnController;

class userScene : public scene
{
public:
	userScene();
	~userScene();
	virtual void sceneEnd();
	virtual void initialize();

private:
		ground* floor;
		frigate* ship;
		player* guy;
		HUD* onScreen;
		tank* vroom;
		Terrain* terra;
		toySoldierSpawnController* enemySpawner;
		std::list<collisionTestCommandBase*>::iterator frigateANDbullet;
		std::list<collisionTestCommandBase*>::iterator frigateANDplayer;
		std::list<collisionTestCommandBase*>::iterator tankANDplayer;
		std::list<collisionTestCommandBase*>::iterator playerANDTerrain;
		std::list<collisionTestCommandBase*>::iterator shellANDEnemy;
		std::list<collisionTestCommandBase*>::iterator	bulletANDtank;
};