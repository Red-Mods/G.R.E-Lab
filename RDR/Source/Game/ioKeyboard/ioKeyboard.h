#pragma once



namespace rage
{
	class ioKeyboard
	{
		public:
			static bool KeyDown(unsigned int _KeyCode);
			static bool KeyPressed(unsigned int _KeyCode);
			static bool KeyReleased(unsigned int _KeyCode);
	};
}