#pragma once
#include "UI_BaseScreen.h"

#include "Texture.h"

class UI_Credits : public UI_BaseScreen {

private:
	ImTextureID m_Icon;

public:
	UI_Credits() : UI_BaseScreen() {
		
		TexturePtr iconTex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"..\\Assets\\Textures\\wood.jpg");
		m_Icon = (ImTextureID)(intptr_t)iconTex.get()->getShaderResourceView();
	}


	void TryShow() {
		if (!m_isActive)
			return;
		
		if (ImGui::Begin("Credits")) {
			ImGui::Image(m_Icon, ImVec2(128, 128));
			ImGui::TextColored(ImVec4(1, 1, 0, 1), "About");
			ImGui::Text("Dev: Charles Ong");
			ImGui::Text("Ver: Pardcode 17 + IMGUI");

			ImGui::Text("References:");
			ImGui::Indent();
			ImGui::BulletText("GDENG03");
			ImGui::BulletText("Pardcode");
			ImGui::Unindent();

			if (ImGui::Button("Close"))
				setActive(false);
		}
		ImGui::End();
	}
};