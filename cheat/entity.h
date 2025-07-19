#pragma once
#include "../ext/memory.h"
#include "offsets.h"
#include "math.h"
#include "cfg.h"

Memory* memory = new Memory{ L"cs2.exe" };

uintptr_t client = memory->GetModuleBase(L"client.dll");

namespace localplayer {
    uintptr_t G_Pawn();
    int G_Team();
    int G_Health();
    Vec3 G_Pos();
    bool B_Dead();

    bool isdead;
    int teamid;

    uintptr_t pawn;
    int health;
    void init();
    void loop();
}

void localplayer::loop()
{
    while (1)
    {
        localplayer::teamid = memory->read<int>(localplayer::G_Pawn() + Offsets::m_iTeamNum);
        localplayer::health = memory->read<int>(localplayer::G_Pawn() + Offsets::m_iHealth);
        localplayer::pawn = memory->read<uintptr_t>(client + Offsets::dwLocalPlayerPawn);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

void localplayer::init()
{
    std::thread([&]() { localplayer::loop(); }).detach();
}

uintptr_t localplayer::G_Pawn()
{
    return memory->read<uintptr_t>(client + Offsets::dwLocalPlayerPawn);
}

int localplayer::G_Team()
{
    return memory->read<int>(localplayer::G_Pawn() + Offsets::m_iTeamNum);
}

int localplayer::G_Health()
{
    return memory->read<int>(localplayer::G_Pawn() + Offsets::m_iHealth);
}

Vec3 localplayer::G_Pos()
{
    return memory->read<Vec3>(localplayer::G_Pawn() + Offsets::m_vOldOrigin);
}

bool localplayer::B_Dead()
{
    return localplayer::G_Health() <= 0;
}

namespace entities {
    struct PLAYER {
        int health, team, armor;
        uintptr_t actorBase;
        std::vector<Vec3> bones;
        Vec3 PlayerPos;
        char name[32];
        short weaponame;
    };

    std::vector<PLAYER> entities;

    struct CacheEntry {
        PLAYER player;
        uint64_t lastUpdate;
    };
    std::vector<CacheEntry> entityCache;
    const uint64_t CACHE_UPDATE_INTERVAL = 1;

    void entityloop();
    void init();

    ImColor GetColorHealth(int health)
    {
        if (health > 98)
            return ImColor(0.0f, 1.0f, 0.0f, 0.8f);
        if (health > 95)
            return ImColor(0.1f, 1.0f, 0.1f, 0.8f);
        if (health > 90)
            return ImColor(0.2f, 1.0f, 0.2f, 0.8f);
        if (health > 80)
            return ImColor(0.4f, 1.0f, 0.0f, 0.8f);
        if (health > 70)
            return ImColor(0.6f, 1.0f, 0.0f, 0.8f);
        if (health > 60)
            return ImColor(0.8f, 1.0f, 0.0f, 0.8f);
        if (health > 50)
            return ImColor(1.0f, 1.0f, 0.0f, 0.8f);
        if (health > 40)
            return ImColor(1.0f, 0.8f, 0.0f, 0.8f);
        if (health > 30)
            return ImColor(1.0f, 0.6f, 0.0f, 0.8f);
        if (health > 25)
            return ImColor(1.0f, 0.4f, 0.0f, 0.8f);
        if (health > 15)
            return ImColor(1.0f, 0.2f, 0.0f, 0.8f);
        if (health > 5)
            return ImColor(1.0f, 0.0f, 0.0f, 0.8f);
        return ImColor(0.5f, 0.0f, 0.0f, 0.8f);
    }
}

void entities::init()
{

    std::cout << "client.dll -> " << std::hex << client << std::dec << "\n";

    std::thread([&]() { entities::entityloop(); }).detach();
}

void entities::entityloop() {
    entityCache.resize(64);

    while (true) {
        std::vector<PLAYER> templist;
        uintptr_t entityList = memory->read<uintptr_t>(client + Offsets::dwEntityList);
        uintptr_t listEntry = memory->read<uintptr_t>(entityList + 0x10);

        auto currentTime = GetTickCount64();

        for (int i = 1; i < 64; ++i) {
            uintptr_t currentController = memory->read<uintptr_t>(listEntry + i * 0x78);
            if (currentController == 0) continue;

            int pawnHandle = memory->read<int>(currentController + Offsets::m_hPlayerPawn);
            if (pawnHandle == 0) continue;

            uintptr_t listEntry2 = memory->read<uintptr_t>(entityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);
            if (listEntry2 == 0) continue;

            uintptr_t entityPawn = memory->read<uintptr_t>(listEntry2 + 0x78 * (pawnHandle & 0x1FF));
            if (entityPawn == 0) continue;

            bool needsUpdate = true;
            if (entityCache[i].player.actorBase == entityPawn &&
                (currentTime - entityCache[i].lastUpdate) < CACHE_UPDATE_INTERVAL) {
                templist.push_back(entityCache[i].player);
                continue;
            }

            int Pawnhealth = memory->read<int>(entityPawn + Offsets::m_iHealth);
            if (Pawnhealth == 0) continue;

            int pawnteamId = memory->read<int>(entityPawn + Offsets::m_iTeamNum);
            if (cfg::teamCheck)
                if (pawnteamId == localplayer::teamid) continue;

            Vec3 position = memory->read<Vec3>(entityPawn + Offsets::m_vOldOrigin);
            if (position.IsNull()) continue;

            uint64_t gamescene = memory->read<uint64_t>(entityPawn + Offsets::m_pGameSceneNode);
            uint64_t bonearray = memory->read<uint64_t>(gamescene + Offsets::m_modelState + 0x80);

            Vec3 bonear[] = {
                memory->read<Vec3>(bonearray + 6 * 32),
                memory->read<Vec3>(bonearray + 5 * 32),
                memory->read<Vec3>(bonearray + 8 * 32),
                memory->read<Vec3>(bonearray + 13 * 32),
                memory->read<Vec3>(bonearray + 9 * 32),
                memory->read<Vec3>(bonearray + 14 * 32),
                memory->read<Vec3>(bonearray + 11 * 32),
                memory->read<Vec3>(bonearray + 16 * 32),
                memory->read<Vec3>(bonearray + 0 * 32),
                memory->read<Vec3>(bonearray + 23 * 32),
                memory->read<Vec3>(bonearray + 26 * 32),
                memory->read<Vec3>(bonearray + 24 * 32),
                memory->read<Vec3>(bonearray + 27 * 32)
            };
            if (bonear[0].IsNull() && bonear[1].IsNull() && bonear[2].IsNull()) continue;

            PLAYER ent;
            ent.actorBase = entityPawn;
            ent.PlayerPos = position;
            ent.bones.assign(bonear, bonear + 13);
            ent.health = Pawnhealth;

            entityCache[i].player = ent;
            entityCache[i].lastUpdate = currentTime;
            templist.push_back(ent);
        }

        entities::entities = templist;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
