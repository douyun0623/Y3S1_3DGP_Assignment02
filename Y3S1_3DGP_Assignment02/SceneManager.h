#pragma once
#include <unordered_map>  
#include <memory>
#include "Scene.h"

enum class SceneType {
    START,
    MENU,
    LEVEL1,
    LEVEL2
};

class SceneManager {
private:
    std::unordered_map<SceneType, std::shared_ptr<Scene>> m_Scenes;
    SceneType m_CurrentScene = SceneType::START;

public:
    static SceneManager& GetInstance();

    void InitScenes(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND m_hWnd); // 씬 등록만 담당
    void ChangeScene(SceneType newType);
    std::shared_ptr<Scene> GetCurrentScene() const;
};


