#include <Draw/Draw.h>
#include<Setting/Setting.h>
void DrawHealthBar(uintptr_t Pawn)
{
    int Health = UPlayer::GetHealth(Pawn);
    if (Health <= 0 || Health > 200) return;

    std::vector<int> ImportantBones =
    {
        6, 5, 4, 2, 0,      // head -> pelvis
        8, 13,             // shoulders
        10, 15,            // hands
        22, 23, 24,        // left leg
        25, 26, 27         // right leg
    };

    float minX = FLT_MAX, minY = FLT_MAX;
    float maxX = -FLT_MAX, maxY = -FLT_MAX;

    for (int boneID : ImportantBones)
    {
        Vector3 boneWorld = UPlayer::GetPostionBone(Pawn, boneID);
        Vector3 boneScreen = Camera::WorldToScreen(&boneWorld);

        if (boneScreen.z <= 0)
            continue;

        minX = min(minX, boneScreen.x);
        minY = min(minY, boneScreen.y);
        maxX = max(maxX, boneScreen.x);
        maxY = max(maxY, boneScreen.y);
    }

    if (minX == FLT_MAX || minY == FLT_MAX)
        return;

    float padding = 4.0f;
    minX -= padding;
    minY -= padding;
    maxX += padding;
    maxY += padding;

    float barWidth = 4.0f;
    float barX = minX - barWidth - 5.0f; 
    float barY = minY;
    float barHeight = maxY - minY;

    ImDrawList* draw = ImGui::GetForegroundDrawList();


    draw->AddRectFilled(
        ImVec2(barX, barY),
        ImVec2(barX + barWidth, barY + barHeight),
        IM_COL32(50, 50, 50, 200)
    );

    float hpPercent = (float)Health / 100.0f;
    if (hpPercent > 1.0f) hpPercent = 1.0f;

    float fillHeight = barHeight * hpPercent;

    ImColor color;
    if (Health > 75) color = ImColor(0, 255, 0);
    else if (Health > 50) color = ImColor(255, 255, 0);
    else if (Health > 25) color = ImColor(255, 165, 0);
    else color = ImColor(255, 0, 0);

    draw->AddRectFilled(
        ImVec2(barX, barY + (barHeight - fillHeight)),
        ImVec2(barX + barWidth, barY + barHeight),
        color
    );

    draw->AddRect(
        ImVec2(barX, barY),
        ImVec2(barX + barWidth, barY + barHeight),
        IM_COL32(0, 0, 0, 255)
    );
}


void DrawSkeleton(uintptr_t Pawn)
{
    for (auto& [a, b] : DATA::BoneMap)
    {
        Vector3 w1 = UPlayer::GetPostionBone(Pawn, a);
        Vector3 w2 = UPlayer::GetPostionBone(Pawn, b);

        Vector3 s1 = Camera::WorldToScreen(&w1);
        Vector3 s2 = Camera::WorldToScreen(&w2);

        if (s1.z > 0 && s2.z > 0)
        {
            ImColor skeletonColor = Setting::ESP::SkeletonColor;
            float thickness = Setting::ESP::SkeletonThickness;

            ImGui::GetForegroundDrawList()->AddLine(
                ImVec2(s1.x, s1.y),
                ImVec2(s2.x, s2.y),
                IM_COL32(skeletonColor.Value.x * 255, skeletonColor.Value.y * 255,
                    skeletonColor.Value.z * 255, skeletonColor.Value.w * 255),
                thickness
            );
        }
    }
}

void DrawBoxESP(uintptr_t Pawn)
{
    std::vector<int> ImportantBones =
    {
        6, 5, 4, 2, 0,      // head -> pelvis
        8, 13,             // shoulders
        10, 15,            // hands
        22, 23, 24,        // left leg
        25, 26, 27         // right leg
    };

    float minX = FLT_MAX, minY = FLT_MAX;
    float maxX = -FLT_MAX, maxY = -FLT_MAX;

    for (int boneID : ImportantBones)
    {
        Vector3 boneWorld = UPlayer::GetPostionBone(Pawn, boneID);
        Vector3 boneScreen = Camera::WorldToScreen(&boneWorld);

        if (boneScreen.z <= 0)
            continue;

        minX = min(minX, boneScreen.x);
        minY = min(minY, boneScreen.y);
        maxX = max(maxX, boneScreen.x);
        maxY = max(maxY, boneScreen.y);
    }


    if (minX == FLT_MAX || minY == FLT_MAX) return;


    float padding = 4.0f;
    minX -= padding;
    minY -= padding;
    maxX += padding;
    maxY += padding;

    ImColor color = Setting::ESP::BoxColor;
    float thickness = Setting::ESP::BoxThickness;

    ImDrawList* draw = ImGui::GetForegroundDrawList();

    draw->AddRect(
        ImVec2(minX, minY),
        ImVec2(maxX, maxY),
        IM_COL32(color.Value.x * 255, color.Value.y * 255, color.Value.z * 255, color.Value.w * 255),
        0.0f, 0, thickness
    );

    draw->AddRectFilled(
        ImVec2(minX, minY),
        ImVec2(maxX, maxY),
        IM_COL32(0, 0, 0, 40)
    );

    float corner = (maxX - minX) * 0.2f;

    // TL
    draw->AddLine(ImVec2(minX, minY), ImVec2(minX + corner, minY), color, thickness);
    draw->AddLine(ImVec2(minX, minY), ImVec2(minX, minY + corner), color, thickness);

    // TR
    draw->AddLine(ImVec2(maxX, minY), ImVec2(maxX - corner, minY), color, thickness);
    draw->AddLine(ImVec2(maxX, minY), ImVec2(maxX, minY + corner), color, thickness);

    // BL
    draw->AddLine(ImVec2(minX, maxY), ImVec2(minX + corner, maxY), color, thickness);
    draw->AddLine(ImVec2(minX, maxY), ImVec2(minX, maxY - corner), color, thickness);

    // BR
    draw->AddLine(ImVec2(maxX, maxY), ImVec2(maxX - corner, maxY), color, thickness);
    draw->AddLine(ImVec2(maxX, maxY), ImVec2(maxX, maxY - corner), color, thickness);
}

