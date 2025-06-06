#pragma once
#include "Scene.h"	

class StartScene : public Scene
{
public:
    // ���콺�� Ű���� �޽��� ó��
    //bool ProcessMouseMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    //bool ProcessKeyboardMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    //bool ProcessInput();

    void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList);
    void ReleaseObjects();

    void AnimateObjects(float fElapsedTime);

    // �ڱⰡ ���� ī�޶�� ������ or player ī�޶�� ������(��� ���� �̿� ���� ������ �ɰŶ� �⺻ �������� �̿��ϵ��� �ϰڴ�.)
    virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList);

    void ReleaseUploadBuffers();

    //�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
    ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice);
};

