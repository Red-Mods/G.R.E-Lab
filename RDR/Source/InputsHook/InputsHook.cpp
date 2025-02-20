#include <pch.h>



void InputsHook::Initialize(HWND _Window)
{
	s_Window = _Window;

	o_WindowProcedure = (WNDPROC)SetWindowLongPtr(s_Window, GWLP_WNDPROC, (LONG_PTR)n_WindowProcedure);

	if (o_WindowProcedure)
	{
		LOG_DEV_INFO("Hooked 'WindowProcedure'");
	}
	else
	{
		LOG_ERROR("Failed to hook 'WindowProcedure'");
	}
}



void InputsHook::Shutdown()
{
	if (o_WindowProcedure)
	{
		SetWindowLongPtr(s_Window, GWLP_WNDPROC, (LONG_PTR)o_WindowProcedure);

		LOG_DEV_INFO("Unhooked 'WindowProcedure'");
	}
}



LRESULT WINAPI InputsHook::n_WindowProcedure(HWND _Window, UINT _Message, WPARAM _WordParam, LPARAM _LongParam)
{
	ImGui_ImplWin32_WndProcHandler(_Window, _Message, _WordParam, _LongParam);

	return CallWindowProc(o_WindowProcedure, _Window, _Message, _WordParam, _LongParam);
}