#pragma once
#include <memory>
#include "Scene.h"


enum SceneType {
    START,      // 시작 화면
    MENU,       // 메뉴 화면
    LEVEL1,     // 1단계
    LEVEL2,     // 2단계
    END         // 종료
};

class SceneManager
{
public:
    static SceneManager& GetInstance(); // 싱글톤 접근

    void ChangeScene(SceneType type, ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);   // 씬 전환
    void Update(float dt);              // 씬 업데이트 (로직)
    void Render(ID3D12GraphicsCommandList* pd3dCommandList);    // 씬 렌더링 (그리기), scene이 카메라를 가지도록 해야할것
    void OnProcessingMouseMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam);
    void OnProcessingKeyboardMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam);
    void ReleaseUploadBuffers();

private:
    SceneManager() = default;
    std::unique_ptr<Scene> currentScene;         // 현재 씬
    std::unique_ptr<Scene> CreateScene(SceneType type);  // 씬 생성 팩토리
};

