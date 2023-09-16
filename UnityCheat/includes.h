#pragma once
#pragma warning ( disable : 4172 )
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

bool show = false;
bool panic = false;

#include <Windows.h>
#include <iostream>
#include <string>
#include <TlHelp32.h>
#include "Psapi.h"
#include <list>
#include <WinUser.h>
#include <map>
#include <iostream>
#include <memory>
#include <string_view>
#include <cstdint>
#include <xstring>
#include <vector>
#include <thread>
#include <filesystem>
#include <stdio.h>
#include <iosfwd>
#include <fstream>
#include <iomanip>

#include <d3d11.h>
#include <dxgi.h>
#include <D3DX11.h>
#include <D3DX11tex.h>
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3d11.lib")

#include "Utils/xorstr.h"
#include "Utils/CRC.hpp"
#include "Utils/Structs/Vector3.hpp"
#include "Utils/Structs/Vector2.hpp"
#include "Utils/Structs/Quanterion.hpp"
#include "Utils/Structs/Matrix.hpp"
#include "Utils/Memory/Memory.hpp"
#include "Utils/Memory/Pattern.hpp"
#include "Utils/String.hpp"
#include "Utils/Il2cpp/Il2cpp.hpp"
#include "Utils/Enums.hpp"
#include "Utils/Memory/Extra.hpp"
#include "Utils/Structs/Structs.hpp"
#include "Utils/Memory/Array.hpp"

#include "Hooks/Minhook/include/MinHook.h"
#include "Hooks/HookLib.h"
#pragma comment(lib, "Hooks/Minhook/MinHook.x64.lib")

#include "Drawing/ImGui/imgui.h"
#include "Drawing/ImGui/imgui_impl_dx11.h"
#include "Drawing/ImGui/imgui_impl_win32.h"
#include "Drawing/ImGui/imgui_internal.h"
#include "Drawing/ui.h"
#include "Drawing/Present.h"

#include "Hooking.h"
#include "gamesdk.h"
#include "Cheat.h"