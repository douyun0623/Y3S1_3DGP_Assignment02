#include "stdafx.h"
#include "Level1Scene.h"
#include "SceneManager.h"

float Clamp(float value, float minVal, float maxVal)
{
	return (value < minVal) ? minVal : (value > maxVal) ? maxVal : value;
}

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
		XMFLOAT3(-1, -2, 0),
		XMFLOAT3(-1, -1, 2),
		XMFLOAT3(-1, 0, 4),
		XMFLOAT3(-1, 1, 6),
		XMFLOAT3(-1, 2, 8),
		XMFLOAT3(-1, 3, 10),
		XMFLOAT3(-1, 4, 12),
		XMFLOAT3(-1, 5, 14),
		XMFLOAT3(-1, 7, 16),
		XMFLOAT3(-1, 9, 18),
		XMFLOAT3(-1, 11, 20),
		XMFLOAT3(-1, 13, 22),
		XMFLOAT3(-1, 15, 24),
		XMFLOAT3(-1, 17, 26),
		XMFLOAT3(-1, 19, 28),
		XMFLOAT3(-1, 21, 30),
		XMFLOAT3(-1, 21, 32),
		XMFLOAT3(-1, 21, 34),
		XMFLOAT3(-1, 21, 36),
		XMFLOAT3(-1, 21, 38),
		XMFLOAT3(-1, 21, 40),
		XMFLOAT3(-3, 21, 40),
		XMFLOAT3(-5, 21, 40),
		XMFLOAT3(-7, 21, 40),
		XMFLOAT3(-9, 21, 40),
		XMFLOAT3(-11, 21, 40),
		XMFLOAT3(-13, 21, 40),
		XMFLOAT3(-15, 21, 40),
		XMFLOAT3(-17, 21, 40),
		XMFLOAT3(-19, 21, 40),
		XMFLOAT3(-21, 21, 40),
		XMFLOAT3(-23, 21, 40),
		XMFLOAT3(-25, 21, 40),
		XMFLOAT3(-27, 21, 40),
		XMFLOAT3(-29, 21, 40),
		XMFLOAT3(-31, 21, 40),
		XMFLOAT3(-33, 21, 40),
		XMFLOAT3(-33, 21, 42),
		XMFLOAT3(-33, 21, 44),
		XMFLOAT3(-33, 21, 46),
		XMFLOAT3(-33, 21, 48),
		XMFLOAT3(-33, 19, 50),
		XMFLOAT3(-33, 17, 52),
		XMFLOAT3(-33, 15, 54),
		XMFLOAT3(-33, 13, 56),
		XMFLOAT3(-33, 11, 58),
		XMFLOAT3(-33, 9, 60),
		XMFLOAT3(-33, 7, 62),
		XMFLOAT3(-33, 5, 64),
		XMFLOAT3(-33, 3, 66),
		XMFLOAT3(-33, 3, 68),
		XMFLOAT3(-33, 3, 70),
		XMFLOAT3(-33, 3, 72),
		XMFLOAT3(-33, 3, 74),
		XMFLOAT3(-31, 3, 74),
		XMFLOAT3(-29, 3, 74),
		XMFLOAT3(-25, 3, 74),
		XMFLOAT3(-23, 3, 74),
		XMFLOAT3(-21, 3, 74),
		XMFLOAT3(-19, 3, 74),
		XMFLOAT3(-17, 3, 74),
		XMFLOAT3(-15, 3, 74),
		XMFLOAT3(-13, 3, 74),
		XMFLOAT3(-11, 3, 74),
		XMFLOAT3(-9, 5, 74),
		XMFLOAT3(-7, 7, 76),
		XMFLOAT3(-5, 9, 78),
		XMFLOAT3(-3, 11, 80),
		XMFLOAT3(-1, 13, 82),
		XMFLOAT3(1, 15, 84),
		XMFLOAT3(3, 17, 86),
		XMFLOAT3(3, 19, 88),
		XMFLOAT3(3, 21, 90),
		XMFLOAT3(3, 23, 92),
		XMFLOAT3(3, 25, 94),
		XMFLOAT3(3, 27, 96),
		XMFLOAT3(3, 29, 98),
		XMFLOAT3(3, 31, 100),
		XMFLOAT3(3, 33, 102),
		XMFLOAT3(3, 35, 104),
		XMFLOAT3(3, 37, 106),
		XMFLOAT3(3, 39, 108),
		XMFLOAT3(3, 41, 110),
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
	XMFLOAT3 pos = m_pPlayer->GetPosition();
	XMFLOAT3 dir = Vector3::Subtract(target, pos);
	float distance = Vector3::Length(dir);

	if (distance < 1.0f) {
		currentTargetIndex++;
		if (currentTargetIndex >= targets.size()) {
			currentTargetIndex = 0;
			SceneManager::GetInstance().ChangeScene(SceneType::LEVEL2);
		}

		return;
	}

	// 방향 정규화
	XMFLOAT3 dirNormalized = Vector3::Normalize(dir);

	// 목표 Yaw 계산
	float targetYaw = XMConvertToDegrees(atan2f(dirNormalized.x, dirNormalized.z));
	float currentYaw = m_pPlayer->GetYaw();

	// Yaw 보간 (회전 속도 제한)
	float maxTurnSpeed = 90.0f * fTimeElapsed; // 초당 90도 회전 가능
	float deltaYaw = targetYaw - currentYaw;

	// [-180, 180] 범위로 조정
	while (deltaYaw > 180.0f) deltaYaw -= 360.0f;
	while (deltaYaw < -180.0f) deltaYaw += 360.0f;

	// 실제로 회전할 값 계산 (보간)
	float yawToApply = Clamp(deltaYaw, -maxTurnSpeed, maxTurnSpeed);
	float newYaw = currentYaw + yawToApply;
	m_pPlayer->Rotate(0, yawToApply, 0); // 또는 Rotate로 구현되어 있다면 Rotate(0, yawToApply, 0);

	// 이동
	float moveDist = 30.f * fTimeElapsed;
	XMFLOAT3 movement = Vector3::ScalarProduct(dirNormalized, moveDist);
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