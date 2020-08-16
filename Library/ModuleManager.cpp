#include "ModuleManager.h"

ModuleManager::ModuleManager(Core& core) : core(core), keyboardHandler(core)
{

}

bool ModuleManager::thinkAll()
{
	if (core.shouldThink)
	{
		this->keyboardHandler.think();
		return true;
	}

	return false;
}
