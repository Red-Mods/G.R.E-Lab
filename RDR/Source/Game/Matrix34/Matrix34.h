#pragma once



namespace rage
{
	struct Matrix34
	{
		alignas(8) Vector3 Forward;                  // 0x0000
		alignas(8) Vector3 Up;                       // 0x0010
		alignas(8) Vector3 Right;                    // 0x0020
		alignas(8) Vector3 Position;                 // 0x0030
	};
}