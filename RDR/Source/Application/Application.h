#pragma once



class Application : public Singleton<Application>
{
	public:
		void Initialize(HMODULE _Module);
		void Shutdown();

	private:
		static inline HMODULE s_Module;

		static void __MainThread(Application* _Self);
};