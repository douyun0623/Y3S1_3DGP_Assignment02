#include "stdafx.h"
#include "Scene.h"

bool Scene::ProcessMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return false;
}

bool Scene::ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return false;
}

bool Scene::ProcessInput()
{
	return false;
}

void Scene::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{
	m_pCamera->SetViewportsAndScissorRects(pd3dCommandList);

	//�׷��� ��Ʈ �ñ׳��ĸ� ���������ο� ����(����)�Ѵ�. 
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	if (m_pCamera) m_pCamera->UpdateShaderVariables(pd3dCommandList);

	//���� �������ϴ� ���� ���� �����ϴ� ���� ��ü(���̴��� �����ϴ� ��ü)���� �������ϴ� ���̴�. 
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].Render(pd3dCommandList, m_pCamera);
	}
}

void Scene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseUploadBuffers();
}

ID3D12RootSignature* Scene::GetGraphicsRootSignature()
{
	return(m_pd3dGraphicsRootSignature);
}
