#pragma once



class ImGUIWindow
{
	public:
		using Super = ImGUIWindow;

		ImGUIWindow()
		{
			m_Id = s_WindowsId++;

			m_IO = nullptr;
			m_Style = nullptr;

			m_IsOpen = false;

			m_OpenHotkey = ImGuiKey_None;

			m_HasBeenInitialized = false;
		}

		void Initialize(ImGuiIO* _io, ImGuiStyle* _style)
		{
			m_IO = _io;
			m_Style = _style;
		}

		virtual void OnOpen() {}
		virtual void OnClose() {}

		virtual void Render()
		{
			if (m_OpenHotkey != ImGuiKey_None)
			{
				if (ImGui::IsKeyPressed(m_OpenHotkey))
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
			}

			if (m_IsOpen)
			{
				if (!m_HasBeenInitialized)
				{
					m_HasBeenInitialized = true;

					ImGui::SetNextWindowPos(m_Position);

					if (m_Size.x != 0.0f || m_Size.y != 0.0f)
						ImGui::SetNextWindowSize(m_Size);
				}
			}
		}

		void Open()
		{
			m_IsOpen = true;

			OnOpen();
		}

		void Close()
		{
			m_IsOpen = false;

			OnClose();
		}

		size_t GetId() const
		{
			return m_Id;
		}

		bool IsOpen() const
		{
			return m_IsOpen;
		}

	protected:
		size_t m_Id;

		ImGuiKey m_OpenHotkey;

		ImVec2 m_Position = ImVec2();
		ImVec2 m_Size = ImVec2();

		ImGuiIO* m_IO;
		ImGuiStyle* m_Style;

		bool m_IsOpen;

	private:
		static inline size_t s_WindowsId = 0;

		bool m_HasBeenInitialized;
};