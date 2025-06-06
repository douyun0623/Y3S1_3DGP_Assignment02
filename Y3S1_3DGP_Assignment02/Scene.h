#pragma once
#include "Timer.h"
//#include "GameObject.h"
#include "Shader.h"
#include "Player.h"

class CCamera;

class CScene
{
public:
	CScene();
	~CScene() {}

	//������ ���콺�� Ű���� �޽����� ó���Ѵ�. 
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM
		lParam);

	
	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND m_hWnd);
	void ReleaseObjects();

	bool ProcessInput(float fTimeElapsed);

	void AnimateObjects(float fTimeElapsed);

	void Render(ID3D12GraphicsCommandList* pd3dCommandList);

	void ReleaseUploadBuffers();

	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device *pd3dDevice);
	ID3D12RootSignature* GetGraphicsRootSignature();

	// 
	void ProcessSelectedObject(DWORD dwDirection, float cxDelta, float cyDelta);

public:
	CPlayer* m_pPlayer = NULL;
	CCamera* m_pCamera = NULL;

	//���� ��� ���� ��ü�鿡 ���� ���콺 ��ŷ�� �����Ѵ�. 
	CGameObject* PickObjectPointedByCursor(int xClient, int yClient, CCamera *pCamera);

	//���������� ���콺 ��ư�� Ŭ���� ���� ���콺 Ŀ���� ��ġ�̴�. 
	POINT m_ptOldCursorPos;

	HWND m_hWnd = NULL;

	CGameObject* m_pSelectedObject = NULL;

protected:
	//��ġ(Batch) ó���� �ϱ� ���Ͽ� ���� ���̴����� ����Ʈ�� ǥ���Ѵ�. 
	CObjectsShader *m_pShaders = NULL;
	int m_nShaders = 0;

	//��Ʈ �ñ׳��ĸ� ��Ÿ���� �������̽� �������̴�. 
	ID3D12RootSignature* m_pd3dGraphicsRootSignature = NULL;
	
};

