#include "LibraryGlobal.h"
#include "Core.h"
#include <cstdio>
#include <dlfcn.h>
#include <stdlib.h>

Core* core;

LIBRARY_LOAD void libraryLoad()
{
	core = new Core();
}

LIBRARY_UNLOAD void libraryUnload()
{
	delete core;
	system("rm -rf /tmp/actrainer &");
	printf("Modulo descarregado\n");
}
