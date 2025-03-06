#pragma once


// Classes & structs forward declaration
namespace rage
{
	struct mvrMoverComponent;
}



// Functions definition
using f_mvrMoverComponent__EnableMoverCollision = void(*)(rage::mvrMoverComponent* _This, bool _Enable);



// Sigs database
class SigsDatabase
{
	public:
		static void Scan();

		static inline f_mvrMoverComponent__EnableMoverCollision s_mvrMoverComponent__EnableMoverCollision;

	private:
		static inline bool s_HasBeenScanned = false;
};