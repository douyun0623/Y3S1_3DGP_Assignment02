#pragma once
#include "Timer.h"
//#include "GameObject.h"
#include "Shader.h"

class CCamera;

class Scene
{
public:
    Scene();
    virtual ~Scene() = default;

    // 마우스와 키보드 메시지 처리
    virtual bool ProcessMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    virtual bool ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    virtual bool ProcessInput() = 0;

    virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList) = 0;
    virtual void ReleaseObjects() = 0;
    
    virtual void AnimateObjects(float fElapsedTime) = 0;

    virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera) = 0;

    void ReleaseUploadBuffers();

    //그래픽 루트 시그너쳐를 생성한다. 
    virtual ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
    ID3D12RootSignature* GetGraphicsRootSignature();


protected:
    //배치(Batch) 처리를 하기 위하여 씬을 셰이더들의 리스트로 표현한다. 
    CObjectsShader* m_pShaders = NULL;
    int m_nShaders = 0;

    //루트 시그너쳐를 나타내는 인터페이스 포인터이다. 
    ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
};

