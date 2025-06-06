#pragma once
#include "Scene.h"	

class StartScene : public Scene
{
public:
    // 마우스와 키보드 메시지 처리
    //bool ProcessMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    //bool ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    //bool ProcessInput();

    void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
    void ReleaseObjects();

    void AnimateObjects(float fElapsedTime);

    // 자기가 가진 카메라로 렌더링 or player 카메라로 렌더링(모든 씬은 이와 같이 렌더링 될거라서 기본 랜더링을 이용하도록 하겠다.)
    virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList);

    void ReleaseUploadBuffers();

    //그래픽 루트 시그너쳐를 생성한다. 
    ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
};

