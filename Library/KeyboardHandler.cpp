#include "KeyboardHandler.h"

#include <iostream>

KeyboardHandler::KeyboardHandler(Core& core) : Module(core)
{

}

bool KeyboardHandler::keyIsPressed(KeySym ks) {
	Display *dpy = XOpenDisplay(":0");
	char keys_return[32];
	XQueryKeymap(dpy, keys_return);
	KeyCode kc2 = XKeysymToKeycode(dpy, ks);
	bool isPressed = !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
	XCloseDisplay(dpy);
	return isPressed;
}

void KeyboardHandler::think()
{
	if (keyIsPressed(XK_i))
	{
		printf("Requisitando descarregamento do modulo...\n");
		this->core.askUnload();
	}
}
