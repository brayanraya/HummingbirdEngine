#ifndef _commandBase
#define _commandBase

#include "AzulCore.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An empty base that all x-able derive from to be added to the scene brokers list. </summary>
///
/// <remarks>	Braya, 3/1/2017. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class commandBase : public Align16
{
public:
	commandBase();
	~commandBase();

	virtual void execute() = 0;
};
#endif // !_commandBase