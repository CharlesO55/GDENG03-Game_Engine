#pragma once
#include "UI_BaseScreen.h"

#include "GameObjectManager.h"

class UI_GameObjectMenu : public UI_BaseScreen {
public:
	UI_GameObjectMenu() : UI_BaseScreen() {}

	void TryShow() {
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Teapot", "")) { GameObjectManager::Get()->InstantiateObj(L"teapot"); }
			if (ImGui::MenuItem("Bunny", "")) { GameObjectManager::Get()->InstantiateObj(L"bunny"); }
			if (ImGui::MenuItem("Armadillo", "")) { GameObjectManager::Get()->InstantiateObj(L"armadillo"); }
			ImGui::EndMenu();
		}
	}
};