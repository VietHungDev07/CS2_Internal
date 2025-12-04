#include <Offset/Offset.h>
#include <string>
#include <SDK.h>
#include <vector>

using namespace std;

namespace DATA
{
    view_matrix_t ViewMatrix{};
    std::vector<std::pair<int, int>> BoneMap =
    {
        // Head
        {6, 5},   // head -> neck
        {5, 4},   // neck -> upper spine
        {4, 2},   // upper spine -> mid spine
        {2, 0},   // mid spine -> pelvis

        // Shoulders
        {4, 8},   // spine -> left shoulder
        {4, 13},  // spine -> right shoulder

        // Left arm
        {8, 9},   // arm_upper_L -> arm_lower_L
        {9, 10},  // arm_lower_L -> hand_L

        // Right arm
        {13, 14}, // arm_upper_R -> arm_lower_R
        {14, 15}, // arm_lower_R -> hand_R

        // Legs 
        {0, 22},  // pelvis -> leg_upper_L
        {22, 23}, // leg_upper_L -> leg_lower_L
        {23, 24}, // leg_lower_L -> ankle_L

        {0, 25},  // pelvis -> leg_upper_R
        {25, 26}, // leg_upper_R -> leg_lower_R
        {26, 27}  // leg_lower_R -> ankle_R
    };

}

namespace Module
{
    uintptr_t GetBase(LPCSTR namemodule)
    {
        HMODULE hMod = GetModuleHandleA(namemodule);
        if (!hMod) return 0;
        return reinterpret_cast<uintptr_t>(hMod);
    }
}

namespace SafeRead
{
    template<typename T>
    bool Read(uintptr_t addr, T& out)
    {
        if (addr < 0x10000) return false; 
        __try {
            out = *(T*)addr;
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }
    }
}

namespace Camera
{
    view_matrix_t GetViewMatrix(LPCSTR namemodule)
    {
        uintptr_t base = Module::GetBase(namemodule);
        if (!base) return view_matrix_t{};

        view_matrix_t temp{};
        if (SafeRead::Read(base + Offset::dwViewMatrix, temp))
            DATA::ViewMatrix = temp;

        return DATA::ViewMatrix;
    }

    Vector3 WorldToScreen(Vector3* v) 
    {
        float _x = DATA::ViewMatrix[0][0] * v->x + DATA::ViewMatrix[0][1] * v->y + DATA::ViewMatrix[0][2] * v->z + DATA::ViewMatrix[0][3];
        float _y = DATA::ViewMatrix[1][0] * v->x + DATA::ViewMatrix[1][1] * v->y + DATA::ViewMatrix[1][2] * v->z + DATA::ViewMatrix[1][3];

        float w = DATA::ViewMatrix[3][0] * v->x + DATA::ViewMatrix[3][1] * v->y + DATA::ViewMatrix[3][2] * v->z + DATA::ViewMatrix[3][3];

        float inv_w = 1.f / w;
        _x *= inv_w;
        _y *= inv_w;

        float x = DATA::windowWidth * .5f;
        float y = DATA::windowHeight * .5f;

        x += 0.5f * _x * DATA::windowWidth + 0.5f;
        y -= 0.5f * _y * DATA::windowHeight + 0.5f;

        return { x, y, w };
    }

    uintptr_t GetYViewAngles(LPCSTR namemodule)
    {
        uintptr_t base = Module::GetBase(namemodule);
        if (!base) return 0.0f;

        return base + Offset::dwViewAngles + 0x0;

    }
    uintptr_t GetXViewAngles(LPCSTR namemodule)
    {
        uintptr_t base = Module::GetBase(namemodule);
        if (!base) return 0;

        return base + Offset::dwViewAngles + 0x4;

    }
    Vector3 GetLastClipCameraPos(uintptr_t Pawn)
    {
        Vector3 LastClipCameraPos;
        SafeRead::Read(Pawn + Offset::m_vecLastClipCameraPos, LastClipCameraPos);
        return LastClipCameraPos;
    }

}

namespace UPlayer
{
    int GetTeamID(uintptr_t Pawn)
    {
        int val = 0;
        SafeRead::Read(Pawn + Offset::m_iTeamNum, val);
        return val;
    }

    Vector3 GetLocaltion(uintptr_t Pawn)
    {
        Vector3 loc{};
        SafeRead::Read(Pawn + Offset::m_vOldOrigin, loc);
        return loc;
    }

    int GetHealth(uintptr_t Pawn)
    {
        int hp = 0;
        SafeRead::Read(Pawn + Offset::m_iHealth, hp);
        return hp;
    }


    uintptr_t GetBoneArray(uintptr_t Pawn)
    {
        uintptr_t gameSceneNode;
        SafeRead::Read(Pawn + Offset::m_pGameSceneNode, gameSceneNode);
        uintptr_t boneArray;
        SafeRead::Read(gameSceneNode + 0x210, boneArray);
        return boneArray;
    }

    Vector3 GetPostionBone(uintptr_t Pawn, int BoneIndex)
    {
        Vector3 bonePosition;
        SafeRead::Read(GetBoneArray(Pawn) + BoneIndex * 32, bonePosition);
        return bonePosition;
    }


}

namespace Entity
{
    uintptr_t GetLocalPlayer(LPCSTR namemodule)
    {
        uintptr_t base = Module::GetBase(namemodule);
        if (!base) return 0;

        uintptr_t local{};
        SafeRead::Read(base + Offset::dwLocalPlayerController, local);
        return local;
    }

    uintptr_t GetPawn(uintptr_t Entity)
    {
        uintptr_t pawn{};
        SafeRead::Read(Entity + Offset::m_hPlayerPawn, pawn);
        return pawn;
    }

    uintptr_t GetEntityList(LPCSTR namemodule)
    {
        uintptr_t base = Module::GetBase(namemodule);
        if (!base) return 0;

        uintptr_t list{};
        SafeRead::Read(base + Offset::dwEntityList, list);
        return list;
    }

    uintptr_t GetpCSPlayerPawn(LPCSTR namemodule, uintptr_t Entity)
    {
        uintptr_t list = GetEntityList(namemodule);
        if (!list) return 0;

        uintptr_t pawn = GetPawn(Entity);
        if (!pawn) return 0;

        uintptr_t list_entry{};
        uintptr_t idx0 = (pawn & 0x7FFF) >> 9;

        if (!SafeRead::Read(list + 0x8 * idx0 + 16, list_entry))
            return 0;

        uintptr_t pawn_addr{};
        uintptr_t idx1 = (pawn & 0x1FF);

        if (!SafeRead::Read(list_entry + 112 * idx1, pawn_addr))
            return 0;

        return pawn_addr;
    }

    std::vector<uintptr_t> GetListPlayer(LPCSTR namemodule)
    {
        std::vector<uintptr_t> EntityList;

        uintptr_t list = GetEntityList(namemodule);
        if (!list) return EntityList;

        int playerIndex = 0;

        while (true)
        {
            playerIndex++;

            uintptr_t list_entry{};
            uintptr_t idx0 = (playerIndex & 0x7FFF) >> 9;

            if (!SafeRead::Read(list + 0x8 * idx0 + 16, list_entry))
                break;

            if (!list_entry)
                break;

            uintptr_t entity{};
            uintptr_t idx1 = (playerIndex & 0x1FF);

            if (!SafeRead::Read(list_entry + 112 * idx1, entity))
                continue;

            if (entity)
                EntityList.push_back(entity);
        }

        return EntityList;
    }
}
