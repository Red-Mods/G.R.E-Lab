#pragma once



class Console : public ImGUIWindow
{
	public:
		Console();

		virtual void OnOpen() override;
		virtual void OnRender() override;

	private:
		bool m_ScrollToLastLine;
		bool m_FocusTextInput;

		std::array<float, MAX_CACHED_LOGS> m_PreviousAlpha = {};

		static inline std::vector<std::string> s_SentCommands = {};
		static inline size_t s_CommandPosition = 0;

		static int LastCommandCallback(ImGuiInputTextCallbackData* _Data);
};