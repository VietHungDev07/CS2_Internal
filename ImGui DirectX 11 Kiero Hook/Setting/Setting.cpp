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
        ImColor SkeletonColor = ImColor(255, 0, 0, 255);

        float SkeletonThickness = 1.5f;
        ImColor BoxColor = ImColor(255, 0, 0, 255);
        float BoxThickness = 1.0f;
        ImColor SnapLineColor = ImColor(255, 0, 0, 255);
    }
    namespace Aimbot
    {
        bool Aimbot = false;
        float FOV = 60.0f;
        int VKKey = VK_XBUTTON2; 
        int AimbotIn;//6 = head , 5 = neck , 0 = pelvis
        bool waitingForKey = false;
    }
    namespace Memory
    {
        bool JumpEvent = false;
    }
}