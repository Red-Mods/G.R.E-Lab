#include <pch.h>



// ImGUI colors definition.
#define IMGUI_COLOR_LIGHTBLUE ImVec4(0.0f, 0.5f, 1.0f, 0.8f)

#define IMGUI_COLOR_FRED ImVec4(1.0f, 0.0f, 0.0f, 1.0f)
#define IMGUI_COLOR_RED ImVec4(1.0f, 0.0f, 0.0f, 0.8f)
#define IMGUI_COLOR_LRED ImVec4(1.0f, 0.0f, 0.0f, 0.5f)
#define IMGUI_COLOR_SLRED ImVec4(1.0f, 0.0f, 0.0f, 0.3f)

#define IMGUI_COLOR_FBLACK ImVec4(0.015f, 0.0f, 0.0f, 1.0f)
#define IMGUI_COLOR_BLACK ImVec4(0.015f, 0.0f, 0.0f, 0.8f)
#define IMGUI_COLOR_LBLACK ImVec4(0.015f, 0.0f, 0.0f, 0.5f)
#define IMGUI_COLOR_SLBLACK ImVec4(0.015f, 0.0f, 0.0f, 0.3f)



ImGUI::ImGUI()
{
	// Default scale factor.
	m_ScaleFactor = 1.0f;

	// Create ImGUI context.
	m_Context = ImGui::CreateContext();

	// Create and setup ImGUI IO.
	m_IO = &ImGui::GetIO();
	m_IO->IniFilename = NULL;
	m_IO->LogFilename = NULL;
	m_IO->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	// Create and load custom font.
	FontData fontData = Utils::LoadFont(HINST_THISCOMPONENT, MAKEINTRESOURCEW(IDR_GAMEFONT), L"TTF");

	ImFontConfig fontConfig;
	fontConfig.FontDataOwnedByAtlas = false;
	fontConfig.OversampleH = 2;
	fontConfig.OversampleV = 2;

	m_IO->Fonts->AddFontFromMemoryTTF(fontData.Data, fontData.Length, 30.0f, &fontConfig);

	// Creating ImGUI theme & style.
	m_Style = &ImGui::GetStyle();

	m_Style->WindowBorderSize = 0.0f;
	m_Style->WindowRounding = 0.0f;
	m_Style->ChildRounding = 2.0f;
	m_Style->FrameRounding = 2.0f;
	m_Style->GrabRounding = 2.0f;
	m_Style->PopupRounding = 2.0f;
	m_Style->ScrollbarRounding = 2.0f;

	m_Style->ItemSpacing = ImVec2(6.0f, 6.0f);

	for (int i = 0; i < ImGuiCol_COUNT; i++)
	{
		m_Style->Colors[i] = IMGUI_COLOR_RED;
	}

	m_Style->Colors[ImGuiCol_WindowBg] = IMGUI_COLOR_LBLACK;
	m_Style->Colors[ImGuiCol_ScrollbarBg] = IMGUI_COLOR_LBLACK;
	m_Style->Colors[ImGuiCol_ChildBg] = ImVec4();

	m_Style->Colors[ImGuiCol_CheckMark] = IMGUI_COLOR_FBLACK;
	m_Style->Colors[ImGuiCol_Text] = IMGUI_COLOR_FBLACK;
	m_Style->Colors[ImGuiCol_TextDisabled] = IMGUI_COLOR_LBLACK;
	m_Style->Colors[ImGuiCol_TextSelectedBg] = IMGUI_COLOR_LIGHTBLUE;

	m_Style->Colors[ImGuiCol_ButtonHovered] = IMGUI_COLOR_RED;
	m_Style->Colors[ImGuiCol_ButtonActive] = IMGUI_COLOR_FRED;

	m_Style->Colors[ImGuiCol_TableRowBg] = IMGUI_COLOR_LRED;
	m_Style->Colors[ImGuiCol_TableRowBgAlt] = IMGUI_COLOR_SLRED;

	m_Style->Colors[ImGuiCol_PlotLines] = IMGUI_COLOR_BLACK;

	// Registering windows...
	std::shared_ptr<Console> consoleWindow = std::make_shared<Console>();

	consoleWindow->Initialize(m_IO, m_Style);

	m_Windows.emplace("Console", consoleWindow);
}



ImGUI::~ImGUI()
{
	m_Windows.clear();
}



void ImGUI::Initialize(HWND _Window, ID3D12Device* _Device, ID3D12DescriptorHeap* _DescriptorHeap, DXGI_FORMAT _Format)
{
	ImGui_ImplWin32_Init(_Window);
	ImGui_ImplDX12_Init(_Device, D3D12_NUM_BACK_BUFFERS, _Format, _DescriptorHeap, _DescriptorHeap->GetCPUDescriptorHandleForHeapStart(), _DescriptorHeap->GetGPUDescriptorHandleForHeapStart());

	Resize();

	LOG_DEV_INFO("Initialized ImGUI");
}



void ImGUI::Render(ID3D12GraphicsCommandList* _GraphicsCommandList)
{
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (const auto& [_, window] : m_Windows)
	{
		window->Render();
	}

	ImGui::Render();
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), _GraphicsCommandList);
}



void ImGUI::Shutdown(bool _DestroyContext)
{
	if (ImGui::GetCurrentContext())
	{
		if (ImGui::GetIO().BackendRendererUserData)
			ImGui_ImplDX12_Shutdown();

		if (ImGui::GetIO().BackendPlatformUserData)
			ImGui_ImplWin32_Shutdown();

		/* For some reason this is crashing the game when uninjecting (probably something not properly free'ed' properly or some thread sync issues)
		if (_DestroyContext)
			ImGui::DestroyContext();
		*/
	}

	LOG_DEV_INFO("Shutdown ImGUI");
}



bool ImGUI::IsAnyWindowOpened()
{
	for (const auto& [_, window] : m_Windows)
	{
		if (window->IsOpen())
		{
			return true;
		}
	}

	return false;
}



void ImGUI::Resize()
{
	ImVec2 resolution = Utils::GetGameWindowResolution();

	static ImVec2 referenceResolution = ImVec2(3840.0f, 2160.0f);

	m_ScaleFactor = (resolution.x / referenceResolution.x);

	m_Style->ChildRounding *= m_ScaleFactor;
	m_Style->FrameRounding *= m_ScaleFactor;
	m_Style->GrabRounding *= m_ScaleFactor;
	m_Style->PopupRounding *= m_ScaleFactor;
	m_Style->ScrollbarRounding *= m_ScaleFactor;

	m_Style->ItemSpacing.x *= m_ScaleFactor;
	m_Style->ItemSpacing.y *= m_ScaleFactor;

	m_IO->FontGlobalScale *= m_ScaleFactor;

	referenceResolution = resolution;
}