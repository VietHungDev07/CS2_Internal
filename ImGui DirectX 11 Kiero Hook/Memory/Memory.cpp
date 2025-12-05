#include <Memory/Memory.h>
#include <Offset/Offset.h>
#include <vector>
#include <Windows.h>


void ApplyGlow(uintptr_t pawn)
{
    if (!pawn) return;

    int* overrideColor = (int*)(pawn + Offset::m_Glow + Offset::m_glowColorOverride);
    bool* glowing = (bool*)(pawn + Offset::m_Glow + Offset::m_bGlowing);

    if (!overrideColor || !glowing)
        return;

    *overrideColor = 0x800000FF;    
    *glowing = true;
}


void GlowEnemy()
{
    uintptr_t localController = Entity::GetLocalPlayer("client.dll");
    if (!localController) return;

    uintptr_t localPawn = Entity::GetpCSPlayerPawn("client.dll", localController);
    if (!localPawn) return;

    int localTeam = *(int*)(localPawn + Offset::m_iTeamNum);

    auto list = Entity::GetListPlayer("client.dll");

    for (auto ent : list)
    {
        if (!ent) continue;

        uintptr_t pawn = Entity::GetpCSPlayerPawn("client.dll", ent);
        if (!pawn) continue;

        if (pawn == localPawn)
            continue;

        int team = *(int*)(pawn + Offset::m_iTeamNum);

        if (team == localTeam)
            continue; 

        int hp = *(int*)(pawn + Offset::m_iHealth);
        if (hp <= 0)
            continue; 

        
        ApplyGlow(pawn);
    }
}


void BunnyHop()
{
    uintptr_t localPlayer = Entity::GetLocalPlayer("client.dll");
    if (!localPlayer) return;

    uintptr_t localPawn = Entity::GetpCSPlayerPawn("client.dll", localPlayer);
    if (!localPawn) return;

    bool canJump = *(bool*)(localPawn + Offset::FlagJump);

    if (GetAsyncKeyState(VK_SPACE) && !canJump)
        *(int*)(Module::GetBase("client.dll") + Offset::jump) = 0x10001;
    else
        *(int*)(Module::GetBase("client.dll") + Offset::jump) = 0x100;
}


DWORD WINAPI EntryMemory(LPVOID lp)
{
    while (true)
    {
        if (Setting::Memory::JumpEvent)
            BunnyHop();

        if (Setting::Memory::Glow)
            GlowEnemy();

        Sleep(5);
    }
}
