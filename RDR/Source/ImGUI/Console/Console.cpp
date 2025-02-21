#include "pch.h"



Console::Console()
{
	m_Position = ImVec2(500.0f, 200.0f);
	m_Size = ImVec2(800.0f, 600.0f);

	m_ScrollToLastLine = false;
	m_FocusTextInput = true;

	Log::RegisterOnLogReceived([=]
	{
		m_ScrollToLastLine = true;
	});
}



void Console::OnOpen()
{
	m_FocusTextInput = true;
}



void Console::Render()
{
	ImVec2 resolution = Utils::GetGameWindowResolution();

	Super::Render();

	if (!IsOpen())
		return;

	if (ImGui::Begin(APPLICATION_NAME " | Console##ConsoleWindow", &m_IsOpen, ImGuiWindowFlags_NoScrollbar))
	{
		if (ImGui::BeginChild("##ConsoleContent", ImVec2(0, m_Size.y - 70.0f), ImGuiChildFlags_Border))
		{
			const auto& lines = Log::GetCachedLogs();

			for (int i = 0; i < MAX_CACHED_LOGS; i++)
			{
				const LogLine line = lines[i];

				if (line.Tag.empty())
					continue;

				if (line.Text.empty())
					continue;

				m_PreviousAlpha[i] = Math<float>::Lerp(m_PreviousAlpha[i], 1.0f, m_IO->DeltaTime * 3.0f);

				ImVec4 color = ImVec4(line.Color.R, line.Color.G, line.Color.B, m_PreviousAlpha[i] * line.Color.A);

				ImGui::PushStyleColor(ImGuiCol_Button, color);
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
				ImGui::PushID(i);
				ImGui::Button(line.Tag.c_str());
				ImGui::PopID();
				ImGui::PopStyleColor(3);
				ImGui::SameLine();

				ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, m_PreviousAlpha[i] * 0.8f), line.Text.c_str());
			}

			if (m_ScrollToLastLine)
			{
				m_ScrollToLastLine = false;

				ImGui::SetScrollHereY();
			}

			ImGui::EndChild();
		}

		if (m_FocusTextInput)
		{
			m_FocusTextInput = false;

			ImGui::SetKeyboardFocusHere();
		}

		static char buffer[CHAR_MAX];
		if (ImGui::InputText("##ConsoleInput", buffer, CHAR_MAX, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackHistory, &LastCommandCallback))
		{
			const std::string input = Utils::ToLower(buffer);

			if (input.length() > 0)
			{
				Commands::Get()->HandleCommand(input);

				s_SentCommands.push_back(input);

				s_CommandPosition = s_SentCommands.size() - 1;

				memset(buffer, 0, CHAR_MAX);

				m_FocusTextInput = true;
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Open Logs"))
		{
			ShellExecuteA(NULL, "open", APPLICATION_NAME ".log", NULL, NULL, SW_SHOWDEFAULT);
		}

		ImGui::End();
	}
}



int Console::LastCommandCallback(ImGuiInputTextCallbackData* _Data)
{
	if (s_SentCommands.size() > 0)
	{
		// Remove text.
		_Data->DeleteChars(0, _Data->BufTextLen);

		if (_Data->EventKey == ImGuiKey_UpArrow)
		{
			if (s_CommandPosition > 0)
				s_CommandPosition--;
		}
		else if (_Data->EventKey == ImGuiKey_DownArrow)
		{
			if (s_CommandPosition < (s_SentCommands.size() - 1))
				s_CommandPosition++;
		}

		// Insert new text.
		_Data->InsertChars(0, s_SentCommands.at(s_CommandPosition).c_str());
	}

	return 0;
}