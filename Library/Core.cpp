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

Core::Core()
{
	this->moduleManager = new ModuleManager(*this);

	this->shouldThink = true;
	this->running = true;

	this->coreThread = new thread(coreThreadRunner, this, this->moduleManager);
	this->coreThread->detach();
}

void Core::askUnload()
{
	this->shouldThink = false;
	printf("Tentando decarregar biblioteca.\n");

	void* handle;
	char handles[9];
	FILE *handlef = fopen("/tmp/actrainer/handle", "r");
	if (handlef) {
		fscanf(handlef, "%s", handles);
		handle = (void*) strtol(handles, NULL, 16);
		fclose(handlef);
		std::thread* dlclosethread = new thread(dlclose, handle);
		dlclosethread->detach();
	} else {
		printf("Erro em carregar o handle\n");
		printf("Calling unload script (SUDO NEEDED)\n");
		system("/tmp/actrainer/unload.sh &");
	}
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
