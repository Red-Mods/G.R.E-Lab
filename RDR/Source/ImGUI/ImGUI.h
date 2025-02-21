#pragma once



// ImGUI colors definition.
#define IMGUI_COLOR_LIGHTBLUE ImVec4(0.0f, 0.5f, 1.0f, 0.8f)

#define IMGUI_COLOR_FRED ImVec4(1.0f, 0.0f, 0.17254902f, 1.0f)
#define IMGUI_COLOR_RED ImVec4(1.0f, 0.0f, 0.17254902f, 0.8f)
#define IMGUI_COLOR_LRED ImVec4(1.0f, 0.0f, 0.17254902f, 0.5f)
#define IMGUI_COLOR_SLRED ImVec4(1.0f, 0.0f, 0.17254902f, 0.3f)

#define IMGUI_COLOR_FBLACK ImVec4(0.07f, 0.0f, 0.0f, 1.0f)
#define IMGUI_COLOR_BLACK ImVec4(0.07f, 0.0f, 0.0f, 0.8f)
#define IMGUI_COLOR_LBLACK ImVec4(0.07f, 0.0f, 0.0f, 0.5f)
#define IMGUI_COLOR_SLBLACK ImVec4(0.07f, 0.0f, 0.0f, 0.3f)

#define IMGUI_COLOR_FWHITE ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
#define IMGUI_COLOR_WHITE ImVec4(1.0f, 1.0f, 1.0f, 0.8f)
#define IMGUI_COLOR_LWHITE ImVec4(1.0f, 1.0f, 1.0f, 0.5f)
#define IMGUI_COLOR_SLWHITE ImVec4(1.0f, 1.0f, 1.0f, 0.3f)



class ImGUI : public Singleton<ImGUI>
{
	public:
		ImGUI();
		~ImGUI();

		void Initialize(HWND _Window, ID3D12Device* _Device, ID3D12DescriptorHeap* _DescriptorHeap, DXGI_FORMAT _Format);
		void Render(ID3D12GraphicsCommandList* _GraphicsCommandList);
		void Shutdown(bool _DestroyContext = false);

		void RegisterWindow(const std::string& _Name, const std::shared_ptr<ImGUIWindow>& _Window);

		template<typename T>
		void RegisterWindow(const std::string& _Name)
		{
			std::shared_ptr<T> window = std::make_shared<T>();

			RegisterWindow(_Name, window);
		}

		const std::shared_ptr<ImGUIWindow> GetWindow(const std::string& _Name) const
		{
			if (!m_Windows.contains(_Name))
				return nullptr;

			return m_Windows.at(_Name);
		}

		bool IsAnyWindowOpened();
		
		void Resize();

		float GetScaleFactor() const
		{
			return m_ScaleFactor;
		}

	private:
		ImGuiIO* m_IO;
		ImGuiStyle* m_Style;
		ImGuiContext* m_Context;

		float m_ScaleFactor;

		bool m_HasEveryWindowsBeenUnfocused;

		std::unordered_map<std::string, std::shared_ptr<ImGUIWindow>> m_Windows;
};