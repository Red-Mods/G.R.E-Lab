#include <pch.h>



namespace rage
{
	void UIInput::__LoadSigs()
	{
		Pattern("rage::UIInput::sm_DisableAllInputs", "48 83 BB ? ? ? ? ? 74 5A").Scan([](const Pattern& _This)
		{
			s_DisableAllInputs = _This.Sub(1).As<decltype(s_DisableAllInputs)>();
		});
	}



	void UIInput::DisableAllInputs(bool _Disable)
	{
		if (!s_DisableAllInputs)
			return;

		Memory::Write(s_DisableAllInputs, _Disable);
	}
}