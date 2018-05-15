#ifndef _gameObjectsEntryCommand
#define _gameObjectsEntryCommand

#include "../Attributes/Command/commandBase.h"

class gameObjects;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A game objects entry command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class gameObjectsEntryCommand: public commandBase
{
public:
	//------------------------------------
	//Big 4
	//------------------------------------
	gameObjectsEntryCommand() = delete;
	gameObjectsEntryCommand(gameObjects * inObject);
	gameObjectsEntryCommand(const gameObjectsEntryCommand& other) = default;
	gameObjectsEntryCommand& operator=(const gameObjectsEntryCommand&) = delete;
	~gameObjectsEntryCommand() = delete;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Executes the GameObject to be added to the manager. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void execute();	
private:
	gameObjects* myObject;
};

#endif //!_gameObjectsEntryCommand
