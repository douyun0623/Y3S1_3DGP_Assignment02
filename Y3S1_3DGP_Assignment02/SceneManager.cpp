#include "stdafx.h"
#include "SceneManager.h"
#include "StartScene.h" // 시작 씬

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::ChangeScene(SceneType type, ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	if (SceneType::END == type) {
		PostQuitMessage(0); // 종료 메시지 전송
		return;
	}

	if (currentScene) currentScene->ReleaseObjects();
	currentScene = CreateScene(type);
	// 생성시 카메라 관리 , 플레이어도 필요시 설정
	if (currentScene) currentScene->BuildObjects(pd3dDevice, pd3dCommandList);
}

void SceneManager::Update(float dt)
{
	if (currentScene) currentScene->AnimateObjects(dt); // 현재 씬의 Update 함수 호출
}

void SceneManager::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{
	if (currentScene) currentScene->Render(pd3dCommandList); // 씬에 HDC전달
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
	case START: return std::make_unique<StartScene>(); // 메뉴 씬
	//case MENU: return std::make_unique<MenuScene>(); // 게임 씬
	//case START:
	//case LEVEL1: return std::make_unique<RollerCoasterScene>(); // 
	//case LEVEL2: return std::make_unique<TankScene>(); // 결과 씬
	default: return nullptr; // 잘못된 씬 타입일 경우 null 반환
	}
}
