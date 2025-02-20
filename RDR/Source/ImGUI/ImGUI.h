#pragma once



class ImGUI : public Singleton<ImGUI>
{
	public:
		ImGUI();
		~ImGUI();

		void Initialize(HWND _Window, ID3D12Device* _Device, ID3D12DescriptorHeap* _DescriptorHeap, DXGI_FORMAT _Format);
		void Render(ID3D12GraphicsCommandList* _GraphicsCommandList);
		void Shutdown(bool _DestroyContext = false);

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

		std::unordered_map<std::string, std::shared_ptr<ImGUIWindow>> m_Windows;
};