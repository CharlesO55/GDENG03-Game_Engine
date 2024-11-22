#pragma once

class EngineState {
public:
	enum class STATE {
		EDIT,
		PLAY,
		PAUSE
	};

private:
	static EngineState* i;
	EngineState();
	~EngineState();

	STATE m_State = STATE::EDIT;

public:
	static void Init();
	static void Release();
	static STATE GetState();
	static void SetState(STATE state);
};