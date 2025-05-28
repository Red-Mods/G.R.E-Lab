#include <pch.h>



namespace rage
{
	bool ioKeyboard::KeyDown(unsigned int _KeyCode)
	{
		if (!SigsDatabase::s_KeyDown)
			return false;

		return SigsDatabase::s_KeyDown(_KeyCode);
	}



	bool ioKeyboard::KeyPressed(unsigned int _KeyCode)
	{
		if (!SigsDatabase::s_KeyPressed)
			return false;

		return SigsDatabase::s_KeyPressed(_KeyCode);
	}



	bool ioKeyboard::KeyReleased(unsigned int _KeyCode)
	{
		if (!SigsDatabase::s_KeyReleased)
			return false;

		return SigsDatabase::s_KeyReleased(_KeyCode);
	}
}