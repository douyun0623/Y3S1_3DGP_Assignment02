#include "stdafx.h"
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"

CGameObject::CGameObject()
{
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
}

CGameObject::~CGameObject()
{
	if (m_pMesh) m_pMesh->Release();
	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CGameObject::SetShader(CShader* pShader)
{
	if (m_pShader) m_pShader->Release();
	m_pShader = pShader;
	if (m_pShader) m_pShader->AddRef();
}

void CGameObject::SetMesh(CMesh* pMesh)
{
	if (m_pMesh) m_pMesh->Release();
	m_pMesh = pMesh;
	if (m_pMesh) m_pMesh->AddRef();
}

void CGameObject::ReleaseUploadBuffers()
{
	//정점 버퍼를 위한 업로드 버퍼를 소멸시킨다. 
	if (m_pMesh) m_pMesh->ReleaseUploadBuffers();
}

void CGameObject::Animate(float fTimeElapsed)
{

}

void CGameObject::OnPrepareRender()
{

}


void CGameObject::Rotate(XMFLOAT3* pxmf3Axis, float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(pxmf3Axis),
		XMConvertToRadians(fAngle));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	//게임 객체가 카메라에 보이면 렌더링한다.
	if (IsVisible(pCamera))
	{
		//객체의 정보를 셰이더 변수(상수 버퍼)로 복사한다. 
		UpdateShaderVariables(pd3dCommandList);
		// if (m_pShader) m_pShader->Render(pd3dCommandList, pCamera); 배치 처리에 의해 셰이더 렌더를 처리하고 오브젝트를 렌더함
		if (m_pMesh) m_pMesh->Render(pd3dCommandList);
	}
}

void CGameObject::CreateShaderVariables(ID3D12Device* pd3dDevice,
	ID3D12GraphicsCommandList* pd3dCommandList)
{

}

void CGameObject::ReleaseShaderVariables()
{

}

void CGameObject::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));
	
	//객체의 월드 변환 행렬을 루트 상수(32-비트 값)를 통하여 셰이더 변수(상수 버퍼)로 복사한다. 
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3 xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}

XMFLOAT3 CGameObject::GetPosition()
{
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

//게임 객체의 로컬 z-축 벡터를 반환한다. 
XMFLOAT3 CGameObject::GetLook() const
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._31, m_xmf4x4World._32,
		m_xmf4x4World._33)));
}

//게임 객체의 로컬 y-축 벡터를 반환한다. 
XMFLOAT3 CGameObject::GetUp()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._21, m_xmf4x4World._22,
		m_xmf4x4World._23)));
}

//게임 객체의 로컬 x-축 벡터를 반환한다. 
XMFLOAT3 CGameObject::GetRight()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._11, m_xmf4x4World._12,
		m_xmf4x4World._13)));
}

