#include <pch.h>



bool DirectXHook::Initialize()
{
    WNDCLASSEXW windowClass{};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = DefWindowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandle(NULL);
    windowClass.hIcon = NULL;
    windowClass.hCursor = NULL;
    windowClass.hbrBackground = NULL;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = L"RDR";
    windowClass.hIconSm = NULL;

    RegisterClassExW(&windowClass);

    HWND window = CreateWindowW(windowClass.lpszClassName, L"RDR", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

    HMODULE libDXGI = GetModuleHandleW(L"dxgi.dll");
    HMODULE libD3D12 = GetModuleHandleW(L"d3d12.dll");

    if (!libDXGI || !libD3D12)
    {
        DestroyWindow(window);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

        LOG_ERROR("[DirectXHook] Failed to load libraries");

        return false;
    }

    void* CreateDXGIFactory1 = GetProcAddress(libDXGI, "CreateDXGIFactory1");

    if (!CreateDXGIFactory1)
    {
        DestroyWindow(window);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

        LOG_ERROR("[DirectXHook] Failed to get CreateDXGIFactory1");

        return false;
    }

    IDXGIFactory2* factory;
    if (((HRESULT(__stdcall*)(const IID&, void**))(CreateDXGIFactory1))(IID_PPV_ARGS(&factory)) < 0)
    {
        DestroyWindow(window);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

        LOG_ERROR("[DirectXHook] Failed to get IDXGIFactory2");

        return false;
    }

    IDXGIAdapter* adapter;
    if (factory->EnumAdapters(0, &adapter) == DXGI_ERROR_NOT_FOUND)
    {
        DestroyWindow(window);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

        LOG_ERROR("[DirectXHook] Failed to enum IDXGIAdapter");

        return false;
    }

    void* D3D12CreateDevice = GetProcAddress(libD3D12, "D3D12CreateDevice");

    if (!D3D12CreateDevice)
    {
        DestroyWindow(window);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

        LOG_ERROR("[DirectXHook] Failed to get D3D12CreateDevice");

        return false;
    }

    ID3D12Device* device;
    if (((HRESULT(__stdcall*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**))(D3D12CreateDevice))(adapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device)) < 0)
    {
        DestroyWindow(window);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

        LOG_ERROR("[DirectXHook] Failed to use D3D12CreateDevice");

        return false;
    }

    D3D12_COMMAND_QUEUE_DESC desc{};
    ID3D12CommandQueue* commandQueue;
    if (device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue)) != S_OK)
    {
        DestroyWindow(window);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

        LOG_ERROR("[DirectXHook] Failed to create ID3D12CommandQueue");

        return false;
    }

    DXGI_SWAP_CHAIN_DESC1 sd{};
    sd.BufferCount = D3D12_NUM_BACK_BUFFERS;
    sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.SampleDesc.Count = 1;
    sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    IDXGISwapChain1* swapChain1;
    if (factory->CreateSwapChainForHwnd(commandQueue, window, &sd, NULL, NULL, &swapChain1) != S_OK)
    {
        DestroyWindow(window);
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

        LOG_ERROR("[DirectXHook] Failed to create IDXGISwapChain1");

        return false;
    }

    for (size_t i = 0; i < 1000; i++)
    {
        ID3D12CommandQueue* temp = *reinterpret_cast<ID3D12CommandQueue**>(swapChain1 + i);

        if (temp == commandQueue)
        {
            m_CommandQueueOffset = i;

            break;
        }
    }

    #if IS_USING_VMT

    m_HookFactory = *reinterpret_cast<void**>(factory);
    m_HookFactory.Hook(15, &n_CreateSwapChainForHwnd, &o_CreateSwapChainForHwnd);

    m_HookSwapChain = *reinterpret_cast<void**>(swapChain1);
    m_HookSwapChain.Hook(8, &n_Present, &o_Present);
    m_HookSwapChain.Hook(13, &n_ResizeBuffers, &o_ResizeBuffers);

    #else

    m_FactoryTable = *reinterpret_cast<void***>(factory);
    m_SwapChain1Table = *reinterpret_cast<void***>(swapChain1);

    Hook::Create("CreateSwapChainForHwnd", m_FactoryTable[15], &n_CreateSwapChainForHwnd, &o_CreateSwapChainForHwnd);
    Hook::Create("ResizeBuffers", m_SwapChain1Table[13], &n_ResizeBuffers, &o_ResizeBuffers);
    Hook::Create("Present", m_SwapChain1Table[8], &n_Present, &o_Present);

    #endif

    SafeRelease(&swapChain1);
    SafeRelease(&device);
    SafeRelease(&factory);
    SafeRelease(&commandQueue);
    SafeRelease(&adapter);

    CloseHandle(libDXGI);
    CloseHandle(libD3D12);

    DestroyWindow(window);
    UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

    LOG_INFO("DirectXHook initialized");

    return true;
}



