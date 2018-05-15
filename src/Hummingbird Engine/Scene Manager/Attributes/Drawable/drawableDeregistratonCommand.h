#pragma once

#include "../Command/commandBase.h"
class drawable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A drawable deregistraton command. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class drawableDeregistratonCommand: public commandBase
{
public:
	drawableDeregistratonCommand();
	~drawableDeregistratonCommand();
	drawableDeregistratonCommand(const drawableDeregistratonCommand& other) = default;
	drawableDeregistratonCommand& operator=(const drawableDeregistratonCommand&) = delete;

	drawableDeregistratonCommand(drawable * up);
	void execute();
private:
	drawable* drawablePointer;
};

