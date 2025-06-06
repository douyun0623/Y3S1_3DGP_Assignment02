#include "SceneManager.h"
#include "Scene.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::init(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND hWnd)
{
	m_pd3dDevice = pd3dDevice; // Direct3D 디바이스 초기화
	m_pd3dCommandList = pd3dCommandList; // 명령 리스트 초기화
	this->m_hWnd = m_hWnd; // 윈도우 핸들 초기화
	// 시작 씬으로 초기화
	ChangeScene(SceneType::START);
}

void SceneManager::ChangeScene(SceneType type)
{
	if (SceneType::END == type) {
		PostQuitMessage(0); // 종료 메시지 전송
		return;
	}

	if (currentScene) {
		currentScene->ReleaseObjects(); // 현재 씬의 객체들 해제
		currentScene.reset(); // 현재 씬 포인터 초기화
	}
	currentScene = CreateScene(type);
	if (currentScene) currentScene->BuildObjects(m_pd3dDevice, m_pd3dCommandList, m_hWnd);
}

void SceneManager::Update(float dt)
{
	if (currentScene) currentScene->AnimateObjects(dt); // 현재 씬의 Update 함수 호출
}

void SceneManager::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{
	if (currentScene) currentScene->Render(pd3dCommandList); // 씬에 HDC전달
}

void SceneManager::OnProcessingMouseMessage(HWND m_hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (currentScene) currentScene->OnProcessingMouseMessage(m_hWnd, nMessageID, wParam, lParam); // 현재 씬의 마우스 메시지 처리
}

void SceneManager::OnProcessingKeyboardMessage(HWND m_hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (currentScene) currentScene->OnProcessingKeyboardMessage(m_hWnd, nMessageID, wParam, lParam); // 현재 씬의 마우스 메시지 처리
}

std::unique_ptr<CScene> SceneManager::CreateScene(SceneType type)
{
	switch (type) {
	case START: return std::make_unique<CScene>(); // 시작 씬
	//case MENU: return std::make_unique<MenuScene>(); // 게임 씬
	//case LEVEL1: return std::make_unique<RollerCoasterScene>(); // 
	//case LEVEL2: return std::make_unique<TankScene>(); // 결과 씬
	default: return nullptr; // 잘못된 씬 타입일 경우 null 반환
	}
}
