#ifndef HACKMAIN_H
#define HACKMAIN_H

#include <thread>

class ModuleManager;

class Core
{
	private:
		std::thread* coreThread;
		ModuleManager* moduleManager;

	public:
		volatile bool shouldThink;
		volatile bool running;

		Core();
		~Core();
		void askUnload();
};

#endif // HACKMAIN_H
