#include<Windows.h>
#include <cstddef>
#include <cstdint>
namespace Offset
{
	//Offsets.x
	inline std::uintptr_t dwLocalPlayerController = 31575048;
	inline std::uintptr_t dwEntityList = 30485736;
	inline std::uintptr_t dwViewMatrix = 31658960;
	inline std::uintptr_t dwViewAngles = 31700992;
	//clinet.dll.x
	inline std::uintptr_t m_vOldOrigin = 5536;
	inline std::uintptr_t m_pGameSceneNode = 816;
	inline std::uintptr_t m_iHealth = 844;
	inline std::uintptr_t m_hPlayerPawn = 2300;
	inline std::uintptr_t m_iTeamNum = 1003;
	inline std::uintptr_t m_vecLastClipCameraPos = 15812;
	inline std::uintptr_t m_entitySpottedState = 0x2700;
	inline std::uintptr_t m_bSpottedByMask = 0xC;
	inline std::uintptr_t m_pEntity = 0x10; // CEntityIdentity*
	inline std::uintptr_t FlagJump = 0x1EDC; //Manually to find [44 8b 87 ? ? ? ? 80 fa]: (rdi+?) - CSPlayerPawn
	//Button.hpp
	inline std::uintptr_t jump = 0x1BE78B0;

	

	inline std::uintptr_t m_Glow = 3248;

	inline std::uintptr_t m_glowColorOverride = 64;

	inline std::uintptr_t m_bGlowing = 81;

	inline std::uintptr_t m_iGlowType = 48;

	inline std::uintptr_t m_iIDEntIndex = 16076;

	




	//namespace Function
	//{
	//	uintptr_t TraceShape = 0x6F7BC0; //client.dll+6F7BC0 [48 89 5C 24 ? 48 89 4C 24 ? 55 57]
	//}
	//





}