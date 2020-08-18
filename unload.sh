#!/bin/sh

LIBPATH="/tmp/actrainer/build-Library-Desktop-Debug/libLibrary.so"

[ ! -f $LIBPATH ] && echo "Biblioteca não encontrada (Compile e execute o script de injeção)." && exit 1
ACPID=$(pidof linux_64_client) || { echo "Processo não encontrado"; exit 1; }
grep -q libLibrary /proc/$ACPID/maps || { echo "Biblioteca não carregada!"; exit 1; }

sudo gdb -batch \
	-ex "attach $ACPID" \
	-ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
	-ex "set \$dlclose = (int(*)(void*)) dlclose" \
	-ex "set \$library = \$dlopen(\"$LIBPATH\", 1)" \
	-ex "call \$dlclose(\$library)" \
	-ex "call \$dlclose(\$library)" \
	-ex "detach" \
	-ex "quit"
