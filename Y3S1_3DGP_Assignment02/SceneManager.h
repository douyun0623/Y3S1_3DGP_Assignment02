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
private:
    std::unique_ptr<CScene> currentScene;                    // 현재 씬

public:
    SceneManager() = default;

    static SceneManager& GetInstance(); // 싱글톤 접근

    void ChangeScene(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND m_hWnd, SceneType type);   // 씬 전환
    void Update(float dt);              // 씬 업데이트 (로직)
    void Render(ID3D12GraphicsCommandList* pd3dCommandList);    // 씬 렌더링 (그리기)

    // 입력 처리             
    void OnProcessingMouseMessage(HWND m_hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
    void OnProcessingKeyboardMessage(HWND m_hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

    // 현재 씬의 업로드 버퍼 해제
	void ReleaseUploadBuffers() {if (currentScene) currentScene->ReleaseUploadBuffers(); }

private:
    std::unique_ptr<CScene> CreateScene(SceneType type);  // 씬 생성 팩토리
};
