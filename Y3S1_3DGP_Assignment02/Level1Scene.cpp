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

	//루트 파라미터를 설정한다.
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
		/* 앱에서 Input Assempler(꼭짓점 버퍼 바인딩 집합을 정의하는 입력 레이아웃 필요)를 선택하고 있습니다.
		이 플래그를 생략하면 일부 하드웨어에서 하나의 루트 인수 공간이 절약될 수 있습니다.
		최적화가 미미하지만 Input Assempler가 필요하지 않다면 이 플래그를 생략하십시오. */
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |

		/* 루트 서명에 대한 ** 셰이더 액세스를 거부합니다. */
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

	//루트 시그너쳐를 생성한다. 
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

	//그래픽 루트 시그너쳐를 생성한다. 
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

	// 플레이어 설정
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
		//마우스가 눌려지면 마우스 픽킹을 하여 선택한 게임 객체를 찾는다.
		m_pSelectedObject = PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pCamera);
		if (m_pSelectedObject) SceneManager::GetInstance().ChangeScene(SceneType::START);

		//마우스 캡쳐를 하고 현재 마우스 위치를 가져온다. 
		::SetCapture(hWnd);
		::GetCursorPos(&m_ptOldCursorPos);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		//마우스 캡쳐를 해제한다. 
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

	//플레이어를 실제로 이동하고 카메라를 갱신한다. 중력과 마찰력의 영향을 속도 벡터에 적용한다.
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

	// 방향 벡터 계산
	XMFLOAT3 pos = m_pPlayer->GetPosition();
	XMFLOAT3 tgt = target;
	XMFLOAT3 dir = Vector3::Subtract(tgt, pos);
	float distance = Vector3::Length(dir);


	if (distance < 1.0f) {
		// 타겟에 도달 → 다음 타겟으로 변경
		currentTargetIndex++;
		if (currentTargetIndex >= targets.size())
			currentTargetIndex = 0; // 반복 순환 가능
		return;
	}

	// 방향 정규화
	XMFLOAT3 dirNormalized = Vector3::Normalize(dir);

	float moveDist = 100.f * fTimeElapsed;
	XMFLOAT3 movement = Vector3::ScalarProduct(dirNormalized, moveDist);  // 정규화 후 이동 벡터 계산


	// Yaw 계산
	float yaw = XMConvertToDegrees(atan2f(dirNormalized.x, dirNormalized.z));

	// Pitch 계산 (원하면)
	float horizontalLen = sqrtf(dirNormalized.x * dirNormalized.x + dirNormalized.z * dirNormalized.z);
	float pitch = XMConvertToDegrees(atan2f(dirNormalized.y, horizontalLen));

	float yawDelta = yaw - m_pPlayer->GetYaw();       // GetYaw()는 현재 방향 (직접 만들 수도 있음)
	float pitchDelta = pitch - m_pPlayer->GetPitch(); // 선택사항

	// 새 위치 계산
	m_pPlayer->Rotate(pitchDelta, yawDelta, 0.0f);
	m_pPlayer->Move(movement, false);
}
void Level1Scene::Render(ID3D12GraphicsCommandList* pd3dCommandList)
{

	m_pCamera->SetViewportsAndScissorRects(pd3dCommandList);

	//그래픽 루트 시그너쳐를 파이프라인에 연결(설정)한다. 
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	if (m_pCamera) m_pCamera->UpdateShaderVariables(pd3dCommandList);

	//씬을 렌더링하는 것은 씬을 구성하는 게임 객체(셰이더를 포함하는 객체)들을 렌더링하는 것이다. 
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].Render(pd3dCommandList, m_pCamera);
	}

	// 3인칭 카메라일 때 플레이어가 항상 보이도록 렌더링한다. 
#ifdef _WITH_PLAYER_TOP
	//렌더 타겟은 그대로 두고 깊이 버퍼를 1.0으로 지우고 플레이어를 렌더링하면 플레이어는 무조건 그려질 것이다. 
	m_pd3dCommandList->ClearDepthStencilView(d3dDsvCPUDescriptorHandle, 
		D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, NULL);
#endif
	//3인칭 카메라일 때 플레이어를 렌더링한다. 
	if (m_pPlayer) m_pPlayer->Render(pd3dCommandList, m_pCamera);
}