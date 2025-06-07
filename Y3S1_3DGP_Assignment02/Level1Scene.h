#pragma once
#include "Scene.h"
#include <vector>

class Level1Scene : public Scene
{
public:
	Level1Scene();
	~Level1Scene();

	void BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND m_hWnd) override;
	void ReleaseObjects() override;


	void AnimateObjects(float fTimeElapsed) override;
	void Render(ID3D12GraphicsCommandList* pd3dCommandList) override;

	//씬에서 마우스와 키보드 메시지를 처리한다. 
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM	lParam)override;
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)override;

	void ReleaseUploadBuffers()override;

	//그래픽 루트 시그너쳐를 생성한다. 
	ID3D12RootSignature* CreateGraphicsRootSignature(ID3D12Device* pd3dDevice) override;
	ID3D12RootSignature* GetGraphicsRootSignature()override;

	// 레일 따라가는 함수
	void moveToRail(float fTimeElapsed);

	int currentTargetIndex = 0;
	std::vector<XMFLOAT3> targets;
};

