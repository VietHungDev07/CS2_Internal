#pragma once
#include <Draw/Draw.h>

namespace Setting
{
    namespace ESP
    {
        extern bool ESP;
        extern bool BOX;
        extern bool HealthBar;
        extern bool Skeleton;
        extern bool DoanVanSang;
        extern bool Distance;
        extern bool SnapLine;
        extern bool TeamCheck;
        extern bool Name;
        extern bool RainbowGlow;
        extern ImColor SkeletonColor;
        extern float SkeletonThickness;
        extern ImColor BoxColor;
        extern float BoxThickness;
        extern bool BoxFilled;
        extern int BoxStyle;
        extern int GlowMode;
        extern float GlowColor[4];
        extern ImColor SnapLineColor;
        extern bool VisibleCheck;
        extern ImColor VisibleColor;
    }
    namespace Aimbot
    {
        extern bool Aimbot;
        extern float FOV;
        extern int VKKey;
        extern int AimbotIn;
        extern bool VisibleCheck;
        extern bool TriggerBot;
        extern float TriggerFov;
    }
    namespace Memory
    {
        extern bool JumpEvent;
        extern bool Glow;
 

    }
}