#pragma once
#include <cstdint>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>

namespace Offsets {
    // OFFSETS.HPP -> https://github.com/a2x/cs2-dumper/blob/main/output/offsets.hpp
    DWORD dwEntityList = 0x1A05670;
    DWORD dwLocalPlayerPawn = 0x18590D0;
    DWORD dwViewMatrix = 0x1A6E3F0;

    // CLIENT_DLL.HPP -> https://github.com/a2x/cs2-dumper/blob/main/output/client_dll.hpp
    DWORD m_hPlayerPawn = 0x824;
    DWORD m_iHealth = 0x344;
    DWORD m_iTeamNum = 0x3E3;
    DWORD m_vOldOrigin = 0x1324;
    DWORD m_pGameSceneNode = 0x328;
    DWORD m_modelState = 0x170;

    constexpr uintptr_t m_pWeaponServices = 0x11A8; // CS2 offset for weapon services
    constexpr uintptr_t m_hActiveWeapon = 0x58;    // Offset within weapon services
    constexpr uintptr_t m_szName = 0xD20;
}