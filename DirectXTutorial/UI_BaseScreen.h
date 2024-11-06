#pragma once
#include "GraphicsEngine.h"

class UI_BaseScreen
{
protected:
	bool m_isActive = false;

public:
	void setActive(bool enable) {
		m_isActive = enable;
	}
	
	virtual void TryShow() = 0;
};