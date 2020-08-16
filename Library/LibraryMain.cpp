#include "LibraryGlobal.h"
#include "Core.h"
#include <cstdio>
#include <dlfcn.h>

Core* core;

LIBRARY_LOAD void libraryLoad()
{
	void* dlHandle = dlopen("/home/giovani/Documentos/repos/AssaultCubeTrainerLinux/build-Library-Desktop-Debug/libLibrary.so", RTLD_NOW);

	if (dlHandle)
	{
		core = new Core(dlHandle);

		printf("dylibHandle: %p\n", dlHandle);
		printf("Modulo carregado\n");
	}

	else
	{
		printf("dylibHandle: NULL\n");
	}
}

LIBRARY_UNLOAD void libraryUnload()
{
	delete core;
	printf("Modulo descarregado\n");
}
