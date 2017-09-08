////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SystemClass.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* system;
	bool result;

	// system ��ü�� �����Ѵ�
	system = new SystemClass;
	if (!system)
	{
		return 0;
	}

	// system ��ü�� �ʱ�ȭ�ϰ� run�� ȣ���Ѵ�.
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}

	// system��ü�� �����ϰ� �޸𸮸� ��ȯ�Ѵ�.
	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}