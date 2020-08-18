#!/bin/sh

[ ! -f ./build-Library-Desktop-Debug/libLibrary.so ] && { echo "Biblioteca não econtrada."; exit 1; }
[ ! -d /tmp/actrainer/ ] && { mkdir -p /tmp/actrainer; cp -r ./{inject.sh,unload.sh,build-Library-Desktop-Debug/} /tmp/actrainer/; }

LIBPATH="/tmp/actrainer/build-Library-Desktop-Debug/libLibrary.so"
ACPID=$(pidof linux_64_client) || { echo "Processo não encontrado"; exit 1; }
grep -q libLibrary /proc/$ACPID/maps && { echo "Biblioteca já carregada!"; exit 1; }

cd /tmp/actrainer/
sudo gdb -batch \
	-ex "attach $ACPID" \
	-ex "set \$dlopen=(void*(*)(char*, int)) dlopen" \
	-ex "set \$dlclose=(int(*)(void*)) dlclose" \
	-ex "set \$library=\$dlopen(\"$LIBPATH\", 1)" \
	-ex "set logging overwrite on" \
	-ex "set logging redirect on" \
	-ex "set logging file handle" \
	-ex "set logging on" \
	-ex "printf \"%p\", \$library" \
	-ex "set logging off" \
	-ex "detach" \
	-ex "quit"
