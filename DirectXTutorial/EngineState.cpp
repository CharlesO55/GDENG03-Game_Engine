#include "EngineState.h"
#include "Debugger.h"

EngineState* EngineState::i = nullptr;

EngineState::EngineState()
{
	Debugger::Success("[Engine State] Created");
}

EngineState::~EngineState()
{
	Debugger::Warning("[Engine State] Destroyed");
}


void EngineState::Init()
{
	if (!EngineState::i)
		EngineState::i = new EngineState();
}

void EngineState::Release()
{
	delete EngineState::i;
}

EngineState::STATE EngineState::GetState()
{
	return i->m_State;
}

void EngineState::SetState(STATE state)
{
	i->m_State = state;
}