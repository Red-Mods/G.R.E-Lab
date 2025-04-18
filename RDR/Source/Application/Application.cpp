#include <pch.h>



void Application::Initialize(HMODULE _Module)
{
	// Create console.
	AllocConsole();

	// Set console name.
	SetConsoleTitleA(APPLICATION_NAME);

	// Disable console selection mode.
	HANDLE consoleInput = GetStdHandle(STD_INPUT_HANDLE);

	DWORD previousMode;
	if (GetConsoleMode(consoleInput, &previousMode))
	{
		SetConsoleMode(consoleInput, ENABLE_EXTENDED_FLAGS | (previousMode & ~ENABLE_QUICK_EDIT_MODE));
	}

	LOG_INIT("Initializing %s...", APPLICATION_NAME);

	s_Module = _Module;

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)__MainThread, this, NULL, NULL);
}



void Application::__MainThread(Application* _Self)
{
	Pattern("SkipLogos", "E8 ? ? ? ? 48 39 3D ? ? ? ? 0F 85 ? ? ? ? E8 ? ? ? ? 8B 0D ? ? ? ?").Scan([](Pattern _This)
	{
		_This.Add(8).Rip().As<bool&>() = true;
	});

	LOG_INFO("Skipped intro logos");

	LOG_INFO("Waiting for game window...");

	HWND gameWindow = nullptr;

	do
	{
		gameWindow = FindWindowA(GAME_WINDOW_CLASS_NAME, NULL);

		Sleep(1);
	}
	while (!gameWindow);

	Sleep(500);

	const auto& directXHook = DirectXHook::Get();

	directXHook->RegisterEvent(Event_OnInitialize, [=]()
	{
		ImGUI::Get()->Initialize(gameWindow, directXHook->GetDevice(), directXHook->GetSrvDescriptorHeap(), directXHook->GetRenderTargetColorFormat());
	});

	directXHook->RegisterEvent(Event_OnRender, [=]()
	{
		ImGUI::Get()->Render(directXHook->GetGraphicsCommandList());
	});

	directXHook->RegisterEvent(Event_OnReset, []
	{
		ImGUI::Get()->Shutdown();
	});

	directXHook->RegisterEvent(Event_OnShutdown, []
	{
		ImGUI::Get()->Shutdown(true);
	});

	directXHook->Initialize();

	InputsHook::Initialize(gameWindow);

	SigsDatabase::Scan();

	rage::NativesInvoker::Initialize();

	rage::scrThread::Initialize();

	FibersPool::Get()->Add<Features>(RunFilter_Main);

	while (true)
	{
		if (GetAsyncKeyState(VK_DELETE))
			break;

		Sleep(10);
	}

	FreeLibraryAndExitThread(_Self->s_Module, EXIT_SUCCESS);
}



void Application::Shutdown()
{
	LOG_INFO("Unloading %s...", APPLICATION_NAME);

	InputsHook::Shutdown();

	DirectXHook::Get()->Shutdown();

	rage::scrThread::Shutdown();

	MH_Uninitialize();

	FreeConsole();
}