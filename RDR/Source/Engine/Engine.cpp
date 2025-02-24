#include <pch.h>



namespace rage
{
	void Engine::Initialize()
	{
		Pattern("FrameCount", "FF 05 ? ? ? ? 48 8D 15 ? ? ? ?").Scan([](const Pattern& _This)
		{
			s_FrameCount = _This.Add(2).Rip().As<decltype(s_FrameCount)>();
		});
		
		Hook::Create("Wait", NativesInvoker::GetNativeHandler(0x7715C03B), &n_Wait, &o_Wait);

		LOG_INFO("Successfully initialized script engine");
	}



	void Engine::Shutdown()
	{
		Hook::Remove(NativesInvoker::GetNativeHandler(0x7715C03B));

		LOG_INFO("Unloaded script engine");
	}



	void Engine::n_Wait(NativeCallContext* _NativeCallContext)
	{
		static uint32_t lastFrameCount = 0;
		uint32_t frameCount = *s_FrameCount;

		if (lastFrameCount != frameCount)
		{
			const char* scriptName = Invoke<0x0BC52445, const char*>();

			if (strstr(scriptName, "content/main"))
			{

			}

			lastFrameCount = frameCount;
		}
		
		return o_Wait(_NativeCallContext);
	}
}