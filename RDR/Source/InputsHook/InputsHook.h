#pragma once



extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND _Window, UINT _Message, WPARAM _WordParam, LPARAM _LongParam);



class InputsHook
{
	public:
		static void Initialize(HWND _Window);
		static void Shutdown();

	private:
		static inline HWND s_Window;

		static inline WNDPROC o_WindowProcedure;
		static LRESULT WINAPI n_WindowProcedure(HWND _Window, UINT _Message, WPARAM _WordParam, LPARAM _LongParam);
};