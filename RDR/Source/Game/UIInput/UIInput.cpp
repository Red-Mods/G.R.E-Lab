#include <pch.h>



namespace rage
{
	void UIInput::DisableAllInputs(bool _Disable)
	{
		if (!SigsDatabase::s_DisableAllInputs)
			return;

		Memory::Write(SigsDatabase::s_DisableAllInputs, _Disable);
	}
}