#pragma once
#include "../Includes.hpp" //Includes for Init Minhook :D

namespace Offsets_Devour 
{
	uintptr_t gameasm = (uintptr_t)GetModuleHandleA("GameAssembly.dll"); //GameAssembly REAL Address
	uintptr_t isrobeunlocked = 0x74B0B0;
	uintptr_t ischaracterunlocked = 0x749D60;
}

bool(__fastcall* IsRobeUnlocked_o)(DWORD*, const char*, DWORD*);

bool __stdcall IsRobeUnlocked_h(DWORD* __this, const char* robe, DWORD* method) 
{
		char name[256];
		wcstombs(name, (wchar_t*)(robe)+0xA, sizeof(name));
		cout << "[DevourUnlocker] Robe is Unlocked Succesfully... Name of Unlocked Robes: " << name << "\n" << endl;
		return true;
}

bool(__fastcall* IsCharacterUnlocked_o)(DWORD*, const char*, DWORD*);

bool __stdcall IsCharacterUnlocked_h(DWORD* __this, const char* prefab, DWORD* method) 
{
		char pref_name[256];
		wcstombs(pref_name, (wchar_t*)(prefab)+0xA, sizeof(pref_name));
		cout << "[DevourUnlocker] Characters is Unlocked Successfully... Name of Unlocked Characters: " << pref_name << "\n" << endl;
		return true;

}

void InitUnlockedRobes() 
{
	MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets_Devour::gameasm + Offsets_Devour::isrobeunlocked), &IsRobeUnlocked_h, (LPVOID*)&IsRobeUnlocked_o);
	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets_Devour::gameasm + Offsets_Devour::isrobeunlocked));
}
void InitUnlockedCharacters() {
	MH_CreateHook(reinterpret_cast<LPVOID*>(Offsets_Devour::gameasm + Offsets_Devour::ischaracterunlocked), &IsCharacterUnlocked_h, (LPVOID*)&IsCharacterUnlocked_o);
	MH_EnableHook(reinterpret_cast<LPVOID*>(Offsets_Devour::gameasm + Offsets_Devour::ischaracterunlocked));

}