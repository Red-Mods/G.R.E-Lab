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
						m_IsOpen = false;

						// Allowing back cursor alteration will make the game automatically
						// restore the correct cursor state
						// Example: If the game is currently paused, the mouse will be unlocked and visible otherwise it will stay locked and invisible
						rage::ioMouse::DisableCursorAlteration(false);

						ImGui::SetWindowFocus(nullptr);

						OnClose();
					}
					else
					{
						m_IsOpen = true;

						// Unlock and show the mouse cursor on screen
						rage::ioMouse::UnlockAndShowCursor(true);
						rage::ioMouse::DisableCursorAlteration(true);

						OnOpen();
					}

					// Enable/Disable UI inputs
					rage::UIInput::DisableAllInputs(m_IsOpen);

					// Enable/Disable player movements & camera movements
					rage::sagPlayerMgr::GetLocalPlayer()->DisablePlayerControl(m_IsOpen);
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

				// Disable player movements & camera movements
				rage::sagPlayerMgr::GetLocalPlayer()->DisablePlayerControl(true);
			}
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

	private:
		static inline size_t s_WindowsId = 0;

		bool m_IsOpen;

		bool m_HasBeenInitialized;
};