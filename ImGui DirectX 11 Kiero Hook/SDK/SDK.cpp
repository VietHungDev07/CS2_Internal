#include <Offset/Offset.h>
#include <string>
#include <SDK.h>
#include <vector>

using namespace std;

namespace DATA
{
    view_matrix_t ViewMatrix{};
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

        float x = windowWidth * .5f;
        float y = windowHeight * .5f;

        x += 0.5f * _x * windowWidth + 0.5f;
        y -= 0.5f * _y * windowHeight + 0.5f;

        return { x, y, w };
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

    int GetArmor(uintptr_t Pawn)
    {
        int armor = 0;
        SafeRead::Read(Pawn + Offset::m_ArmorValue, armor);
        return armor;
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
