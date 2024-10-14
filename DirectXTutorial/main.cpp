#include "AppWindow.h"
#include "InputSystem.h"
#include "EngineTime.h"


int main()
{
	try
	{
		GraphicsEngine::create();
		InputSystem::create();
		EngineTime::create();
	}
	catch (...) { return -1; }

	{
		try
		{
			AppWindow app;
			while (app.Run());
		}
		catch (...) {
			InputSystem::release();
			GraphicsEngine::release();
			return -1;
		}
	}


	InputSystem::release();
	GraphicsEngine::release();

	return 0;
}