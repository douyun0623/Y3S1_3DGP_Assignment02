#pragma once
#include "Timer.h"
//#include "GameObject.h"
#include "Shader.h"

class CCamera;

class Scene
{
public:
    // Scene();
    ~Scene() = default;

    // 마우스와 키보드 메시지 처리
    virtual bool ProcessMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual bool ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual bool ProcessInput();

    virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList) = 0;
    virtual void ReleaseObjects() = 0;
    
    virtual void AnimateObjects(float fElapsedTime) = 0;

    // 자기가 가진 카메라로 렌더링 or player 카메라로 렌더링(모든 씬은 이와 같이 렌더링 될거라서 기본 랜더링을 이용하도록 하겠다.)
    virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList);

    void ReleaseUploadBuffers();

    //그래픽 루트 시그너쳐를 생성한다. 
    virtual ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice) = 0;
    ID3D12RootSignature* GetGraphicsRootSignature();


protected:
    //배치(Batch) 처리를 하기 위하여 씬을 셰이더들의 리스트로 표현한다. 
    CObjectsShader* m_pShaders = NULL;
    int m_nShaders = 0;

    //루트 시그너쳐를 나타내는 인터페이스 포인터이다. 
    ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;

    CCamera* m_pCamera = nullptr;
};

