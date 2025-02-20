#pragma once



#define APPLICATION_NAME "G.R.E Lab"
#define GAME_WINDOW_CLASS_NAME "Red Dead Redemption"

#define MAX_CACHED_LOGS 0x100

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

#define IS_USING_VMT false
#define D3D12_NUM_BACK_BUFFERS 3