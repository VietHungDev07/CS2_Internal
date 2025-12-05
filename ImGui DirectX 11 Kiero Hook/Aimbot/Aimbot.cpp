#include <Aimbot/Aimbot.h>

float GetDistance2D(const Vector3& a, const Vector3& b)
{
    return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
Vector3 CalAngel(Vector3 myself, Vector3 enemy) {
    Vector3 difference = { myself.x - enemy.x, myself.y - enemy.y, myself.z - enemy.z };
    Vector3 a = { 0, 0 };
    if (difference.x > 0 && difference.y > 0)
        a.x = atan(difference.y / difference.x) / (float)PI * 180 - 180;
    else if (difference.x <= 0 && difference.y > 0)
        a.x = atan(difference.y / difference.x) / (float)PI * 180;
    else if (difference.x <= 0 && difference.y < 0)
        a.x = atan(difference.y / difference.x) / (float)PI * 180;
    else if (difference.x >= 0 && difference.y < 0)
        a.x = atan(difference.y / difference.x) / (float)PI * 180 + 180;
    a.y = atan(difference.z / sqrt(difference.x * difference.x + difference.y * difference.y)) / (float)PI * 180;
    return a;
}

DWORD WINAPI AimbotMain(LPVOID)
{
    while (true)
    {
        if (!Setting::Aimbot::Aimbot)
        {
            Sleep(1);
            continue;
        }

        auto entityList = Entity::GetListPlayer("client.dll");
        if (entityList.empty())
            continue;

        uintptr_t localPlayer = Entity::GetLocalPlayer("client.dll");
        uintptr_t localPawn = Entity::GetpCSPlayerPawn("client.dll", localPlayer);
        if (!localPawn) continue;

        int localTeam = UPlayer::GetTeamID(localPawn);
        Vector3 localCam = Camera::GetLastClipCameraPos(localPawn);

        float bestDist = FLT_MAX;
        Vector3 bestAngle{};
        bool hasTarget = false;

        for (auto& ent : entityList)
        {
            uintptr_t pawn = Entity::GetpCSPlayerPawn("client.dll", ent);
            if (!pawn || pawn == localPawn) continue;

            if (UPlayer::GetHealth(pawn) <= 0) continue;
            if (Setting::ESP::TeamCheck) {

                if (UPlayer::GetTeamID(pawn) == localTeam) continue;
            }

            Vector3 worldBone = UPlayer::GetPostionBone(pawn, Setting::Aimbot::AimbotIn);

            Vector3 s = Camera::WorldToScreen(&worldBone);
            if (s.z < 0.1f) continue; 

            Vector3 screenCenter =
            {
                DATA::windowWidth / 2.0f,
                DATA::windowHeight / 2.0f,
                0.0f
            };

            float dist = GetDistance2D(screenCenter, s);

            if (dist > Setting::Aimbot::FOV) continue;

            if (dist < bestDist)
            {
                bestDist = dist;
                bestAngle = CalAngel(localCam, worldBone);

                hasTarget = true;
            }
        }

        if (!hasTarget) continue;

        if (!(GetAsyncKeyState(Setting::Aimbot::VKKey) & 0x8000))
            continue;

        uintptr_t pPitch = Camera::GetXViewAngles("client.dll");
        uintptr_t pYaw = Camera::GetYViewAngles("client.dll");
        bestAngle.x = *(float*)pPitch + (bestAngle.x - *(float*)pPitch) / 1.0f;
        bestAngle.y = *(float*)pYaw + (bestAngle.y - *(float*)pYaw) / 1.0f;
        *(float*)pPitch = bestAngle.x;
        *(float*)pYaw = bestAngle.y;

        Sleep(1);
    }
    return 0;
}
