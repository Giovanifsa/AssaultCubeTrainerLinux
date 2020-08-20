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

		// Gets saved handle addres from the ./inject.sh script
		fscanf(handlef, "%s", handles);
		handle = (void*) strtol(handles, NULL, 16);
		fclose(handlef);

		// Creates thread for the dlclose() function
		pthread_attr_t tAttr;
		pthread_t dlclosethread;
		pthread_attr_init(&tAttr);
		pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);
		pthread_create(&dlclosethread, &tAttr, (void *(*)(void *))dlclose, handle);
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
