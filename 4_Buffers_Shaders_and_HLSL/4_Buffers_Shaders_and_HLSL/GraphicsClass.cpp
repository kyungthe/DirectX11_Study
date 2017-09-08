////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "GraphicsClass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_ColorShader = 0;
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

	// ī�޶� ��ü�� �����մϴ�.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// ī�޶� ��ġ�� �����մϴ�.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// �� ��ü�� �����մϴ�.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// �� ��ü�� �ʱ�ȭ�մϴ�.
	result = m_Model->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// ColorShader ��ü�� �����մϴ�.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// ColorShader ��ü�� �ʱ�ȭ�մϴ�.
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}

void GraphicsClass::Shutdown()
{
	// ColorShader ��ü�� ��ȯ�մϴ�.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// �� ��ü�� ��ȯ�մϴ�.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// ī�޶� ��ü�� ��ȯ�մϴ�.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

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

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;

	// ���� �����ϱ� ���� ���۸� ���ϴ�.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// ���ۿ� �׷��� ���� ȭ�鿡 ǥ���մϴ�.
	m_D3D->EndScene();

	return true;
}