////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "GraphicsClass.h"
#include <stdio.h>

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	// Direct3D ��ü�� �����մϴ�.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Direct3D ��ü�� �ʱ�ȭ�մϴ�.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	// D3D ��ü�� ��ȯ�մϴ�.
	if (m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	// �׷��� �������� �����մϴ�.
	result = Render();
	if (!result)
	{
		return false;
	}

	static bool createFile = false;
	if (!createFile)
	{
		FILE* file;
		fopen_s(&file, "GPU_INFO.txt", "w");
		char name[128];
		int memory;

		m_D3D->GetVideoCardInfo(name, memory);
		fprintf(file, "GPU_NAME: %s, GPU_MEMORY : %dMB", name, memory);

		fclose(file);
		createFile = true;
	}

	return true;
}

bool GraphicsClass::Render()
{
	// �� �׸��⸦ �����ϱ� ���� ������ ������ ����ϴ�.
	m_D3D->BeginScene(1.0f, 1.0f, 0.0f, 1.0f);

	// ���ۿ� �׷��� ���� ȭ�鿡 ǥ���մϴ�.
	m_D3D->EndScene();

	return true;
}