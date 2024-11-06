#pragma once
#include "GraphicsEngine.h"

#include "UI_Credits.h"
#include "UI_RenderOptions.h"


class UIManager
{
private:
	UIManager();
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};

	static UIManager* sharedInstance;

public:
	static UIManager* get();
	
	static void initialize(HWND windowHandle);
	static void release();

	void drawAllUI();

	const UI_RenderOptions* getRenderOptions() { return m_UI_RenderOptions; }


private:
	bool is_Show_Window = true;
	UI_Credits* m_UI_Credits = nullptr;
	UI_RenderOptions* m_UI_RenderOptions = nullptr;


};