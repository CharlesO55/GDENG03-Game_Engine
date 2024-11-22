#pragma once
#include "UI_BaseScreen.h"

#include "EngineState.h"

class UI_EngineState : public UI_BaseScreen {
public:
	UI_EngineState() : UI_BaseScreen() { m_isActive = true; }

	void TryShow() {
		if (!m_isActive)
			return;

		if (ImGui::Begin("Engine State")) {
			if (ImGui::Button("Edit")) {
				EngineState::SetState(EngineState::STATE::EDIT);
				GameObjectManager::Get()->RevertObjectStates();
			}
			ImGui::SameLine();			


			if (EngineState::GetState() == EngineState::STATE::PLAY) {
				if (ImGui::Button("Pause")) {
					EngineState::SetState(EngineState::STATE::PAUSE);
				}
			}
			else {
				if (ImGui::Button("Play")) {
					EngineState::SetState(EngineState::STATE::PLAY);
				}
			}

			
		}
		ImGui::End();
	}
};