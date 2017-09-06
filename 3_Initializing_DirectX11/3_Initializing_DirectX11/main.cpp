////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SystemClass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* system;
	bool result;

	// system 객체를 생성한다
	system = new SystemClass;
	if (!system)
	{
		return 0;
	}

	// system 객체를 초기화하고 run을 호출한다.
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}

	// system객체를 종료하고 메모리를 반환한다.
	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}