#ifndef _gameObjectsExitCommand
#define _gameObjectsExitCommand

#include "../Attributes/Command/commandBase.h"

class gameObjects;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A game objects exit command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class gameObjectsExitCommand: public commandBase
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	gameObjectsExitCommand() = delete;
	gameObjectsExitCommand(gameObjects * inObject);
	~gameObjectsExitCommand() = delete;
	gameObjectsExitCommand(const gameObjectsExitCommand& other) = default;
	gameObjectsExitCommand& operator=(const gameObjectsExitCommand&) = default;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes the GameObject to be added to the manager. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void execute();	
private:
	gameObjects* myObject;
};

#endif //_gameObjectsExitCommand