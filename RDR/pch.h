#ifndef PCH_H
#define PCH_H



// Windows / C headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <psapi.h>
#include <shellapi.h>
#include <map>
#include <functional>
#include <dxgi1_4.h>
#include <d3d12.h>
#include <chrono>
#include <string>
#include <queue>
#include <array>
#include <mutex>
#include <future>
#include <filesystem>
#include <set>



// Included headers
#include <resource.h>

#include <MinHook/MinHook.h>

#include <ImGui/imconfig.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui_impl_dx12.h>

#include <Shared/Utils.hpp>



// Application headers
#include "Headers/Singleton.h"
#include "Headers/Defines.h"
#include "Headers/Utils.h"
#include "Headers/Math.h"
#include "Headers/EventsHandler.h"
#include "Headers/Memory.h"

#include "Source/Log/Log.h"

#include "Headers/Hook.h"
#include "Headers/VMT.h"
#include "Headers/Pattern.h"

#include "Source/InputsHook/InputsHook.h"

#include "Source/DirectXHook/DirectXHook.h"

#include "Source/NativesInvoker/NativesInvoker.h"

#include "Source/Game/ioMouse/ioMouse.h"
#include "Source/Game/UIInput/UIInput.h"

#include "Source/Game/gohObjectManager/gohObjectManager.h"

#include "Source/Game/sagGuid/sagGuid.h"
#include "Source/Game/sagActorManager/sagActorManager.h"
#include "Source/Game/sagPlayer/sagPlayer.h"
#include "Source/Game/sagPlayerMgr/sagPlayerMgr.h"

#include "Source/Engine/Engine.h"

#include "Source/ImGUI/ImGUIWindow.h"

#include "Source/ImGUI/Home/Home.h"

#include "Source/ImGUI/Console/Commands/Commands.h"
#include "Source/ImGUI/Console/Console.h"

#include "Source/ImGUI/ImGUI.h"

#include "Source/Application/Application.h"



#endif