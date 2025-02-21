#pragma once



class ImGUIWindow
{
	public:
		ImGUIWindow()
		{
			m_IO = nullptr;
			m_Style = nullptr;

			m_IsOpen = false;

			m_OpenHotkey = ImGuiKey_None;
		}

		void Initialize(ImGuiIO* _io, ImGuiStyle* _style)
		{
			m_IO = _io;
			m_Style = _style;
		}

		void Open()
		{
			m_IsOpen = true;

			OnOpen();
		}

		void Render()
		{
			if (m_OpenHotkey != ImGuiKey_None && ImGui::IsKeyPressed(m_OpenHotkey))
			{
				if (m_IsOpen)
				{
					Close();
				}
				else
				{
					Open();
				}
			}

			if (m_IsOpen)
			{
				ImGui::SetNextWindowPos(m_Position, ImGuiCond_FirstUseEver);
				ImGui::SetNextWindowSize(m_Size, ImGuiCond_FirstUseEver);

				OnRender();
			}
		}

		void Close()
		{
			m_IsOpen = false;

			OnClose();
		}

		bool IsOpen() const
		{
			return m_IsOpen;
		}

		virtual void OnOpen() {}
		virtual void OnRender() {}
		virtual void OnClose() {}

	protected:
		ImGuiKey m_OpenHotkey;

		ImVec2 m_Position = ImVec2();
		ImVec2 m_Size = ImVec2();

		ImGuiIO* m_IO;
		ImGuiStyle* m_Style;

		bool m_IsOpen;
};