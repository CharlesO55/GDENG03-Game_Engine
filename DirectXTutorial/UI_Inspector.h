#pragma once
#include "UI_BaseScreen.h"

#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "GameObjectManager.h"

class UI_Inspector : public UI_BaseScreen {
public:
	UI_Inspector() : UI_BaseScreen() { m_isActive = true; }

	void TryShow() {
		if (!m_isActive || !GameObjectManager::Get())
			return;


		SceneObject* obj = GameObjectManager::Get()->GetSelectedObject();

		

		if (ImGui::Begin("Inspector") && obj) {
			ImGui::Text(("#" + std::to_string(obj->GetInstanceID()) + ": ").c_str());
			ImGui::SameLine();
			ImGui::Text(obj->GetName().c_str());

			HandleTransformPanel(obj);
			HandleRigidbodyPanel(obj);
		}
		ImGui::End();
	}

	void HandleTransformPanel(SceneObject* obj) {
		if (!obj->getTransform())
			return;
		
		Matrix4x4 world = obj->getTransform()->getWorldMatrix();
		Vector3D pos = world.getTranslation();
		Vector3D rot = world.getEulerAngles();
		Vector3D scale = world.getScale();

		if (ImGui::CollapsingHeader("Transform"))
		{
			if (ImGui::BeginTable("Control Transform", 3))
			{
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::DragFloat("Px", &pos.x, 0.01f);
				ImGui::TableNextColumn();
				ImGui::DragFloat("Py", &pos.y, 0.01f);
				ImGui::TableNextColumn();
				ImGui::DragFloat("Pz", &pos.z, 0.01f);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::DragFloat("Rx", &rot.x, 0.01f);
				ImGui::TableNextColumn();
				ImGui::DragFloat("Ry", &rot.y, 0.01f);
				ImGui::TableNextColumn();
				ImGui::DragFloat("Rz", &rot.z, 0.01f);

				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::DragFloat("Sx", &scale.x, 0.01f);
				ImGui::TableNextColumn();
				ImGui::DragFloat("Sy", &scale.y, 0.01f);
				ImGui::TableNextColumn();
				ImGui::DragFloat("Sz", &scale.z, 0.01f);

				ImGui::EndTable();
			}


			static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
			if (ImGui::BeginTable("Matrix", 4, flags)) {
				
				const std::array<float, 16> &v = world.Flatten();

				for (int i = 0; i < 16; i++) {
					ImGui::TableNextColumn();

					std::stringstream stream;
					stream << std::fixed << std::setprecision(2) << v[i];
					ImGui::Text(stream.str().c_str());
				}

				ImGui::EndTable();
			}
		}
		obj->getTransform()->setPosition(pos);
		obj->getTransform()->setRotation(rot);
		obj->getTransform()->setScale(scale);
	}


	void HandleRigidbodyPanel(SceneObject* obj) {
		PhysicsComponent* rb = nullptr;

		if (ImGui::CollapsingHeader("Rigidbody")) {
			if (PhysicsSystem::Get()->TryFindComponent(obj->GetInstanceID(), rb)) {
				ImGui::Text("Add rigidbody settings here to toggle");







			}

			else {
				if (ImGui::Button("Add Rigidbody")) {
					new PhysicsComponent(obj);
				}
			}
		}
	}
};