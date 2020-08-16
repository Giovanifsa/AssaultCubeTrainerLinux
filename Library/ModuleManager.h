#ifndef MODULEMANAGER_H
#define MODULEMANAGER_H

#include "Core.h"
#include "KeyboardHandler.h"

class ModuleManager
{
	private:
		Core& core;
		KeyboardHandler keyboardHandler;

	public:
		ModuleManager(Core& core);
		bool thinkAll();
};

#endif // MODULEMANAGER_H
