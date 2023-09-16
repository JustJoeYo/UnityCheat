#pragma once

class Hooks
{
private:
	CREATE(void, AddRecoil, (float, float, float))
	CREATE(float, CalculateSpread, ())
	CREATE(float, CalculateSpreadPenalty, ())
	//CREATE(float, GravityMultiplier, (float, bool))

public:
	static auto Hook() -> void;
	static auto UnHook() -> void;
};

auto Hooks::Hook() -> void {
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
	{
		printf("Failed Hook");
		return;
	}

	//const auto SwapChainFn = reinterpret_cast<IDXGISwapChain * (*)()>(pattern::find(L"UnityPlayer.dll", "48 83 ec 28 e8 ? ? ? ? 48 8b 80 a0 03 00 00"))();
	//static auto SwapChain = *reinterpret_cast<PVOID**> (SwapChainFn);
	//static auto PresentAddr = reinterpret_cast<HRESULT(__fastcall*)(IDXGISwapChain*, UINT, UINT)>(SwapChain[8]);
	
	//MH_CreateHook(PresentAddr, Present::PresentHk, &Present::o_present);
	//MH_EnableHook(PresentAddr);

	Hooks::AddRecoilhk.InitializeHook("Brainwash.FKF.Runtime", "", "CharacterCameraRig", "AddRecoil", Hooks::AddRecoil);
	Hooks::CalculateSpreadhk.InitializeHook("Brainwash.FKF.Runtime", "Brainwash.FKF.Weapons", "FireWeaponController", "CalculateSpread", Hooks::CalculateSpread);
	Hooks::CalculateSpreadPenaltyhk.InitializeHook("Brainwash.FKF.Runtime", "", "CharacterWeaponController", "CalculateSpreadPenalty", Hooks::CalculateSpreadPenalty);
	//Hooks::GravityMultiplierhk.InitializeHook("Brainwash.FKF.Runtime", "", "CharacterJump", "GravityMultiplier", Hooks::GravityMultiplier);
}

void clear() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

bool doOnce = false;
auto Hooks::UnHook() -> void {
	if (doOnce == false) {
		MH_DisableHook(MH_ALL_HOOKS);
		clear();
		std::cout << "Unhooked\n";
		doOnce = true;
	}
}