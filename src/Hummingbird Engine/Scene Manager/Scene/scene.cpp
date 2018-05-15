#include "scene.h"
#include "sceneManager.h"

scene::scene()
{
	prepareSwitch = false;
}

scene::~scene()
{
}

void scene::initialize()
{
}

void scene::update()
{
	myRegistrationBroker.executeCommands();

	myAlarmableManager.processElements();
	myUpdateableManager.processElements();
	myKeyboardEventManager.processElements();
	myCollideableManager.processElements();
}

void scene::draw()
{
	myDrawableManager.processElements();
	myGameObjectsManager.processElements();

	if (prepareSwitch)
	{
		sceneManager::swapScenes();
		prepareSwitch = false;
	}	
}

void scene::sceneEnd()
{
}

void scene::registerDrawable(drawable * up)
{
	myDrawableManager.registerDrawable(up);
}

void scene::deregisterDrawable(drawable * up)
{
	myDrawableManager.deregisterDrawable(up);
}
void scene::registerUpdateable(updateable * up)
{
	myUpdateableManager.registerUpdateable(up);
}

void scene::deregisterUpdateable(updateable * up)
{
	myUpdateableManager.deregisterUpdateable(up);
}

void scene::registerAlarmable(float time, alarmableManager::AlarmEvent up)
{
	myAlarmableManager.registerAlarmable(time, up);
}

void scene::deregisterAlarmable(alarmable * up, alarmableManager::ALARM_ID id)
{
	myAlarmableManager.deregisterAlarmable(up, id);
}

void scene::registerInputable(inputable * pInput, std::pair<AZUL_KEY, inputable::INPUT_TYPE> inPair)
{
	myKeyboardEventManager.registerinputable(pInput, inPair);
}

void scene::deregisterInputable(inputable * pInput, AZUL_KEY inKey, inputable::INPUT_TYPE inEvent)
{
	myKeyboardEventManager.deregisterinputable(pInput, inKey, inEvent);
}

void scene::registerGameObject(gameObjects * pObject)
{
	myGameObjectsManager.registerGameObjects(pObject,gameObjectsManager::SCENE_ID::ENTER);
}

void scene::deregisterGameObject(gameObjects * pObject)
{
	myGameObjectsManager.registerGameObjects(pObject, gameObjectsManager::SCENE_ID::EXIT);
}

void scene::submitCommand(commandBase * cmd)
{
	myRegistrationBroker.addCommand(cmd);
}