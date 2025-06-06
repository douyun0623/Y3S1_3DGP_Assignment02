#pragma once
#include <memory>
#include "Scene.h"

enum SceneType {
    START,      // ���� ȭ��
    MENU,       // �޴� ȭ��
    LEVEL1,     // 1�ܰ�
    LEVEL2,     // 2�ܰ�
    END         // ����
};

class SceneManager
{
private:
    std::unique_ptr<CScene> currentScene;                    // ���� ��

public:
    SceneManager() = default;

    static SceneManager& GetInstance(); // �̱��� ����

    void ChangeScene(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND m_hWnd, SceneType type);   // �� ��ȯ
    void Update(float dt);              // �� ������Ʈ (����)
    void Render(ID3D12GraphicsCommandList* pd3dCommandList);    // �� ������ (�׸���)

    // �Է� ó��             
    void OnProcessingMouseMessage(HWND m_hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
    void OnProcessingKeyboardMessage(HWND m_hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

    // ���� ���� ���ε� ���� ����
	void ReleaseUploadBuffers() {if (currentScene) currentScene->ReleaseUploadBuffers(); }

private:
    std::unique_ptr<CScene> CreateScene(SceneType type);  // �� ���� ���丮
};
