#include "userScene.h"

#include "frigate.h"
#include "ground.h"
#include "player.h"
#include "HUD.h"
#include "tank.h"
#include "../Hummingbird Engine/Additions/Terrain/Terrain.h"
#include "bulletFactoryWithRecycling.h"
#include "EnemtBulletFactoryWithRecycling.h"
#include "toySoldierFactoryWithRecycling.h"
#include "toySoldierSpawnController.h"
#include "EnemySoldier.h"
#include "../Hummingbird Engine/Asset Manager/Sound Manager/SoundManager.h"

#include "TankShellFactoryWithRecycling.h"

userScene::userScene()
{
}

userScene::~userScene()
{
	delete onScreen;
	delete ship;
	delete vroom;
	delete guy;

	bulletFactoryWithRecycling::Terminate();
	EnemyBulletFactoryWithRecycling::Terminate();
	//toySoldierFactoryWithRecycling::Terminate();
}

void userScene::initialize()
{
	DebugMsg::out("ENTERING USER  SCENE\n");
	
	SetTerrain("pBumpy");
	playerANDTerrain = SetCollisionTerrain<player>();
	SoundManager::playSound("BackgroundRain", true);

	onScreen = new HUD();
	ship = new frigate();
	vroom = new tank();	
	guy = new player();

	//enemySpawner =  new toySoldierSpawnController(guy);

	frigateANDbullet = registerCollideablePair<bullet, EnemySoldier>();
	frigateANDplayer = registerCollideablePair<EnemyBullet, player>();
	tankANDplayer = registerCollideablePair<tank, player>();
	shellANDEnemy = registerCollideablePair<TankShell, EnemySoldier>();
	bulletANDtank = registerCollideablePair<EnemyBullet, tank>();
}

void userScene::sceneEnd()
{
	SoundManager::stopSound("BackgroundRain");
	RemoveTerrain("pBumpy");
	deregisterTerrainCollision(playerANDTerrain);

	deregisterCollideableGroup(frigateANDbullet);
	deregisterCollideableGroup(frigateANDplayer);
	deregisterCollideableGroup(tankANDplayer);
	ship->sceneExit();
	guy->sceneExit();
	vroom->sceneExit();
	onScreen->sceneExit();

	bulletFactoryWithRecycling::returnAllObjects();
	EnemyBulletFactoryWithRecycling::returnAllObjects();
	//toySoldierFactoryWithRecycling::returnAllObjects();
}