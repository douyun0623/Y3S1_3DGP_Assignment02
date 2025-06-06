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

    // ���콺�� Ű���� �޽��� ó��
    virtual bool ProcessMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual bool ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual bool ProcessInput();

    virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList) = 0;
    virtual void ReleaseObjects() = 0;
    
    virtual void AnimateObjects(float fElapsedTime) = 0;

    // �ڱⰡ ���� ī�޶�� ������ or player ī�޶�� ������(��� ���� �̿� ���� ������ �ɰŶ� �⺻ �������� �̿��ϵ��� �ϰڴ�.)
    virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList);

    void ReleaseUploadBuffers();

    //�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
    virtual ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice) = 0;
    ID3D12RootSignature* GetGraphicsRootSignature();


protected:
    //��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�. 
    CObjectsShader* m_pShaders = NULL;
    int m_nShaders = 0;

    //��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�. 
    ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;

    CCamera* m_pCamera = nullptr;
};

