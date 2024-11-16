#include "UIManager.h"


#include "GraphicsEngine.h"
#include "Debugger.h"


UIManager* UIManager::sharedInstance = NULL;

UIManager* UIManager::get()
{
	return sharedInstance;
}

void UIManager::initialize(HWND windowHandle)
{
	if (sharedInstance != nullptr)
		Debugger::Error("[DUPLICATE ERROR] Engine Time");

	sharedInstance = new UIManager();


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

void UIManager::release()
{
	delete UIManager::sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (is_Show_Window) {
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Screens")) {
				if (ImGui::MenuItem("Credits", "")) { m_UI_Credits->setActive(true); }
				if (ImGui::MenuItem("Render Options", "")) { m_UI_RenderOptions->setActive(true); }
				ImGui::EndMenu();
			}

			m_UI_GameObjectMenu->TryShow();
			

			ImGui::EndMainMenuBar();
		}

		m_UI_Credits->TryShow();
		m_UI_RenderOptions->TryShow();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}


UIManager::UIManager()
{
	m_UI_Credits = new UI_Credits();
	m_UI_RenderOptions = new UI_RenderOptions();
	m_UI_GameObjectMenu = new UI_GameObjectMenu();
}

UIManager::~UIManager()
{
	is_Show_Window = false;
	delete m_UI_Credits;

	Debugger::Warning("[UIManager] Destroyed");
}