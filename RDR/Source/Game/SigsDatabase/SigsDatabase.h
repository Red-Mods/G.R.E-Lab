#pragma once



// Classes & structs forward declaration
namespace rage
{
	struct sagPlayer;

	struct animAnimatorComponent;
	struct mvrMoverComponent;
}



// Functions definition
using f_UnlockAndShowCursor = bool(*)(bool _Toggle);

using f_animAnimatorComponent__GetCurrentAnimDuration = double(*)(rage::animAnimatorComponent* _This);
using f_mvrMoverComponent__EnableMoverCollision = void(*)(rage::mvrMoverComponent* _This, bool _Enable);



// Sigs database
class SigsDatabase
{
	public:
		static void Scan();

		// ioMouse
		static inline bool* s_DisableCursorAlteration;

		static inline f_UnlockAndShowCursor s_UnlockAndShowCursor;

		// UIInput
		static inline void* s_DisableAllInputs;

		// gohObjectManager
		static inline uintptr_t* s_GohBaseManagerSlots;

		// sagActorManager
		static inline uintptr_t* s_GeneralManagerSlots;

		// sagPlayerMgr
		static inline rage::sagPlayer** s_LocalPlayer;

		// animAnimatorComponent
		static inline f_animAnimatorComponent__GetCurrentAnimDuration s_animAnimatorComponent__GetCurrentAnimDuration;

		// mvrMoverComponent
		static inline f_mvrMoverComponent__EnableMoverCollision s_mvrMoverComponent__EnableMoverCollision;

	private:
		static inline bool s_HasBeenScanned = false;
};