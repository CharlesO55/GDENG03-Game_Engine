#include "AppWindow.h"
#include "InputSystem.h"
#include "EngineTime.h"
#include "Debugger.h"

#include "UIManager.h"

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
			while (app.Run()) {
			}
		}
		catch (...) {
			UIManager::release();
			InputSystem::release();
			GraphicsEngine::release();
			EngineTime::release();
			return -1;
		}
	}


	UIManager::release();
	InputSystem::release();
	GraphicsEngine::release();
	EngineTime::release();

	return 0;
}