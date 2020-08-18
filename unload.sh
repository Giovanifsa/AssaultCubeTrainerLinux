#!/bin/sh

LIBPATH="/home/rafael/dev/cxx/AssaultCubeTrainerLinux/build-Library-Desktop-Debug/libLibrary.so"

sudo gdb -batch \
	-ex "attach $(pidof linux_64_client)" \
	-ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
	-ex "set \$dlclose = (int(*)(void*)) dlclose" \
	-ex "set \$library = \$dlopen(\"${LIBPATH}\", 1)" \
	-ex "call \$dlclose(\$library)" \
	-ex "call \$dlclose(\$library)" \
	-ex "call \$dlclose(\$library)" \
	-ex "detach" \
	-ex "quit"
