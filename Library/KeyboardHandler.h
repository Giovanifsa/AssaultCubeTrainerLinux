#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "Module.h"

class KeyboardHandler : Module
{
	public:
		KeyboardHandler(Core& core);
		bool keyIsPressed(KeySym ks);
		void think() override;
};

#endif // KEYBOARDHANDLER_H
