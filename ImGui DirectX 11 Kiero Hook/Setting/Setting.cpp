#include "Setting/Setting.h"

namespace Setting
{
    namespace ESP
    {
        bool ESP = true;
        bool BOX = false;
        bool HealthBar = false;
        bool Skeleton = false;
        bool DoanVanSang = false;
        bool Distance = false;
        bool SnapLine = false;
        bool TeamCheck = false;
        bool Name = false;
        bool RainbowGlow = false;
        bool VisibleCheck = false;

        ImColor VisibleColor = ImColor(255, 0, 0, 255);
        int GlowMode = 0;
        ImColor SkeletonColor = ImColor(255, 0, 0, 255);

        float SkeletonThickness = 1.5f;
        ImColor BoxColor = ImColor(255, 0, 0, 255);
        float BoxThickness = 1.0f;
        ImColor SnapLineColor = ImColor(255, 0, 0, 255);
        float GlowColor[4] = {0.0f, 0.0f, 1.0f, 1.0f};    
    }
    namespace Aimbot
    {
        bool Aimbot = false;
        float FOV = 60.0f;
        int VKKey = VK_XBUTTON2; 
        int AimbotIn = 6;//6 = head , 5 = neck , 0 = pelvis
        bool waitingForKey = false;
        bool VisibleCheck = false;
        bool TriggerBot = false;
        float TriggerFov = 5.0f;
    }
    namespace Memory
    {
        bool JumpEvent = false;
        bool Glow = false;
     
    }
}