void DrawDistance(uintptr_t Pawn)
{
    Vector3 HeadWorld = UPlayer::GetPostionBone(Pawn, 6);
    Vector3 RootWorld = UPlayer::GetLocaltion(Pawn);

    Vector3 HeadScreen = Camera::WorldToScreen(&HeadWorld);
    Vector3 RootScreen = Camera::WorldToScreen(&RootWorld);

    if (HeadScreen.z <= 0 || RootScreen.z <= 0) return;

    // Calculate distance
    uintptr_t localPawn = Entity::GetpCSPlayerPawn("client.dll", Entity::GetLocalPlayer("client.dll"));
    if (!localPawn) return;

    Vector3 localPos = UPlayer::GetLocaltion(localPawn);
    Vector3 enemyPos = RootWorld;

    float distance = sqrt(
        pow(localPos.x - enemyPos.x, 2) +
        pow(localPos.y - enemyPos.y, 2) +
        pow(localPos.z - enemyPos.z, 2)
    );

    distance = distance / 39.37f; 

    char distanceText[32];
    snprintf(distanceText, sizeof(distanceText), "%.1fm", distance);

    // Position text below the box
    float height = abs(RootScreen.y - HeadScreen.y);
    float width = height * 0.3f;

    ImVec2 textSize = ImGui::CalcTextSize(distanceText);
    float textX = HeadScreen.x - textSize.x / 2;
    float textY = HeadScreen.y + height + 2.0f;

    /*
    if (Setting::ESP::TextBackground)
    {
        ImGui::GetForegroundDrawList()->AddRectFilled(
            ImVec2(textX - 2, textY - 2),
            ImVec2(textX + textSize.x + 2, textY + textSize.y + 2),
            IM_COL32(0, 0, 0, 150)
        );
    }
    */

    // Draw distance text
    ImGui::GetForegroundDrawList()->AddText(
        ImVec2(textX, textY),
        IM_COL32(255, 255, 255, 255),
        distanceText
    );
}

void EntryDrawEntity()
{
    if (!Setting::ESP::ESP) return;

    auto entityList = Entity::GetListPlayer("client.dll");
    if (entityList.empty()) return;

    uintptr_t localPlayer = Entity::GetLocalPlayer("client.dll");
    if (!localPlayer) return;

    uintptr_t localPawn = Entity::GetpCSPlayerPawn("client.dll", localPlayer);
    if (!localPawn) return;

    int localTeam = UPlayer::GetTeamID(localPawn);

    for (auto& ent : entityList)
    {
        if (!ent) continue;

        uintptr_t pawn = Entity::GetpCSPlayerPawn("client.dll", ent);
        if (!pawn) continue;


        if (pawn == localPawn) continue;

        int health = UPlayer::GetHealth(pawn);
        if (health <= 0 || health > 200) continue;


         int team = UPlayer::GetTeamID(pawn);
         if (team == localTeam) continue;
        

        Vector3 rootPos = UPlayer::GetLocaltion(pawn);
        Vector3 screenPos = Camera::WorldToScreen(&rootPos);
        if (screenPos.z <= 0) continue;

        float distance = sqrt(
            pow(UPlayer::GetLocaltion(localPawn).x - rootPos.x, 2) +
            pow(UPlayer::GetLocaltion(localPawn).y - rootPos.y, 2) +
            pow(UPlayer::GetLocaltion(localPawn).z - rootPos.z, 2)
        );


        if (Setting::ESP::BOX)
        {
            DrawBoxESP(pawn);
        }

        if (Setting::ESP::Skeleton)
        {
            DrawSkeleton(pawn);
        }

        if (Setting::ESP::HealthBar)
        {
            DrawHealthBar(pawn);
        }

        if (Setting::ESP::Distance)
        {
            DrawDistance(pawn);
        }


        if (Setting::ESP::SnapLine)
        {
            ImVec2 screenCenter = ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y);
            ImGui::GetForegroundDrawList()->AddLine(
                screenCenter,
                ImVec2(screenPos.x, screenPos.y),
                Setting::ESP::SnapLineColor,
                1.0f
            );
        }
    }
}