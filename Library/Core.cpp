#include "Core.h"
#include <dlfcn.h>
#include <iostream>
#include <thread>

#include "ModuleManager.h"

using namespace std;

void coreThreadRunner(Core* core, ModuleManager* moduleManager)
{
	while (moduleManager->thinkAll())
	{
		printf("ThinkAll\n");
	}

	printf("ThinkAll stopping\n");
	core->running = false;
}

Core::Core(void* dylibHandle)
{
	this->dylibHandle = dylibHandle;
	this->moduleManager = new ModuleManager(*this);

	this->shouldThink = true;
	this->running = true;

	this->coreThread = new thread(coreThreadRunner, this, this->moduleManager);
	this->coreThread->detach();
}

void Core::askUnload()
{
	this->shouldThink = false;
	dlclose(this->dylibHandle);
}

Core::~Core()
{
	printf("Tentando destruir Core...\n");

	this->shouldThink = false;
	while (this->running);

	printf("Destruindo Core...\n");

	delete this->coreThread;
	delete this->moduleManager;
}
