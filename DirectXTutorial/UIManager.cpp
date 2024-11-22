#include "UIManager.h"

#include "UI_Credits.h"
#include "UI_RenderOptions.h"
#include "UI_GameObjectMenu.h"
#include "UI_Hierarchy.h"
#include "UI_Inspector.h"
#include "UI_EngineState.h"

#include "Debugger.h"

UIManager* UIManager::i = NULL;

UIManager* UIManager::Get()
{
	return i;
}

void UIManager::Init(HWND windowHandle)
{
	if (i != nullptr)
		Debugger::Error("[DUPLICATE ERROR] Engine Time");

	i = new UIManager();


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(
		GraphicsEngine::get()->getRenderSystem()->m_d3d_device,
		GraphicsEngine::get()->getRenderSystem()->m_imm_context
	);
	ImGui::StyleColorsDark();


	Debugger::Success("[UIManager] Created");
}

void UIManager::Release()
{
	delete UIManager::i;
}

void UIManager::DrawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (is_Show_Window) {
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Samples")) {
				if (ImGui::MenuItem("Credits", ""))			{ m_ScreensMap[SCREEN_ID::CREDITS]->setActive(true); }
				if (ImGui::MenuItem("Render Options", ""))  { m_ScreensMap[SCREEN_ID::RENDER_OPTIONS]->setActive(true); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Window")) {
				if (ImGui::MenuItem("Hierarchy", "")) { m_ScreensMap[SCREEN_ID::HIERARCHY]->setActive(true); }
				if (ImGui::MenuItem("Inspector", "")) { m_ScreensMap[SCREEN_ID::INSPECTOR]->setActive(true); }
				ImGui::EndMenu();
			}


			m_ScreensMap[SCREEN_ID::MENU_GAMEOBJECT]->TryShow();
			

			ImGui::EndMainMenuBar();
		}

		m_ScreensMap[SCREEN_ID::CREDITS]->TryShow();
		m_ScreensMap[SCREEN_ID::RENDER_OPTIONS]->TryShow();
		m_ScreensMap[SCREEN_ID::HIERARCHY]->TryShow();
		m_ScreensMap[SCREEN_ID::INSPECTOR]->TryShow();
		m_ScreensMap[SCREEN_ID::ENGINE_STATE]->TryShow();

		

	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UI_BaseScreen* UIManager::GetScreen(SCREEN_ID id)
{
	return i->m_ScreensMap[id];
}

UIManager::UIManager()
{
	m_ScreensMap[SCREEN_ID::CREDITS] = new UI_Credits();
	m_ScreensMap[SCREEN_ID::RENDER_OPTIONS] = new UI_RenderOptions();
	m_ScreensMap[SCREEN_ID::MENU_GAMEOBJECT] = new UI_GameObjectMenu();
	m_ScreensMap[SCREEN_ID::HIERARCHY] = new UI_Hierarchy();
	m_ScreensMap[SCREEN_ID::INSPECTOR] = new UI_Inspector();
	m_ScreensMap[SCREEN_ID::ENGINE_STATE] = new UI_EngineState();
}

UIManager::~UIManager()
{
	is_Show_Window = false;
	
	for (UI_SCREEN_MAP::iterator itr = m_ScreensMap.begin(); itr != m_ScreensMap.end(); itr++)
	{
		delete (itr->second);
	}
	m_ScreensMap.clear();

	Debugger::Warning("[UIManager] Destroyed");
}