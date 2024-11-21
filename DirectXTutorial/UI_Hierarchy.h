#pragma once
#include "UI_BaseScreen.h"

#include "GameObjectManager.h"

class UI_Hierarchy : public UI_BaseScreen {
public:
	UI_Hierarchy() : UI_BaseScreen() { m_isActive = true; }


	void TryShow() {
		if (!m_isActive || !GameObjectManager::Get())
			return;

		if (ImGui::Begin("Hierarchy")) {
			ImGui::Text(("Objects: " + std::to_string(GameObjectManager::Get()->GetAllObjects().size())).c_str());

			for (SceneObject* o : GameObjectManager::Get()->GetAllObjects()) {
				if (ImGui::Button(o->GetName().c_str())) {
					GameObjectManager::Get()->SelectObject(o);
				}
			}
		}
		ImGui::End();
	}
};