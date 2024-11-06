#pragma once
#include "UI_BaseScreen.h"

class UI_RenderOptions : public UI_BaseScreen {
public:
	float WorldColor[4] = { 0.2f,0.2f,0.2f,0.2f };

public:
	UI_RenderOptions() : UI_BaseScreen() {}

	void TryShow() {
		if (!m_isActive)
			return;

		if (ImGui::Begin("Render Options")) {

			ImGui::ColorPicker4("##ColorWheel", (float*)&WorldColor, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
			ImGui::SameLine();
			if (ImGui::BeginChild("##ColorResults")) {
				ImGui::Text("Color");
				ImGui::ColorEdit4("##ColorIcon", (float*)&WorldColor, ImGuiColorEditFlags_NoInputs);
			}
			ImGui::EndChild();
			
			if (ImGui::Button("Close"))
				setActive(false);
		}
		ImGui::End();
	}
};