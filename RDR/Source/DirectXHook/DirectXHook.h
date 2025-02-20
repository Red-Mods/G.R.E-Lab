#pragma once



template<class I>
inline void SafeRelease(I** _InterfaceToRelease)
{
	if (*_InterfaceToRelease != nullptr)
	{
		(*_InterfaceToRelease)->Release();
		(*_InterfaceToRelease) = nullptr;
	}
}



using f_CreateSwapChainForHwnd = HRESULT(WINAPI*)(IDXGIFactory* _Factory, IUnknown* _Device, HWND _Wnd, const DXGI_SWAP_CHAIN_DESC1* _Desc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* _FullscreenDesc, IDXGIOutput* _RestrictToOutput, IDXGISwapChain1** _SwapChain);
using f_ResizeBuffers = HRESULT(WINAPI*)(IDXGISwapChain3* _SwapChain, UINT _BufferCount, UINT _Width, UINT _Height, DXGI_FORMAT _NewFormat, UINT _SwapChainFlags);
using f_Present = HRESULT(WINAPI*)(IDXGISwapChain3* _SwapChain, UINT _SyncInterval, UINT _Flags);



class DirectXHook : public Singleton<DirectXHook>, public EventsHandler
{
	public:
		bool Initialize();
		void Shutdown();

		bool IsInitialized() const
		{
			return m_IsInitialized;
		}

		ID3D12Device* GetDevice() const
		{
			return m_Device;
		}

		ID3D12DescriptorHeap* GetSrvDescriptorHeap() const
		{
			return m_SrvDescriptorHeap;
		}

		ID3D12GraphicsCommandList* GetGraphicsCommandList() const
		{
			return m_GraphicsCommandList;
		}

		DXGI_FORMAT GetRenderTargetColorFormat() const
		{
			return m_RenderTargetColorFormat;
		}

		bool IsUsingHDR() const
		{
			return m_IsUsingHDR;
		}

	private:
		bool m_IsInitialized = false;
		bool m_IsRenderTargetInitialized = false;
		DXGI_FORMAT m_RenderTargetColorFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
		bool m_IsUsingHDR = false;

		uintptr_t m_CommandQueueOffset = 0;

		VMT m_HookFactory;
		VMT m_HookSwapChain;

		void** m_FactoryTable;
		void** m_SwapChain1Table;

		ID3D12Device* m_Device = nullptr;

		ID3D12DescriptorHeap* m_RtvDescriptorHeap = nullptr;
		ID3D12DescriptorHeap* m_SrvDescriptorHeap = nullptr;

		ID3D12CommandAllocator* m_CommandAllocators[D3D12_NUM_BACK_BUFFERS] = {};
		ID3D12GraphicsCommandList* m_GraphicsCommandList = nullptr;

		ID3D12Resource* m_MainRenderTargetResource[D3D12_NUM_BACK_BUFFERS] = {};
		D3D12_CPU_DESCRIPTOR_HANDLE m_MainRenderTargetDescriptor[D3D12_NUM_BACK_BUFFERS] = {};

		void CreateDevices(IDXGISwapChain3* _SwapChain);
		void CleanupDevices();

		void CreateRenderTarget(IDXGISwapChain* _SwapChain);
		void CleanupRenderTarget();

		void DoRun(IDXGISwapChain3* _SwapChain);

		void Reset();

		static inline f_CreateSwapChainForHwnd o_CreateSwapChainForHwnd;
		static HRESULT WINAPI n_CreateSwapChainForHwnd(IDXGIFactory* _Factory, IUnknown* _Device, HWND _Window, const DXGI_SWAP_CHAIN_DESC1* _Desc, const DXGI_SWAP_CHAIN_FULLSCREEN_DESC* _FullscreenDesc, IDXGIOutput* _RestrictToOutput, IDXGISwapChain1** _SwapChain);

		static inline f_Present o_Present;
		static HRESULT WINAPI n_Present(IDXGISwapChain3* _SwapChain, UINT _SyncInterval, UINT _Flags);

		static inline f_ResizeBuffers o_ResizeBuffers;
		static HRESULT WINAPI n_ResizeBuffers(IDXGISwapChain3* _SwapChain, UINT _BufferCount, UINT _Width, UINT _Height, DXGI_FORMAT _NewFormat, UINT _SwapChainFlags);
};