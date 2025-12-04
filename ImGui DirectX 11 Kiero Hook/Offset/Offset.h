#include<Windows.h>
#include <cstddef>
#include <cstdint>
namespace Offset 
{
//Offsets.x
	inline std::uintptr_t dwLocalPlayerController = 31571032;
	inline std::uintptr_t dwEntityList = 30481784;
	inline std::uintptr_t dwViewMatrix = 31654992;
	inline std::uintptr_t dwViewAngles = 0x1E3A880;
//clinet.dll.x
	inline std::uintptr_t m_vOldOrigin = 5536; 
	inline std::uintptr_t m_pGameSceneNode = 816;
	inline std::uintptr_t m_iHealth = 844;
	inline std::uintptr_t m_hPlayerPawn = 2300;
	inline std::uintptr_t m_iTeamNum = 1003;
	inline std::uintptr_t m_vecLastClipCameraPos = 0x3DC4;
}