#include <Memory/Memory.h>
#include <Offset/Offset.h>
#include <vector>
#include <Windows.h>
#include <unordered_map>
#pragma comment(lib, "winmm.lib")

void GetRainbowColor(float* outColor)
{
    if (!outColor) return;
    DWORD tick = GetTickCount() % 10000;
    float hue = (float)tick / 5000.0f;
    float r, g, b;
    int i = int(hue * 6);
    float f = hue * 6 - i;
    float q = 1 - f;
    switch (i % 6)
    {
    case 0: r = 1; g = f; b = 0; break;
    case 1: r = q; g = 1; b = 0; break;
    case 2: r = 0; g = 1; b = f; break;
    case 3: r = 0; g = q; b = 1; break;
    case 4: r = f; g = 0; b = 1; break;
    case 5: r = 1; g = 0; b = q; break;
    default: r = g = b = 1; break;
    }
    outColor[0] = r;
    outColor[1] = g;
    outColor[2] = b;
    outColor[3] = 1.0f;
}

void ApplyGlow(uintptr_t pawn)
{
    if (!pawn) return;
    int* overrideColor = (int*)(pawn + Offset::m_Glow + Offset::m_glowColorOverride);
    bool* glowing = (bool*)(pawn + Offset::m_Glow + Offset::m_bGlowing);
    if (!overrideColor || !glowing) return;
    float color[4];
    if (Setting::ESP::RainbowGlow)
        GetRainbowColor(color);
    else
        memcpy(color, Setting::ESP::GlowColor, sizeof(color));
   
    int r = (int)(color[0] * 255.0f);
    int g = (int)(color[1] * 255.0f);
    int b = (int)(color[2] * 255.0f);
    int a = (int)(color[3] * 255.0f);
    *overrideColor = (a << 24) | (b << 16) | (g << 8) | r;
    *glowing = true;
}

void GlowEnemy()
{
    uintptr_t localController = Entity::GetLocalPlayer("client.dll");
    if (!localController) return;
    uintptr_t localPawn = Entity::GetpCSPlayerPawn("client.dll", localController);
    if (!localPawn) return;
    int localTeam = UPlayer::GetTeamID(localPawn);
    auto list = Entity::GetListPlayer("client.dll");
    for (auto ent : list)
    {
        if (!ent) continue;
        uintptr_t pawn = Entity::GetpCSPlayerPawn("client.dll", ent);
        if (!pawn || pawn == localPawn) continue;
        if (Setting::ESP::TeamCheck) 
        {

            int team = UPlayer::GetTeamID(pawn);
            if (team == localTeam) continue;
        }
        int hp = UPlayer::GetHealth(pawn);
        if (hp <= 0) continue;
        ApplyGlow(pawn);
    }
}




void BunnyHop()
{
    uintptr_t localPlayer = Entity::GetLocalPlayer("client.dll");
    if (!localPlayer) return;
    uintptr_t localPawn = Entity::GetpCSPlayerPawn("client.dll", localPlayer);

   // printf("P: %p\n", localPawn);
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



      
    }
}