#pragma once

#include "../Command/commandBase.h"
#include "Keyboard.h"
#include "inputable.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An inputable deregistraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class inputableDeregistratonCommand: public commandBase
{
public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	inputableDeregistratonCommand() = delete;
	~inputableDeregistratonCommand() = default;
	inputableDeregistratonCommand(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType);
	inputableDeregistratonCommand(const inputableDeregistratonCommand& other) = default;
	inputableDeregistratonCommand& operator=(const inputableDeregistratonCommand&) = delete;

	///-------------------------------------------------------------------------------------------------
	/// <summary>	Executes this object. </summary>
	///
	/// <remarks>	Braya, 3/1/2017. </remarks>
	///-------------------------------------------------------------------------------------------------
	void execute();

private:
	inputable* inputablePointer;	
	AZUL_KEY givenKey;
	inputable::INPUT_TYPE givenType;
};

