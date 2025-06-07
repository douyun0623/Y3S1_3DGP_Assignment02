#pragma once

#include "stdafx.h"
#include "Camera.h"
#include "Shader.h"
#include "Player.h"

class Scene
{
public:
    Scene();
    virtual ~Scene();

    virtual void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND hWnd) = 0;
    virtual void ReleaseObjects() = 0;

    virtual void AnimateObjects(float fTimeElapsed) = 0;
    virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList) = 0;

    virtual bool ProcessInput(float fTimeElapsed);
    virtual bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
    virtual bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

    virtual void ReleaseUploadBuffers() = 0;

    virtual ID3D12RootSignature* GetGraphicsRootSignature();
    virtual CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera* pCamera);

protected:
    virtual ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice) = 0;
    virtual void ProcessSelectedObject(DWORD dwDirection, float cxDelta, float cyDelta);

protected:
    HWND m_hWnd;
    ID3D12RootSignature* m_pd3dGraphicsRootSignature = nullptr;

    CShader* m_pShaders = nullptr;
    int m_nShaders = 0;

    CPlayer* m_pPlayer = nullptr;
    CCamera* m_pCamera = nullptr;

    CGameObject* m_pSelectedObject = nullptr;
    POINT m_ptOldCursorPos{};
};

