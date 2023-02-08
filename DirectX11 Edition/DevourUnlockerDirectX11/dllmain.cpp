// dllmain.cpp : Defines the entry point for the DLL application.
#include "Includes.hpp" // Targeted D11 Application Window Title.
#include "CheatDevour/Font_Memory.hpp"
#include "ImGui/imgui_impl_win32.h"
#include "CheatDevour/Devour_Soft.hpp"
#pragma warning (disable : 6387) //Disabling This Warning 
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); //ImGui Window Process Handler
void CreateConsole() {
	AllocConsole();
	SetConsoleTitleA("DevourUnlocker by RaizyDaizy");
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	cout << "[DevourUnlocker] Welcome to My New Cheat By RaizyDaizy" << endl;
}
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.Fonts->AddFontFromMemoryTTF(nimbussans, sizeof(nimbussans), 18.F);
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer {0}; 
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView); //False Positive Warning DirectX 11 SDK(Idk Why)
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
			cout << "[DevourUnlocker] Successfully Getting D3D11 Device" << endl;
		}

		else 
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	ImGuiWindowFlags fl = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("DevourUnlocker by RaizyDaizy", 0, fl);
	ImGui::SetNextWindowSize(ImVec2(500, 500));
	ImGui::TextColored(ImVec4(145, 0, 0, 255), "Welcome to My Unlocker");
	if (ImGui::Button("Detach Console", ImVec2(162, 78))) 
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE); 
	}
	if (ImGui::Button("UNLOCK ALL ROBES", ImVec2(180, 125)))
	{
		InitUnlockedRobes();
	}
	if (ImGui::Button("UNLOCK ALL CHARACTERS", ImVec2(225, 125)))
	{
		InitUnlockedCharacters();
	}
	ImGui::End();
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(HMODULE hMod)
{
	bool init_hook = false;
	CreateConsole();
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
			cout << "[DevourUnlocker] Kiero Has Been Successfully Initializated" << endl;
		}
		else {
			cout << "[DevourUnlocker] Kiero is not Initializated" << endl;
			Sleep(4500);
			exit(122);
		}
		if (GetAsyncKeyState(VK_F5)) 
		{
			kiero::shutdown();
			FreeLibraryAndExitThread(hMod, 950);
		}
	} while (!init_hook);
	return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
		DisableThreadLibraryCalls(hModule);
		kiero::shutdown();
        break;
    }
    return TRUE;
}

