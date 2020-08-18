#!/bin/sh

LIBPATH=$(pwd)"/build-Library-Desktop-Debug/libLibrary.so"

[ ! -f $LIBPATH ] && echo "Biblioteca não compilada ou diretório errado" && exit 1
ACPID=$(pidof linux_64_client) || { echo "Processo não encontrado"; exit 1; }
grep -q libLibrary /proc/$ACPID/maps && { echo "Biblioteca já carregada!"; exit 1; }

sudo gdb -batch \
	-ex "attach $ACPID" \
	-ex "set \$dlopen=(void*(*)(char*, int)) dlopen" \
	-ex "set \$dlclose=(int(*)(void*)) dlclose" \
	-ex "set \$library=\$dlopen(\"$LIBPATH\", 1)" \
	-ex "detach" \
	-ex "quit"
