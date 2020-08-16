#ifndef HACKMAIN_H
#define HACKMAIN_H

#include <thread>

class ModuleManager;

class Core
{
	private:
		std::thread* coreThread;
		ModuleManager* moduleManager;
		void* dylibHandle;

	public:
		volatile bool shouldThink;
		volatile bool running;

		Core(void* dylibHandle);
		~Core();
		void askUnload();
};

#endif // HACKMAIN_H