//게임 객체를 로컬 x-축 방향으로 이동한다. 
void CGameObject::MoveStrafe(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

//게임 객체를 로컬 y-축 방향으로 이동한다. 
void CGameObject::MoveUp(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

//게임 객체를 로컬 z-축 방향으로 이동한다. 
void CGameObject::MoveForward(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

//게임 객체를 주어진 각도로 회전한다. 
void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch),
		XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

bool CGameObject::IsVisible(CCamera* pCamera)
{
	OnPrepareRender();

	bool bIsVisible = false;
	BoundingOrientedBox xmBoundingBox = m_pMesh->GetBoundingBox();

	//모델 좌표계의 바운딩 박스를 월드 좌표계로 변환한다.
	xmBoundingBox.Transform(xmBoundingBox, XMLoadFloat4x4(&m_xmf4x4World));

	if (pCamera) bIsVisible = pCamera->IsInFrustum(xmBoundingBox);

	return(bIsVisible);
}

void CGameObject::GenerateRayForPicking(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4&
	xmf4x4View, XMFLOAT3* pxmf3PickRayOrigin, XMFLOAT3* pxmf3PickRayDirection)
{
	XMFLOAT4X4 xmf4x4WorldView = Matrix4x4::Multiply(m_xmf4x4World, xmf4x4View);
	XMFLOAT4X4 xmf4x4Inverse = Matrix4x4::Inverse(xmf4x4WorldView);
	XMFLOAT3 xmf3CameraOrigin(0.0f, 0.0f, 0.0f);

	//카메라 좌표계의 원점을 모델 좌표계로 변환한다. 
	*pxmf3PickRayOrigin = Vector3::TransformCoord(xmf3CameraOrigin, xmf4x4Inverse);

	//카메라 좌표계의 점(마우스 좌표를 역변환하여 구한 점)을 모델 좌표계로 변환한다.
	*pxmf3PickRayDirection= Vector3::TransformCoord(xmf3PickPosition, xmf4x4Inverse);

	//광선의 방향 벡터를 구한다. 
	*pxmf3PickRayDirection = Vector3::Normalize(Vector3::Subtract(*pxmf3PickRayDirection, *pxmf3PickRayOrigin));
}

int CGameObject::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4&
	xmf4x4View, float* pfHitDistance)
{
	int nIntersected = 0;
	if (m_pMesh)
	{
		XMFLOAT3 xmf3PickRayOrigin, xmf3PickRayDirection;
		//모델 좌표계의 광선을 생성한다.
		GenerateRayForPicking(xmf3PickPosition, xmf4x4View, &xmf3PickRayOrigin, &xmf3PickRayDirection);

		//모델 좌표계의 광선과 메쉬의 교차를 검사한다.
		nIntersected = m_pMesh->CheckRayIntersection(xmf3PickRayOrigin,
		xmf3PickRayDirection, pfHitDistance);
	}
	return(nIntersected);
}

//------------------------------------------------------------------------------------------------
//----------------------------------------CRotatingObject-----------------------------------------
//------------------------------------------------------------------------------------------------

CRotatingObject::CRotatingObject()
{
	m_xmf3RotationAxis = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotationSpeed = 90.0f;
}

CRotatingObject::~CRotatingObject()
{

}

void CRotatingObject::Animate(float fTimeElapsed)
{
	CGameObject::Rotate(&m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
}

//------------------------------------------------------------------------------------------------
//----------------------------------------CTankObject-----------------------------------------
//------------------------------------------------------------------------------------------------


void CTankObject::Animate(float fTimeElapsed)
{
    m_fDirectionChangeTime += fTimeElapsed;

    // 일정 시간마다 목표 회전각 설정 (-180 ~ +180도)
    if (m_fDirectionChangeTime >= m_fDirectionChangeInterval)
    {
        int angleDeg = (rand() % 45) - 25;
        m_fTargetYaw = angleDeg * 0.0174533f;
        m_fDirectionChangeTime = 0.0f;
    }

    // 부드러운 회전을 위해 선형 보간 (lerp)
    float fLerpSpeed = m_fRotationLerpSpeed * fTimeElapsed;
    if (fLerpSpeed > 1.0f) fLerpSpeed = 1.0f;

    // 보간된 회전 적용
    m_fCurrentYaw = m_fCurrentYaw + (m_fTargetYaw - m_fCurrentYaw) * fLerpSpeed;
    Rotate(0.0f, m_fCurrentYaw, 0.0f);  // 절대 회전 적용

    // 이동
    XMFLOAT3 dir = GetLook();
    XMFLOAT3 moveDir = Vector3::ScalarProduct(dir, m_fMoveSpeed * fTimeElapsed);
    SetPosition(Vector3::Add(GetPosition(), moveDir));
}

//------------------------------------------------------------------------------------------------
//----------------------------------------CBulletObject-----------------------------------------
//------------------------------------------------------------------------------------------------


CBulletObject::CBulletObject()
{
}

CBulletObject::~CBulletObject()
{
}

void CBulletObject::Animate(float fTimeElapsed)
{
	//// 1. 플레이어 위치 추출
	//XMFLOAT3 playerPos = XMFLOAT3(playerWorld._41, playerWorld._42, playerWorld._43);

	//// 2. 플레이어 Look 벡터 (Z축 방향)
	//XMFLOAT3 lookDir = XMFLOAT3(playerWorld._31, playerWorld._32, playerWorld._33);
	//lookDir = Vector3::Normalize(lookDir);

	// 3. 총알 위치가 아직 초기화되지 않았다면 → 플레이어 위치로 설정
	//if (moveable) {
	//	reset(playerWorld);
	//}

	if(moveable){
		// 4. 총알 이동 (look 방향으로)
		XMFLOAT3 moveDir = Vector3::ScalarProduct(lookDir, bulletSpeed * fTimeElapsed);
		SetPosition(Vector3::Add(GetPosition(), moveDir));
	}
}

void CBulletObject::reset(XMFLOAT3 position, XMFLOAT3 dir)
{

	// 총알 위치와 방향 초기화
	SetPosition(position);

	// 플레이어의 정면 방향 (행렬의 3번째 행)
	lookDir = Vector3::Normalize(dir);

	moveable = true; // 총알이 움직일 수 있는 상태로 설정
}