void DirectXHook::CreateDevices(IDXGISwapChain3* _SwapChain)
{
    if (FAILED(_SwapChain->GetDevice(IID_PPV_ARGS(&m_Device))))
    {
        LOG_ERROR("Failed to get device");

        return;
    }

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc{};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        desc.NumDescriptors = D3D12_NUM_BACK_BUFFERS;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        desc.NodeMask = 1;
 
        if (m_Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_RtvDescriptorHeap)) != S_OK)
        {
            LOG_ERROR("Failed to create rtv descriptor heap");

            return;
        }

        SIZE_T rtvDescriptorSize = m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = m_RtvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();

        for (UINT i = 0; i < D3D12_NUM_BACK_BUFFERS; i++)
        {
            m_MainRenderTargetDescriptor[i] = rtvHandle;

            rtvHandle.ptr += rtvDescriptorSize;
        }
    }

    {
        D3D12_DESCRIPTOR_HEAP_DESC desc{};
        desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        desc.NumDescriptors = 2;
        desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        if (m_Device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_SrvDescriptorHeap)) != S_OK)
        {
            LOG_ERROR("Failed to create srv descriptor heap");

            return;
        }
    }

    for (UINT i = 0; i < D3D12_NUM_BACK_BUFFERS; i++)
    {
        if (m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_CommandAllocators[i])) != S_OK)
        {
            LOG_ERROR("Failed to create command allocator at back buffer index %u", i);

            return;
        }
    }

    if (m_Device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_CommandAllocators[0], NULL, IID_PPV_ARGS(&m_GraphicsCommandList)) != S_OK || m_GraphicsCommandList->Close() != S_OK)
    {
        LOG_ERROR("Failed to get command list !");

        return;
    }

    LOG_DEV_INFO("Created devices");
}



void DirectXHook::CleanupDevices()
{
    SafeRelease(&m_Device);
    SafeRelease(&m_RtvDescriptorHeap);
    SafeRelease(&m_SrvDescriptorHeap);

    for (UINT i = 0; i < D3D12_NUM_BACK_BUFFERS; ++i)
    {
        SafeRelease(&m_CommandAllocators[i]);
    }

    SafeRelease(&m_GraphicsCommandList);

    LOG_DEV_INFO("Cleaned devices");
}



void DirectXHook::CreateRenderTarget(IDXGISwapChain* _SwapChain)
{
    for (UINT i = 0; i < D3D12_NUM_BACK_BUFFERS; i++)
    {
        ID3D12Resource* backBuffer;

        if (FAILED(_SwapChain->GetBuffer(i, IID_PPV_ARGS(&backBuffer))))
            continue;

        DXGI_SWAP_CHAIN_DESC swapChainDesc;
        if (FAILED(_SwapChain->GetDesc(&swapChainDesc)))
            continue;

        D3D12_RENDER_TARGET_VIEW_DESC renderTargetDesc{};
        renderTargetDesc.Format = swapChainDesc.BufferDesc.Format;
        renderTargetDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

        m_RenderTargetColorFormat = renderTargetDesc.Format;

        m_IsUsingHDR = renderTargetDesc.Format == DXGI_FORMAT_R16G16B16A16_FLOAT ||
            renderTargetDesc.Format == DXGI_FORMAT_R32G32B32A32_FLOAT ||
            renderTargetDesc.Format == DXGI_FORMAT_R11G11B10_FLOAT ||
            renderTargetDesc.Format == DXGI_FORMAT_R10G10B10A2_UNORM ||
            renderTargetDesc.Format == DXGI_FORMAT_R16G16_FLOAT ||
            renderTargetDesc.Format == DXGI_FORMAT_R16_FLOAT ||
            renderTargetDesc.Format == DXGI_FORMAT_R16G16B16A16_TYPELESS ||
            renderTargetDesc.Format == DXGI_FORMAT_R32G32B32A32_TYPELESS ||
            renderTargetDesc.Format == DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM ||
            renderTargetDesc.Format == DXGI_FORMAT_R9G9B9E5_SHAREDEXP;

        m_Device->CreateRenderTargetView(backBuffer, &renderTargetDesc, m_MainRenderTargetDescriptor[i]);

        m_MainRenderTargetResource[i] = backBuffer;
    }

    LOG_DEV_INFO("Created render target");
}



