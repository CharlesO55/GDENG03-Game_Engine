#pragma once
#include <Windows.h>

class Window
{
public:
	Window();
	bool init();
	bool broadcast();
	bool release();
	bool isRun();
	~Window();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	virtual void onFocus();
	virtual void onKillFocus();

	void CalcWindowRect();

protected:
	HWND m_hwnd;

	int m_windowWidth, m_windowHeight;

	bool m_is_run;
};

