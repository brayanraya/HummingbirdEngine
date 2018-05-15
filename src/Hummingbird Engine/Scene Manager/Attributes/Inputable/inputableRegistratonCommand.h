#pragma once

#include "../Command/commandBase.h"
#include "Keyboard.h"
#include "inputable.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An inputable registraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class inputableRegistratonCommand: public commandBase
{
public:
	//------------------------------------
	// Big 4. 
	//------------------------------------
	inputableRegistratonCommand();
	~inputableRegistratonCommand();
	inputableRegistratonCommand(const inputableRegistratonCommand& other) = default;
	inputableRegistratonCommand& operator=(const inputableRegistratonCommand&) = delete;

	inputableRegistratonCommand(inputable * input, AZUL_KEY inKey, inputable::INPUT_TYPE inType);

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

