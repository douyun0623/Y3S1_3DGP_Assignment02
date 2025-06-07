#include "stdafx.h"
#include "Level2Scene.h"
#include "SceneManager.h"

Level2Scene::Level2Scene()
{
}

Level2Scene::~Level2Scene()
{
	ReleaseObjects();
}

ID3D12RootSignature* Level2Scene::CreateGraphicsRootSignature(ID3D12Device* pd3dDevice)
{
	ID3D12RootSignature* pd3dGraphicsRootSignature = NULL;

	//��Ʈ �Ķ���͸� �����Ѵ�.
	D3D12_ROOT_PARAMETER pd3dRootParameters[2];
	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[0].Constants.Num32BitValues = 16;
	pd3dRootParameters[0].Constants.ShaderRegister = 0;
	pd3dRootParameters[0].Constants.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 1;
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags =
		/* �ۿ��� Input Assempler(������ ���� ���ε� ������ �����ϴ� �Է� ���̾ƿ� �ʿ�)�� �����ϰ� �ֽ��ϴ�.
		�� �÷��׸� �����ϸ� �Ϻ� �ϵ����� �ϳ��� ��Ʈ �μ� ������ ����� �� �ֽ��ϴ�.
		����ȭ�� �̹������� Input Assempler�� �ʿ����� �ʴٸ� �� �÷��׸� �����Ͻʽÿ�. */
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |

		/* ��Ʈ ���� ���� ** ���̴� �׼����� �ź��մϴ�. */
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

	//��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob* pd3dSignatureBlob = NULL;
	ID3DBlob* pd3dErrorBlob = NULL;

	::D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		&pd3dSignatureBlob, &pd3dErrorBlob);

	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(),
		pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void**)&pd3dGraphicsRootSignature);

	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void Level2Scene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND hWnd)
{
	m_hWnd = hWnd;

	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	FloorShader = new CFloorShader[m_nFShaders];
	FloorShader[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	FloorShader[0].BuildObjects(pd3dDevice, pd3dCommandList);



	// �÷��̾� ����
	CPlayer* pAirplanePlayer = new CLevel2Player(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	m_pPlayer = pAirplanePlayer;
	m_pPlayer->AddRef();
	m_pCamera = m_pPlayer->GetCamera();
}

void Level2Scene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].ReleaseShaderVariables();
		m_pShaders[i].ReleaseObjects();
	}
	FloorShader[0].ReleaseShaderVariables();
	FloorShader[0].ReleaseObjects();
	if (m_pShaders) delete[] m_pShaders;
	if (m_pPlayer) m_pPlayer->Release();
}

