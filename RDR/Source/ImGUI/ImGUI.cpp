#include <pch.h>



ImGUI::ImGUI()
{
	// Default scale factor.
	m_ScaleFactor = 1.0f;

	m_HasEveryWindowsBeenUnfocused = false;

	// Create ImGUI context.
	m_Context = ImGui::CreateContext();

	const std::filesystem::path configPath = "ImGUI.ini"_ApplicationPath;
	static const std::string configPathStr = configPath.string();

	// Create and setup ImGUI IO.
	m_IO = &ImGui::GetIO();
	m_IO->IniFilename = configPathStr.c_str();
	m_IO->LogFilename = NULL;
	m_IO->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	// Create and load custom font.
	FontData fontData = Utils::LoadFont(HINST_THISCOMPONENT, MAKEINTRESOURCEW(IDR_GAMEFONT), L"TTF");

	ImFontConfig fontConfig;
	fontConfig.FontDataOwnedByAtlas = false;
	fontConfig.OversampleH = 2;
	fontConfig.OversampleV = 2;

	m_IO->Fonts->AddFontFromMemoryTTF(fontData.Data, fontData.Length, 40.0f, &fontConfig);

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
	RegisterWindow<Home>("Home");
	RegisterWindow<Console>("Console");
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

	bool isAnyWindowFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow);

	if (isAnyWindowFocused)
	{
		m_HasEveryWindowsBeenUnfocused = false;

		// Unlock and show the mouse cursor on screen
		rage::ioMouse::UnlockAndShowCursor(true);
		rage::ioMouse::DisableCursorAlteration(true);

		// Enable/Disable UI inputs
		rage::UIInput::DisableAllInputs(true);

		// Disable player movements & camera movements
		rage::sagPlayerMgr::GetLocalPlayer()->DisablePlayerControl(true);
	}
	else
	{
		if (!m_HasEveryWindowsBeenUnfocused)
		{
			m_HasEveryWindowsBeenUnfocused = true;

			// Allowing back cursor alteration will make the game automatically
			// restore the correct cursor state
			// Example: If the game is currently paused, the mouse will be unlocked and visible otherwise it will stay locked and invisible
			rage::ioMouse::DisableCursorAlteration(false);

			// Enable/Disable UI inputs
			rage::UIInput::DisableAllInputs(false);

			// Disable player movements & camera movements
			rage::sagPlayerMgr::GetLocalPlayer()->DisablePlayerControl(false);
		}
	}

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



void ImGUI::RegisterWindow(const std::string& _Name, const std::shared_ptr<ImGUIWindow>& _Window)
{
	_Window->Initialize(m_IO, m_Style);

	m_Windows.insert_or_assign(_Name, _Window);
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