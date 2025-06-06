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
public:
    static SceneManager& GetInstance(); // �̱��� ����

    void ChangeScene(SceneType type, ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);   // �� ��ȯ
    void Update(float dt);              // �� ������Ʈ (����)
    void Render(ID3D12GraphicsCommandList* pd3dCommandList);    // �� ������ (�׸���), scene�� ī�޶� �������� �ؾ��Ұ�
    void OnProcessingMouseMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam);
    void OnProcessingKeyboardMessage(UINT nMessageID, WPARAM wParam, LPARAM lParam);
    void ReleaseUploadBuffers();

private:
    SceneManager() = default;
    std::unique_ptr<Scene> currentScene;         // ���� ��
    std::unique_ptr<Scene> CreateScene(SceneType type);  // �� ���� ���丮
};

