#include "stdafx.h"
#include "Level1Scene.h"
#include "SceneManager.h"

Level1Scene::Level1Scene()
{
}

Level1Scene::~Level1Scene()
{
	ReleaseObjects();
}

ID3D12RootSignature* Level1Scene::CreateGraphicsRootSignature(ID3D12Device* pd3dDevice)
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

void Level1Scene::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, HWND hWnd)
{
	m_hWnd = hWnd;

	//�׷��� ��Ʈ �ñ׳��ĸ� �����Ѵ�. 
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	targets = {
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(100.f, 0.f, 100.f),
		XMFLOAT3(100.f, 0.f, 200.f),
		XMFLOAT3(0.f, 0.f, 300.f),
		XMFLOAT3(0.f, 0.f, 400.f),
		XMFLOAT3(0.f, 0.f, 500.f),
		XMFLOAT3(0.f, 0.f, 600.f),
		XMFLOAT3(0.f, 0.f, 700.f),
		XMFLOAT3(0.f, 0.f, 800.f),
		XMFLOAT3(0.f, 0.f, 900.f),
		XMFLOAT3(0.f, 0.f, 1000.f),
		XMFLOAT3(0.f, 0.f, 1100.f),
		XMFLOAT3(0.f, 0.f, 1200.f),
		XMFLOAT3(0.f, 0.f, 1300.f)
	};

	m_nShaders = 1;
	m_pShaders = new CObjectsShader1[m_nShaders];
	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0].BuildObjects(pd3dDevice, pd3dCommandList);

	// �÷��̾� ����
	CPlayer* pAirplanePlayer = new CLevel1Player(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature);
	m_pPlayer = pAirplanePlayer;
	m_pPlayer->AddRef();
	m_pCamera = m_pPlayer->GetCamera();
}

void Level1Scene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].ReleaseShaderVariables();
		m_pShaders[i].ReleaseObjects();
	}
	if (m_pShaders) delete[] m_pShaders;
	if (m_pPlayer) m_pPlayer->Release();
}

bool Level1Scene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		//���콺�� �������� ���콺 ��ŷ�� �Ͽ� ������ ���� ��ü�� ã�´�.
		m_pSelectedObject = PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pCamera);
		if (m_pSelectedObject) SceneManager::GetInstance().ChangeScene(SceneType::START);

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

bool Level1Scene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

void Level1Scene::AnimateObjects(float fTimeElapsed)
{
	ProcessInput(fTimeElapsed);

	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].AnimateObjects(fTimeElapsed);
	}

	//�÷��̾ ������ �̵��ϰ� ī�޶� �����Ѵ�. �߷°� �������� ������ �ӵ� ���Ϳ� �����Ѵ�.
	// m_pPlayer->Move(DIR_FORWARD, 300.0f * fTimeElapsed, false);
	moveToRail(fTimeElapsed);
	m_pPlayer->Update(fTimeElapsed);
}

void Level1Scene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseUploadBuffers();
}

ID3D12RootSignature* Level1Scene::GetGraphicsRootSignature()
{
	return(m_pd3dGraphicsRootSignature);
}

void Level1Scene::moveToRail(float fTimeElapsed)
{
	if (targets.empty()) return;

	XMFLOAT3 target = targets[currentTargetIndex];

	// ���� ���� ���
	XMFLOAT3 pos = m_pPlayer->GetPosition();
	XMFLOAT3 tgt = target;
	XMFLOAT3 dir = Vector3::Subtract(tgt, pos);
	float distance = Vector3::Length(dir);


	if (distance < 1.0f) {
		// Ÿ�ٿ� ���� �� ���� Ÿ������ ����
		currentTargetIndex++;
		if (currentTargetIndex >= targets.size())
			currentTargetIndex = 0; // �ݺ� ��ȯ ����
		return;
	}

	// ���� ����ȭ
	XMFLOAT3 dirNormalized = Vector3::Normalize(dir);

	float moveDist = 100.f * fTimeElapsed;
	XMFLOAT3 movement = Vector3::ScalarProduct(dirNormalized, moveDist);  // ����ȭ �� �̵� ���� ���


	// Yaw ���
	float yaw = XMConvertToDegrees(atan2f(dirNormalized.x, dirNormalized.z));

	// Pitch ��� (���ϸ�)
	float horizontalLen = sqrtf(dirNormalized.x * dirNormalized.x + dirNormalized.z * dirNormalized.z);
	float pitch = XMConvertToDegrees(atan2f(dirNormalized.y, horizontalLen));

	float yawDelta = yaw - m_pPlayer->GetYaw();       // GetYaw()�� ���� ���� (���� ���� ���� ����)
	float pitchDelta = pitch - m_pPlayer->GetPitch(); // ���û���

	// �� ��ġ ���
	m_pPlayer->Rotate(pitchDelta, yawDelta, 0.0f);
	m_pPlayer->Move(movement, false);
}
void Level1Scene::Render(ID3D12GraphicsCommandList* pd3dCommandList)
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

	// 3��Ī ī�޶��� �� �÷��̾ �׻� ���̵��� �������Ѵ�. 
#ifdef _WITH_PLAYER_TOP
	//���� Ÿ���� �״�� �ΰ� ���� ���۸� 1.0���� ����� �÷��̾ �������ϸ� �÷��̾�� ������ �׷��� ���̴�. 
	m_pd3dCommandList->ClearDepthStencilView(d3dDsvCPUDescriptorHandle, 
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, NULL);
#endif
	//3��Ī ī�޶��� �� �÷��̾ �������Ѵ�. 
	if (m_pPlayer) m_pPlayer->Render(pd3dCommandList, m_pCamera);
}