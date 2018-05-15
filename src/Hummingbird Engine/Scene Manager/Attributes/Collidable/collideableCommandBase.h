#ifndef _collideableCommandBase
#define _collideableCommandBase

#include "AzulCore.h"
#include "..\..\Attributes\Command\commandBase.h"

class collideableCommandBase : public commandBase
{
public:
	collideableCommandBase();
	~collideableCommandBase();

	virtual void execute() {};
};

#endif // !_collideableCommandBase