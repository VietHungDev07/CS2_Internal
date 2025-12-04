#include<Memory/Memory.h>
#include <mutex>
#include<Offset/Offset.h>
void BunnyHop()
{

    uintptr_t localPlayer = Entity::GetLocalPlayer("client.dll");
    if (!localPlayer) return;

    uintptr_t localPawn = Entity::GetpCSPlayerPawn("client.dll", localPlayer);
    if (!localPawn) return;

	//printf("pointer is %p\n", localPawn);

	bool FlagJ = *(bool*)(localPawn + Offset::FlagJump);
	if (GetAsyncKeyState(VK_SPACE) && !FlagJ)
	{
		*(int*)(Module::GetBase("client.dll") + Offset::jump) = 0x10001;
	}
	else
	{
		*(int*)(Module::GetBase("client.dll") + Offset::jump) = 0x100;
	}


}



DWORD WINAPI EntryMemory(LPVOID lpReserved)
{
	while (true)
	{
		if (Setting::Memory::JumpEvent)
		{
			BunnyHop();
		}

		Sleep(10);
	}
}