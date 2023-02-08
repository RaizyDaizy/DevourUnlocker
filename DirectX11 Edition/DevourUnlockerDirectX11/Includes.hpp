#pragma once
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <d3d11.h>
#include <dxgi.h>
#include <MinHook.h>
#include "ImGui/imconfig.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imstb_rectpack.h"
#include "ImGui/imstb_textedit.h"
#include "ImGui/imstb_truetype.h"
#include "kiero/kiero.h"
#pragma comment (lib, "d3d11.lib")
typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;
using namespace std;
