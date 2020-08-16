#ifndef MODULE_H
#define MODULE_H

#include "Core.h"

class Module
{
	protected:
		Core& core;

	public:
		Module(Core& core);
		virtual void think() = 0;
};

#endif // MODULE_H