void DirectXHook::CleanupRenderTarget()
{
    for (UINT i = 0; i < D3D12_NUM_BACK_BUFFERS; i++)
    {
        SafeRelease(&m_MainRenderTargetResource[i]);
    }

    m_IsRenderTargetInitialized = false;

    LOG_DEV_INFO("Cleaned render target");
}



void DirectXHook::DoRun(IDXGISwapChain3* _SwapChain)
{
    if (!m_IsInitialized)
    {
        CreateDevices(_SwapChain);

        m_IsInitialized = true;
    }

    if (!m_IsRenderTargetInitialized)
    {
        CreateRenderTarget(_SwapChain);

        ExecuteEvent(Event_OnInitialize);

        m_IsRenderTargetInitialized = true;
    }

    ID3D12CommandQueue* commandQueue = *reinterpret_cast<ID3D12CommandQueue**>(_SwapChain + m_CommandQueueOffset);

    if (!commandQueue)
    {
        Reset();

        return;
    }

    UINT backBufferIndex = _SwapChain->GetCurrentBackBufferIndex();

    ID3D12CommandAllocator* commandAllocator = m_CommandAllocators[backBufferIndex];

    commandAllocator->Reset();

    D3D12_RESOURCE_BARRIER barrier{};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = m_MainRenderTargetResource[backBufferIndex];
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

    m_GraphicsCommandList->Reset(commandAllocator, NULL);
    m_GraphicsCommandList->ResourceBarrier(1, &barrier);

    m_GraphicsCommandList->OMSetRenderTargets(1, &m_MainRenderTargetDescriptor[backBufferIndex], FALSE, NULL);
    m_GraphicsCommandList->SetDescriptorHeaps(1, &m_SrvDescriptorHeap);

    ExecuteEvent(Event_OnRender);

    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

    m_GraphicsCommandList->ResourceBarrier(1, &barrier);
    m_GraphicsCommandList->Close();

    commandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&m_GraphicsCommandList));
}



void DirectXHook::Reset()
{
    ExecuteEvent(Event_OnReset);

    CleanupRenderTarget();
}



void DirectXHook::Shutdown()
{
    #if IS_USING_VMT

    m_HookSwapChain.Unhook(8);
    m_HookSwapChain.Unhook(13);
    m_HookFactory.Unhook(15);

    #else

    Hook::Remove(m_SwapChain1Table[8]);
    Hook::Remove(m_SwapChain1Table[13]);
    Hook::Remove(m_FactoryTable[15]);

    #endif

    CleanupRenderTarget();

    CleanupDevices();

    ExecuteEvent(Event_OnShutdown);

    LOG_INFO("DirectXHook has been shutdown");
}



HRESULT WINAPI DirectXHook::n_CreateSwapChainForHwnd(IDXGIFactory* _Factory, IUnknown* _Device, HWND _Window, const DXGI_SWAP_CHAIN_DESC1* _Desc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* _FullscreenDesc, IDXGIOutput* _RestrictToOutput, IDXGISwapChain1** _SwapChain)
{
    DirectXHook::Get()->Reset();

    return o_CreateSwapChainForHwnd(_Factory, _Device, _Window, _Desc, _FullscreenDesc, _RestrictToOutput, _SwapChain);
}



HRESULT WINAPI DirectXHook::n_Present(IDXGISwapChain3* _SwapChain, UINT _SyncInterval, UINT _Flags)
{
    DirectXHook::Get()->DoRun(_SwapChain);

    return o_Present(_SwapChain, _SyncInterval, _Flags);
}



HRESULT WINAPI DirectXHook::n_ResizeBuffers(IDXGISwapChain3* _SwapChain, UINT _BufferCount, UINT _Width, UINT _Height, DXGI_FORMAT _NewFormat, UINT _SwapChainFlags)
{
    DirectXHook::Get()->Reset();

    return o_ResizeBuffers(_SwapChain, _BufferCount, _Width, _Height, _NewFormat, _SwapChainFlags);
}