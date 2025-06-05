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

    // ���콺�� Ű���� �޽��� ó��
    virtual bool ProcessMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    virtual bool ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
    virtual bool ProcessInput() = 0;

    virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList) = 0;
    virtual void ReleaseObjects() = 0;
    
    virtual void AnimateObjects(float fElapsedTime) = 0;

    virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera) = 0;

    void ReleaseUploadBuffers();

    //�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
    virtual ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
    ID3D12RootSignature* GetGraphicsRootSignature();


protected:
    //��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�. 
    CObjectsShader* m_pShaders = NULL;
    int m_nShaders = 0;

    //��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�. 
    ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
};

