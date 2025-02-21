#pragma once



#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define APPLICATION_NAME "G.R.E Lab"

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)