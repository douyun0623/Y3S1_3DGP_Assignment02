#include "SceneManager.h"
#include "StartScene.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::InitScenes()
{
	// �� ��� ������ ���⿡ �ۼ��մϴ�.
	m_Scenes[SceneType::START] = std::make_shared<StartScene>();

	/* m_Scenes[SceneType::LEVEL1] = std::make_unique<Level1Scene>();
	 m_Scenes[SceneType::LEVEL2] = std::make_unique<Level2Scene>();*/
}


void SceneManager::ChangeScene(SceneType newType)
{
	m_CurrentScene = newType;
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() const
{
	return m_Scenes.at(m_CurrentScene);
}
