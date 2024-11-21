#pragma once
#include "GraphicsEngine.h"
#include <map>

class UI_BaseScreen;


class UIManager
{
public:
	enum class SCREEN_ID {
		CREDITS,
		RENDER_OPTIONS,

		MENU_GAMEOBJECT,
		HIERARCHY,
		INSPECTOR
	};

	typedef std::unordered_map<SCREEN_ID, UI_BaseScreen*> UI_SCREEN_MAP;

private:
	UI_SCREEN_MAP m_ScreensMap;


private:
	UIManager();
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};

	static UIManager* i;

public:
	static UIManager* Get();
	
	static void Init(HWND windowHandle);
	static void Release();

	void DrawAllUI();

	static UI_BaseScreen* GetScreen(SCREEN_ID id);

private:
	bool is_Show_Window = true;
};