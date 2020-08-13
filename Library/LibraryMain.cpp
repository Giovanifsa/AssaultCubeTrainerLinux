#include "LibraryGlobal.h"
#include <cstdio>

LIBRARY_LOAD void libraryLoad()
{
	printf("teste load");
}

LIBRARY_UNLOAD void libraryUnload()
{
	printf("teste unload");
}
