#include "stdafx.h"
#include "SceneManager.h"
#include "StartScene.h" // ���� ��

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::ChangeScene(SceneType type, ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	if (SceneType::END == type) {
		PostQuitMessage(0); // ���� �޽��� ����
		return;
	}

	if (currentScene) currentScene->ReleaseObjects();
	currentScene = CreateScene(type);
	// ������ ī�޶� ���� , �÷��̾ �ʿ�� ����
	if (currentScene) currentScene->BuildObjects(pd3dDevice, pd3dCommandList);
}

void SceneManager::Update(float dt)
{
	if (currentScene) currentScene->AnimateObjects(dt); // ���� ���� Update �Լ� ȣ��
}

void SceneManager::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{
	if (currentScene) currentScene->Render(pd3dCommandList); // ���� HDC����
}

void SceneManager::OnProcessingMouseMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void SceneManager::OnProcessingKeyboardMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void SceneManager::ReleaseUploadBuffers()
{
	if (currentScene) currentScene->ReleaseUploadBuffers();
}

std::unique_ptr<Scene> SceneManager::CreateScene(SceneType type)
{
	switch (type) {
	case START: return std::make_unique<StartScene>(); // �޴� ��
	//case MENU: return std::make_unique<MenuScene>(); // ���� ��
	//case START:
	//case LEVEL1: return std::make_unique<RollerCoasterScene>(); // 
	//case LEVEL2: return std::make_unique<TankScene>(); // ��� ��
	default: return nullptr; // �߸��� �� Ÿ���� ��� null ��ȯ
	}
}
