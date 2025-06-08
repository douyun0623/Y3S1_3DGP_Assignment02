#pragma once
#include "Mesh.h"

class CShader;
class CCamera;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

private:
	int m_nReferences = 0;
public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

protected:
	XMFLOAT4X4 m_xmf4x4World;
	CMesh* m_pMesh = NULL;
	CShader* m_pShader = NULL;

public:
	void ReleaseUploadBuffers();

	virtual void SetMesh(CMesh* pMesh);
	virtual void SetShader(CShader* pShader);

	virtual void Animate(float fTimeElapsed);

	virtual void OnPrepareRender();
	virtual void Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera);

public:
	void Rotate(XMFLOAT3* pxmf3Axis, float fAngle);

public:
	//��� ���۸� �����Ѵ�. 
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);
	
	//��� ������ ������ �����Ѵ�. 
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	//���� ��ü�� ���� ��ȯ ��Ŀ��� ��ġ ���Ϳ� ����(x-��, y-��, z-��) ���͸� ��ȯ�Ѵ�.
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook() const;
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	//���� ��ü�� ��ġ�� �����Ѵ�. 
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	//���� ��ü�� ���� x-��, y-��, z-�� �������� �̵��Ѵ�.
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);

	//���� ��ü�� ȸ��(x-��, y-��, z-��)�Ѵ�. 
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);

	void UpdateBoundingBox()
	{
		m_xmBoundingBox = m_pMesh->GetBoundingBox();
		m_xmBoundingBox.Transform(m_xmBoundingBox, XMLoadFloat4x4(&m_xmf4x4World));
	}

public:
	//���� ��ü�� ī�޶� ���δ� ���� �˻��Ѵ�.
	bool IsVisible(CCamera *pCamera=NULL);

	bool m_bActive = true;

public:
	//�� ��ǥ���� ��ŷ ������ �����Ѵ�. 
	void GenerateRayForPicking(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View,
	XMFLOAT3* pxmf3PickRayOrigin, XMFLOAT3* pxmf3PickRayDirection);

	//ī�޶� ��ǥ���� �� ���� ���� �� ��ǥ���� ��ŷ ������ �����ϰ� ��ü���� ������ �˻��Ѵ�. 
	int PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View, float* pfHitDistance);

	//�޽��� �ٿ�� �ڽ�(�� ��ǥ��)�� �����Ѵ�.
	BoundingOrientedBox m_xmBoundingBox;
};


class CRotatingObject : public CGameObject
{
public:
	CRotatingObject();
	virtual ~CRotatingObject();
private:
	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;
public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) {
		m_xmf3RotationAxis =
			xmf3RotationAxis;
	}
	virtual void Animate(float fTimeElapsed);
};

class CTankObject : public CGameObject
{
public:
	CTankObject() = default;
	virtual ~CTankObject() = default;

private:
	XMFLOAT3 m_xmf3RotationAxis = { 0, 1, 0 }; // y�� ȸ��
	float m_fRotationSpeed = 0.0f;

	float m_fMoveSpeed = 10.0f;
	float m_fDirectionChangeTime = 0.0f; // �ð� ����
	float m_fDirectionChangeInterval = 1.0f; // 2�ʸ��� ���� ����

	float m_fCurrentYaw = 0.0f;       // ���� y�� ȸ�� ���� (����)
	float m_fTargetYaw = 0.0f;        // ��ǥ y�� ȸ�� ���� (����)
	float m_fRotationLerpSpeed = 2.0f; // ȸ�� �ӵ� (���� Ŭ���� ���� ȸ��)

public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) { m_xmf3RotationAxis = xmf3RotationAxis; }

	virtual void Animate(float fTimeElapsed) override;
};


class CBulletObject : public CGameObject
{
public:
	CBulletObject();
	virtual ~CBulletObject();
private:
	float bulletSpeed = 100.0f; // �Ѿ� �ӵ�

public:
	virtual void Animate(float fTimeElapsed);
public:
	void reset(XMFLOAT3 position, XMFLOAT3 dir);
private:
	XMFLOAT3 lookDir = { 0.0f, 0.0f, 1.0f }; // �÷��̾��� Look ���� (Z�� ����)
	bool moveable = false; // �Ѿ��� ������ �� �ִ� �������� ����

	CGameObject* m_pLockedObject = NULL;	// lock ������Ʈ
};