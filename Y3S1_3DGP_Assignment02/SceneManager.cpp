#include "SceneManager.h"
#include "StartScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::InitScenes(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND m_hWnd)
{
	// 씬 등록 로직을 여기에 작성합니다.
	m_Scenes[SceneType::START] = std::make_shared<StartScene>();
	m_Scenes[SceneType::LEVEL1] = std::make_shared<Level1Scene>();
	m_Scenes[SceneType::LEVEL2] = std::make_shared<Level2Scene>();

	for (auto& scenePair : m_Scenes) {
		scenePair.second->BuildObjects(pd3dDevice, pd3dCommandList, m_hWnd);
	}
}


void SceneManager::ChangeScene(SceneType newType)
{
	m_CurrentScene = newType;
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() const
{
	return m_Scenes.at(m_CurrentScene);
}
