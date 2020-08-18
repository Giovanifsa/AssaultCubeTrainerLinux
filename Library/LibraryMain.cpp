#include "LibraryGlobal.h"
#include "Core.h"
#include <cstdio>
#include <dlfcn.h>

Core* core;

LIBRARY_LOAD void libraryLoad()
{
	core = new Core();
}

LIBRARY_UNLOAD void libraryUnload()
{
	delete core;
	printf("Modulo descarregado\n");
}
