#include <pch.h>



namespace rage
{
	void scrThread::Initialize()
	{
		Pattern("FrameCount", "FF 05 ? ? ? ? 48 8D 15 ? ? ? ?").Scan([](const Pattern& _This)
		{
			s_FrameCount = _This.Add(2).Rip().As<decltype(s_FrameCount)>();
		});
		
		Hook::Create("rage::scrThread::Wait", NativesInvoker::GetNativeHandler(0x7715C03B), &n_Wait, &o_Wait);

		LOG_INFO("Successfully initialized script engine");
	}



	void scrThread::Shutdown()
	{
		Hook::Remove(NativesInvoker::GetNativeHandler(0x7715C03B));

		LOG_INFO("Unloaded script engine");
	}



	void scrThread::n_Wait(NativeCallContext* _NativeCallContext)
	{
		static uint32_t lastFrameCount = 0;
		uint32_t frameCount = *s_FrameCount;

		if (lastFrameCount != frameCount)
		{
			const char* scriptName = Invoke<0x0BC52445, const char*>();

			if (strstr(scriptName, "content/main"))
			{
				FibersPool::Get()->DoRun(RunFilter_Main);
			}

			lastFrameCount = frameCount;
		}

		FibersPool::Get()->DoGarbageCollection();
		
		return o_Wait(_NativeCallContext);
	}
}