bool Level2Scene::ProcessInput(float fTimeElapsed)
{
	static UCHAR pKeyBuffer[256];
	DWORD dwDirection = 0;
	/*Ű������ ���� ������ ��ȯ�Ѵ�. ȭ��ǥ Ű(���桯, ���硯, ���衯, ���顯)�� ������
	�÷��̾ ������/����(���� x-��), ��/��(���� z-��)�� �̵��Ѵ�.
	��Page Up���� ��Page Down�� Ű�� ������ �÷��̾ ��/�Ʒ�(���� y-��)�� �̵��Ѵ�.*/
	if (::GetKeyboardState(pKeyBuffer))
	{
		if (pKeyBuffer['W'] & 0xF0) dwDirection |= DIR_FORWARD;
		if (pKeyBuffer['S'] & 0xF0) dwDirection |= DIR_BACKWARD;
		if (pKeyBuffer['A'] & 0xF0) dwDirection |= DIR_LEFT;
		if (pKeyBuffer['D'] & 0xF0) dwDirection |= DIR_RIGHT;
		//if (pKeyBuffer['Q'] & 0xF0) dwDirection |= DIR_UP;
		//if (pKeyBuffer['E'] & 0xF0) dwDirection |= DIR_DOWN;
	}
	float cxDelta = 0.0f, cyDelta = 0.0f;
	POINT ptCursorPos;
	/*���콺�� ĸ�������� ���콺�� �󸶸�ŭ �̵��Ͽ��� ���� ����Ѵ�.
	  ���콺 ���� �Ǵ� ������ ��ư�� ������ ���� �޽���(WM_LBUTTONDOWN, WM_RBUTTONDOWN)�� ó���� �� ���콺�� ĸ���Ͽ���.
	  �׷��Ƿ� ���콺�� ĸ�ĵ� ���� ���콺 ��ư�� ������ ���¸� �ǹ��Ѵ�.
	  ���콺 ��ư�� ������ ���¿��� ���콺�� �¿� �Ǵ� ���Ϸ� �����̸� �÷��̾ x-�� �Ǵ� y-������ ȸ���Ѵ�.*/
	if (::GetCapture() == m_hWnd)
	{
		//���콺 Ŀ���� ȭ�鿡�� ���ش�(������ �ʰ� �Ѵ�).
		::SetCursor(NULL);

		//���� ���콺 Ŀ���� ��ġ�� �����´�. 
		::GetCursorPos(&ptCursorPos);

		//���콺 ��ư�� ���� ���¿��� ���콺�� ������ ���� ���Ѵ�. 
		cxDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
		cyDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;

		//���콺 Ŀ���� ��ġ�� ���콺�� �������� ��ġ�� �����Ѵ�. 
		::SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
	}

	//���콺 �Ǵ� Ű �Է��� ������ �÷��̾ �̵��ϰų�(dwDirection) ȸ���Ѵ�(cxDelta �Ǵ� cyDelta).
	if ((dwDirection != 0) || (cxDelta != 0.0f) || (cyDelta != 0.0f))
	{
		//��ŷ���� ������ ���� ��ü�� ������ Ű���带 �����ų� ���콺�� �����̸� ���� ��ü�� �̵� �Ǵ� ȸ���Ѵ�.
		if (m_pSelectedObject)
		{
			ProcessSelectedObject(dwDirection, cxDelta, cyDelta);
		}
		else
		{
			if (cxDelta || cyDelta)
			{
				/*cxDelta�� y-���� ȸ���� ��Ÿ���� cyDelta�� x-���� ȸ���� ��Ÿ����.
				  ������ ���콺 ��ư�� ������ ��� cxDelta�� z-���� ȸ���� ��Ÿ����.*/
				if (pKeyBuffer[VK_RBUTTON] & 0xF0)
					m_pPlayer->Rotate(cyDelta, 0.0f, -cxDelta);
				else
					m_pPlayer->Rotate(cyDelta, cxDelta, 0.0f);
			}
			/*�÷��̾ dwDirection �������� �̵��Ѵ�(�����δ� �ӵ� ���͸� �����Ѵ�).
			�̵� �Ÿ��� �ð��� ����ϵ��� �Ѵ�. */
			if (dwDirection) m_pPlayer->Move(dwDirection, 300.0f * fTimeElapsed, true);
		}
	}

	//�÷��̾ ������ �̵��ϰ� ī�޶� �����Ѵ�. �߷°� �������� ������ �ӵ� ���Ϳ� �����Ѵ�.
	m_pPlayer->Update(fTimeElapsed);

	return false;
}

bool Level2Scene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		//���콺�� �������� ���콺 ��ŷ�� �Ͽ� ������ ���� ��ü�� ã�´�.
		m_pSelectedObject = PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pCamera);

		//���콺 ĸ�ĸ� �ϰ� ���� ���콺 ��ġ�� �����´�. 
		::SetCapture(hWnd);
		::GetCursorPos(&m_ptOldCursorPos);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		//���콺 ĸ�ĸ� �����Ѵ�. 
		::ReleaseCapture();
		break;
	case WM_MOUSEMOVE:

		break;
	default:
		break;
	}

	return false;
}

bool Level2Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

void Level2Scene::AnimateObjects(float fTimeElapsed)
{
	ProcessInput(fTimeElapsed);

	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].AnimateObjects(fTimeElapsed);
	}
	
	m_pPlayer->Update(fTimeElapsed);
}

void Level2Scene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseUploadBuffers();
	if (FloorShader) FloorShader[0].ReleaseUploadBuffers();
}

ID3D12RootSignature* Level2Scene::GetGraphicsRootSignature()
{
	return(m_pd3dGraphicsRootSignature);
}

void Level2Scene::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{

	m_pCamera->SetViewportsAndScissorRects(pd3dCommandList);

	//�׷��� ��Ʈ �ñ׳��ĸ� ���������ο� ����(����)�Ѵ�. 
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	if (m_pCamera) m_pCamera->UpdateShaderVariables(pd3dCommandList);

	//���� �������ϴ� ���� ���� �����ϴ� ���� ��ü(���̴��� �����ϴ� ��ü)���� �������ϴ� ���̴�. 
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].Render(pd3dCommandList, m_pCamera);
	}
	FloorShader[0].Render(pd3dCommandList, m_pCamera);

	// 3��Ī ī�޶��� �� �÷��̾ �׻� ���̵��� �������Ѵ�. 
#ifdef _WITH_PLAYER_TOP
	//���� Ÿ���� �״�� �ΰ� ���� ���۸� 1.0���� ����� �÷��̾ �������ϸ� �÷��̾�� ������ �׷��� ���̴�. 
	m_pd3dCommandList->ClearDepthStencilView(d3dDsvCPUDescriptorHandle,
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, NULL);
#endif
	//3��Ī ī�޶��� �� �÷��̾ �������Ѵ�. 
	if (m_pPlayer) m_pPlayer->Render(pd3dCommandList, m_pCamera);
}