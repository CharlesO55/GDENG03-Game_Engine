#pragma once
#include "UI_BaseScreen.h"

#include "PhysicsComponent.h"
#include "GameObjectManager.h"

class UI_Inspector : public UI_BaseScreen {
public:
	UI_Inspector() : UI_BaseScreen() { m_isActive = true; }

	void TryShow() {
		if (!m_isActive || !GameObjectManager::Get())
			return;

		
		SceneObject* obj = GameObjectManager::Get()->GetSelectedObject();
		if (ImGui::Begin("Inspector") && obj) {
			ImGui::Text(obj->GetName().c_str());

			if (ImGui::Button("Add Rigidbody")) {
				new PhysicsComponent(obj);
			}
		}
		ImGui::End();
	}
};