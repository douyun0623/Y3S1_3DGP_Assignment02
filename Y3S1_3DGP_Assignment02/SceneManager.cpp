#include "SceneManager.h"
#include "Scene.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::init(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND hWnd)
{
	m_pd3dDevice = pd3dDevice; // Direct3D ����̽� �ʱ�ȭ
	m_pd3dCommandList = pd3dCommandList; // ��� ����Ʈ �ʱ�ȭ
	this->m_hWnd = m_hWnd; // ������ �ڵ� �ʱ�ȭ
	// ���� ������ �ʱ�ȭ
	ChangeScene(SceneType::START);
}

void SceneManager::ChangeScene(SceneType type)
{
	if (SceneType::END == type) {
		PostQuitMessage(0); // ���� �޽��� ����
		return;
	}

	if (currentScene) {
		currentScene->ReleaseObjects(); // ���� ���� ��ü�� ����
		currentScene.reset(); // ���� �� ������ �ʱ�ȭ
	}
	currentScene = CreateScene(type);
	if (currentScene) currentScene->BuildObjects(m_pd3dDevice, m_pd3dCommandList, m_hWnd);
}

void SceneManager::Update(float dt)
{
	if (currentScene) currentScene->AnimateObjects(dt); // ���� ���� Update �Լ� ȣ��
}

void SceneManager::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{
	if (currentScene) currentScene->Render(pd3dCommandList); // ���� HDC����
}

void SceneManager::OnProcessingMouseMessage(HWND m_hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (currentScene) currentScene->OnProcessingMouseMessage(m_hWnd, nMessageID, wParam, lParam); // ���� ���� ���콺 �޽��� ó��
}

void SceneManager::OnProcessingKeyboardMessage(HWND m_hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (currentScene) currentScene->OnProcessingKeyboardMessage(m_hWnd, nMessageID, wParam, lParam); // ���� ���� ���콺 �޽��� ó��
}

std::unique_ptr<CScene> SceneManager::CreateScene(SceneType type)
{
	switch (type) {
	case START: return std::make_unique<CScene>(); // ���� ��
	//case MENU: return std::make_unique<MenuScene>(); // ���� ��
	//case LEVEL1: return std::make_unique<RollerCoasterScene>(); // 
	//case LEVEL2: return std::make_unique<TankScene>(); // ��� ��
	default: return nullptr; // �߸��� �� Ÿ���� ��� null ��ȯ
	}
}
