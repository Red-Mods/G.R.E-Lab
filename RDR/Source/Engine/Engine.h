#pragma once



namespace rage
{
	class Engine
	{
		public:
			static void Initialize();
			static void Shutdown();

		private:
			static inline uint32_t* s_FrameCount;

			static inline f_NativeHandler o_Wait;
			static void n_Wait(NativeCallContext* _NativeCallContext);
	};
}