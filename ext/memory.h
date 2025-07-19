#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <string_view>
#include <string_view>

class Memory
{
private:
    std::uintptr_t processId = 0;
    void* processHandle = nullptr;

public:
    Memory(std::wstring_view processName) noexcept
    {
        ::PROCESSENTRY32W entry = { };
        entry.dwSize = sizeof(::PROCESSENTRY32W);

        const HANDLE snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        while (::Process32NextW(snapShot, &entry))
        {
            if (!processName.compare(entry.szExeFile))
            {
                processId = entry.th32ProcessID;
                processHandle = ::OpenProcess(PROCESS_VM_READ, FALSE, processId);
                break;
            }
        }

        if (snapShot)
            ::CloseHandle(snapShot);
    }

    ~Memory()
    {
        if (processHandle)
            ::CloseHandle(processHandle);
    }

    std::uintptr_t GetModuleBase(std::wstring_view moduleName) const noexcept
    {
        ::MODULEENTRY32W entry = { };
        entry.dwSize = sizeof(::MODULEENTRY32W);

        const HANDLE snapShot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

        std::uintptr_t result = 0;

        while (::Module32NextW(snapShot, &entry))
        {
            if (!moduleName.compare(entry.szModule))
            {
                result = reinterpret_cast<std::uintptr_t>(entry.modBaseAddr);
                break;
            }
        }

        if (snapShot)
            ::CloseHandle(snapShot);

        return result;
    }

    template <typename T>
    const T read(const std::uintptr_t address) const noexcept
    {
        T value = { };
        ::ReadProcessMemory(processHandle, reinterpret_cast<const void*>(address), &value, sizeof(T), NULL);
        return value;
    }

    template <typename T>
    void write(const std::uintptr_t address, const T& value) const noexcept
    {
        ::WriteProcessMemory(processHandle, reinterpret_cast<void*>(address), &value, sizeof(T), NULL);
    }
};
