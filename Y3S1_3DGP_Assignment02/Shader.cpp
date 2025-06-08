#include "stdafx.h"
#include <vector>
#include "Shader.h"

CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i])
			m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

//래스터라이저 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_RASTERIZER_DESC CShader::CreateRasterizerState()
{
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	return(d3dRasterizerDesc);
}

//깊이-스텐실 검사를 위한 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState()
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

//블렌딩 상태를 설정하기 위한 구조체를 반환한다. 
D3D12_BLEND_DESC CShader::CreateBlendState()
{
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	return(d3dBlendDesc);
}

//입력 조립기에게 정점 버퍼의 구조를 알려주기 위한 구조체를 반환한다. 
D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout()
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;

	return(d3dInputLayoutDesc);
}

//정점 셰이더 바이트 코드를 생성(컴파일)한다. 
D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

//픽셀 셰이더 바이트 코드를 생성(컴파일)한다. 
D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

//셰이더 소스 코드를 컴파일하여 바이트 코드 구조체를 반환한다. 
D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(const WCHAR *pszFileName, LPCSTR pszShaderName,
	LPCSTR pszShaderProfile, ID3DBlob** ppd3dShaderBlob)
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile,
		nCompileFlags, 0, ppd3dShaderBlob, NULL);
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();
	return(d3dShaderByteCode);
}

//그래픽스 파이프라인 상태 객체를 생성한다. 
void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	ID3DBlob* pd3dVertexShaderBlob = NULL, * pd3dPixelShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void**)&m_ppd3dPipelineStates[0]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();

	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) 
		delete[] d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{

}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{

}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList* pd3dCommandList, XMFLOAT4X4
	* pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CShader::ReleaseShaderVariables()
{

}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
	//파이프라인에 그래픽스 상태 객체를 설정한다. 
	pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}

void CShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender(pd3dCommandList);
}

void CShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
}

void CShader::AnimateObjects(float fTimeElapsed)
{
}

void CShader::ReleaseObjects()
{
}

void CShader::ReleaseUploadBuffers()
{
}

CGameObject* CShader::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition, XMFLOAT4X4& xmf4x4View, float* pfNearHitDistance)
{
	return nullptr;
}




//------------------------------------------------------------------------------------------------
//----------------------------------------CPlayerShader-------------------------------------------
//------------------------------------------------------------------------------------------------

CPlayerShader::CPlayerShader()
{
}

CPlayerShader::~CPlayerShader()
{
}

D3D12_INPUT_LAYOUT_DESC CPlayerShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;

	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CPlayerShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CPlayerShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}

void CPlayerShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}



//------------------------------------------------------------------------------------------------
//----------------------------------------CObjectsShader------------------------------------------
//------------------------------------------------------------------------------------------------

CObjectsShader::CObjectsShader()
{

}

CObjectsShader::~CObjectsShader()
{

}

D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;

	D3D12_INPUT_ELEMENT_DESC* pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];
	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,
	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "VSDiffused", "vs_5_1",
		ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob** ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shaders.hlsl", "PSDiffused", "ps_5_1",
		ppd3dShaderBlob));
}

void CObjectsShader::CreateShader(ID3D12Device* pd3dDevice, ID3D12RootSignature
	* pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState * [m_nPipelineStates];

	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CObjectsShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList
	* pd3dCommandList)
{
	std::vector<XMFLOAT3> positions = {
	XMFLOAT3(-43, 21, -1),
	XMFLOAT3(-41, 21, -1),
	XMFLOAT3(-39, 21, -1),
	XMFLOAT3(-39, 19, -1),
	XMFLOAT3(-43, 17, -1),
	XMFLOAT3(-39, 17, -1),
	XMFLOAT3(-43, 13, -1),
	XMFLOAT3(-39, 15, -1),
	XMFLOAT3(-39, 13, -1),
	XMFLOAT3(-41, 13, -1),
	XMFLOAT3(-41, 17, -1),
	XMFLOAT3(-36, 21, -1),
	XMFLOAT3(-36, 19, -1),
	XMFLOAT3(-36, 17, -1),
	XMFLOAT3(-36, 15, -1),
	XMFLOAT3(-36, 13, -1),
	XMFLOAT3(-32, 19, -1),
	XMFLOAT3(-25, 19, -1),
	XMFLOAT3(-25, 21, -1),
	XMFLOAT3(-27, 21, -1),
	XMFLOAT3(-29, 21, -1),
	XMFLOAT3(-25, 17, -1),
	XMFLOAT3(-32, 17, -1),
	XMFLOAT3(-32, 15, -1),
	XMFLOAT3(-32, 19, -1),
	XMFLOAT3(-32, 15, -1),
	XMFLOAT3(-34, 13, -1),
	XMFLOAT3(-34, 21, -1),
	XMFLOAT3(-32, 17, -1),
	XMFLOAT3(-25, 17, -1),
	XMFLOAT3(-3, 0, -1),
	XMFLOAT3(1, 2, -1),
	XMFLOAT3(-1, 2, -1),
	XMFLOAT3(-3, 2, -1),
	XMFLOAT3(-3, -2, -1),
	XMFLOAT3(-3, 0, -1),
	XMFLOAT3(1, 2, -1),
	XMFLOAT3(-1, 2, -1),
	XMFLOAT3(-3, 2, -1),
	XMFLOAT3(1, -2, -1),
	XMFLOAT3(-1, -2, -1),
	XMFLOAT3(-3, -2, -1),
	XMFLOAT3(1, -2, -1),
	XMFLOAT3(-1, -2, -1),
	XMFLOAT3(-3, -2, -1),
	XMFLOAT3(-12, 0, -1),
	XMFLOAT3(-12, 2, -1),
	XMFLOAT3(-14, 2, -1),
	XMFLOAT3(-16, 2, -1),
	XMFLOAT3(-12, -2, -1),
	XMFLOAT3(-12, 0, -1),
	XMFLOAT3(-12, 2, -1),
	XMFLOAT3(-14, 2, -1),
	XMFLOAT3(-16, 2, -1),
	XMFLOAT3(-12, -2, -1),
	XMFLOAT3(5, -10, -1),
	XMFLOAT3(5, -8, -1),
	XMFLOAT3(9, -12, -1),
	XMFLOAT3(7, -12, -1),
	XMFLOAT3(5, -12, -1),
	XMFLOAT3(5, -10, -1),
	XMFLOAT3(5, -8, -1),
	XMFLOAT3(9, -12, -1),
	XMFLOAT3(11, -12, -1),
	XMFLOAT3(13, -12, -1),
	XMFLOAT3(7, -12, -1),
	XMFLOAT3(5, -12, -1),
	XMFLOAT3(-8, 0, -1),
	XMFLOAT3(-8, 2, -1),
	XMFLOAT3(-8, -2, -1),
	XMFLOAT3(-8, 0, -1),
	XMFLOAT3(-8, 2, -1),
	XMFLOAT3(-8, -2, -1),
	XMFLOAT3(19, 19, -1),
	XMFLOAT3(19, 21, -1),
	XMFLOAT3(17, 21, -1),
	XMFLOAT3(15, 21, -1),
	XMFLOAT3(19, 17, -1),
	XMFLOAT3(-29, 21, -1),
	XMFLOAT3(-27, 21, -1),
	XMFLOAT3(-25, 21, -1),
	XMFLOAT3(-25, 19, -1),
	XMFLOAT3(-23, 19, -1),
	XMFLOAT3(-21, 19, -1),
	XMFLOAT3(-21, 21, -1),
	XMFLOAT3(-21, 17, -1),
	XMFLOAT3(-18, 17, -1),
	XMFLOAT3(-18, 19, -1),
	XMFLOAT3(-18, 21, -1),
	XMFLOAT3(-15, 18, -1),
	XMFLOAT3(7, 1, -1),
	XMFLOAT3(11, 1, -1),
	XMFLOAT3(9, -2, -1),
	XMFLOAT3(11, -1, -1),
	XMFLOAT3(9, 2, -1),
	XMFLOAT3(7, -1, -1),
	XMFLOAT3(38, 13, -1),
	XMFLOAT3(42, 13, -1),
	XMFLOAT3(40, 10, -1),
	XMFLOAT3(42, 11, -1),
	XMFLOAT3(40, 14, -1),
	XMFLOAT3(38, 11, -1),
	XMFLOAT3(-13, 21, -1),
	XMFLOAT3(-11, 18, -1),
	XMFLOAT3(-13, 17, -1),
	XMFLOAT3(-8, 17, -1),
	XMFLOAT3(-4, 21, -1),
	XMFLOAT3(-2, 21, -1),
	XMFLOAT3(-3, 19, -1),
	XMFLOAT3(1, 19, -1),
	XMFLOAT3(0, 17, -1),
	XMFLOAT3(-2, 17, -1),
	XMFLOAT3(-4, 17, -1),
	XMFLOAT3(-4, 14, -1),
	XMFLOAT3(-2, 14, -1),
	XMFLOAT3(0, 14, -1),
	XMFLOAT3(2, 14, -1),
	XMFLOAT3(7, 21, -1),
	XMFLOAT3(27, 13, -1),
	XMFLOAT3(25, 13, -1),
	XMFLOAT3(23, 13, -1),
	XMFLOAT3(23, 15, -1),
	XMFLOAT3(23, 17, -1),
	XMFLOAT3(25, 17, -1),
	XMFLOAT3(27, 17, -1),
	XMFLOAT3(27, 19, -1),
	XMFLOAT3(27, 21, -1),
	XMFLOAT3(25, 21, -1),
	XMFLOAT3(23, 21, -1),
	XMFLOAT3(9, 21, -1),
	XMFLOAT3(11, 21, -1),
	XMFLOAT3(11, 19, -1),
	XMFLOAT3(11, 17, -1),
	XMFLOAT3(9, 17, -1),
	XMFLOAT3(7, 17, -1),
	XMFLOAT3(7, 15, -1),
	XMFLOAT3(7, 13, -1),
	XMFLOAT3(19, 13, -1),
	XMFLOAT3(17, 13, -1),
	XMFLOAT3(15, 13, -1),
	XMFLOAT3(9, 13, -1),
	XMFLOAT3(9, 10, -1),
	XMFLOAT3(-3, -7, -1),
	XMFLOAT3(1, -7, -1),
	XMFLOAT3(-1, -7, -1),
	XMFLOAT3(5, -5, -1),
	XMFLOAT3(9, -5, -1),
	XMFLOAT3(11, -5, -1),
	XMFLOAT3(13, -5, -1),
	XMFLOAT3(7, -5, -1),
	XMFLOAT3(8, -7, -1),
	XMFLOAT3(11, -7, -1),
	XMFLOAT3(-1, -5, -1),
	XMFLOAT3(9, 8, -1),
	XMFLOAT3(11, 8, -1),
	XMFLOAT3(7, 8, -1),
	XMFLOAT3(11, 13, -1),
	XMFLOAT3(31, 17, -1),
	XMFLOAT3(30, 17, -1),
	XMFLOAT3(30, 19, -1),
	XMFLOAT3(30, 15, -1),
	XMFLOAT3(33, 15, -1),
	XMFLOAT3(43, 21, -1),
	XMFLOAT3(43, 19, -1),
	XMFLOAT3(43, 17, -1),
	XMFLOAT3(33, 17, -1),
	XMFLOAT3(33, 19, -1),
	XMFLOAT3(2, 17, -1),
	XMFLOAT3(0, 21, -1),
	XMFLOAT3(2, 21, -1),
	XMFLOAT3(-8, 19, -1),
	XMFLOAT3(-8, 21, -1),
	XMFLOAT3(-11, 20, -1),
	XMFLOAT3(-15, 20, -1),
	XMFLOAT3(-13, 14, -1),
	XMFLOAT3(-10, -9, -1),
	XMFLOAT3(-12, -9, -1),
	XMFLOAT3(-12, -7, -1),
	XMFLOAT3(-8, -9, -1),
	XMFLOAT3(-8, -7, -1),
	XMFLOAT3(-8, -5, -1),
	XMFLOAT3(-10, -5, -1),
	XMFLOAT3(-12, -5, -1),
	XMFLOAT3(38, 17, -1),
	XMFLOAT3(36, 17, -1),
	XMFLOAT3(36, 19, -1),
	XMFLOAT3(40, 17, -1),
	XMFLOAT3(40, 19, -1),
	XMFLOAT3(40, 21, -1),
	XMFLOAT3(38, 21, -1),
	XMFLOAT3(36, 21, -1),
	XMFLOAT3(-11, 14, -1),
	XMFLOAT3(-9, 14, -1),
	XMFLOAT3(-9, 12, -1),
	XMFLOAT3(-9, 10, -1),
	XMFLOAT3(-13, 12, -1),
	XMFLOAT3(-13, 10, -1),
	XMFLOAT3(-11, 10, -1)
	};
	const int numPositions = positions.size();

	// 정육면체 메쉬 생성 (12x12x12)
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList);

	m_nObjects = numPositions;
	m_ppObjects = new CGameObject * [m_nObjects];

	for (int i = 0; i < m_nObjects; ++i)	
	{
		CRotatingObject* pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(positions[i]);
		m_ppObjects[i] = pRotatingObject;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}



void CObjectsShader::ReleaseObjects()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++)
		{
			if (m_ppObjects[j]) delete m_ppObjects[j];
		}
		delete[] m_ppObjects;
	}
}

void CObjectsShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		m_ppObjects[j]->Animate(fTimeElapsed);
		m_ppObjects[j]->UpdateBoundingBox();
	}
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_ppObjects)
	{
		for (int j = 0; j < m_nObjects; j++) m_ppObjects[j]->ReleaseUploadBuffers();
	}
}

void CObjectsShader::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);
	for (int j = 0; j < m_nObjects; j++)
	{
		if (m_ppObjects[j] and m_ppObjects[j]->m_bActive)
		{
			m_ppObjects[j]->Render(pd3dCommandList, pCamera);
		}
	}
}

CGameObject* CObjectsShader::PickObjectByRayIntersection(XMFLOAT3& xmf3PickPosition,
	XMFLOAT4X4& xmf4x4View, float* pfNearHitDistance)
{
	int nIntersected = 0;
	*pfNearHitDistance = FLT_MAX;
	float fHitDistance = FLT_MAX;
	CGameObject* pSelectedObject = NULL;
	for (int j = 0; j < m_nObjects; j++)
	{
		nIntersected = m_ppObjects[j]->PickObjectByRayIntersection(xmf3PickPosition,
			xmf4x4View, &fHitDistance);
		if ((nIntersected > 0) && (fHitDistance < *pfNearHitDistance))
		{
			*pfNearHitDistance = fHitDistance;
			pSelectedObject = m_ppObjects[j];
		}
	}
	return(pSelectedObject);
}

//------------------------------------------------------------------------------------------------
//----------------------------------------CObjectsShader1------------------------------------------
//------------------------------------------------------------------------------------------------



void CObjectsShader1::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	std::vector<XMFLOAT3> positions = {
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
		XMFLOAT3(-27, 3, 74),
	};
	const int numPositions = positions.size();

	

	m_nObjects = numPositions;
	m_ppObjects = new CGameObject * [m_nObjects];

	for (int i = 0; i < m_nObjects; ++i)
	{
		// 정육면체 메쉬 생성 (12x12x12)
		CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList);

		CRotatingObject* pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(positions[i]);
		m_ppObjects[i] = pRotatingObject;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CObjectsShader1::AnimateObjects(float fTimeElapsed)
{

}


//------------------------------------------------------------------------------------------------
//----------------------------------------CFloorShader--------------------------------------------
//------------------------------------------------------------------------------------------------


void CFloorShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	std::vector<XMFLOAT3> positions = {
		XMFLOAT3(0.f, -5.f, 0.f)
	};
	const int numPositions = positions.size();

	// 정육면체 메쉬 생성 (12x12x12)
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 1000.f, 10.f, 1000.f);

	m_nObjects = numPositions;
	m_ppObjects = new CGameObject * [m_nObjects];

	for (int i = 0; i < m_nObjects; ++i)
	{
		CRotatingObject* pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(positions[i]);
		m_ppObjects[i] = pRotatingObject;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CFloorShader::AnimateObjects(float fTimeElapsed)
{
}


//------------------------------------------------------------------------------------------------
//----------------------------------------CEnemyShader--------------------------------------------
//------------------------------------------------------------------------------------------------

void CEnemyShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	std::vector<XMFLOAT3> positions = {
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
		XMFLOAT3(0.f, 0.f, 0.f),
	};
	const int numPositions = positions.size();

	// 정육면체 메쉬 생성 (12x12x12)
	CTankMesh* pCubeMesh = new CTankMesh(pd3dDevice, pd3dCommandList, 5, 5, 10);

	m_nObjects = numPositions;
	m_ppObjects = new CGameObject * [m_nObjects];

	for (int i = 0; i < m_nObjects; ++i)
	{
		CGameObject* pRotatingObject = new CTankObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(positions[i]);
		m_ppObjects[i] = pRotatingObject;
		m_ppObjects[i]->m_xmBoundingBox = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.5f, 1.7f, 4.f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

//------------------------------------------------------------------------------------------------
//----------------------------------------CBulletShader--------------------------------------------
//------------------------------------------------------------------------------------------------

void CBulletShader::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	std::vector<XMFLOAT3> positions = {
		XMFLOAT3(0.f, -50.f, 0.f),
	};
	const int numPositions = positions.size();

	// 정육면체 메쉬 생성 (12x12x12)
	//CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, 1000.f, 10.f, 1000.f);
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList);

	// numPositions;
	m_nObjects = 50;
	m_ppObjects = new CGameObject * [m_nObjects];

	for (int i = 0; i < m_nObjects; ++i)
	{
		CGameObject* pRotatingObject = new CBulletObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(positions[0]);
		m_ppObjects[i] = pRotatingObject;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CBulletShader::AnimateObjects(float fTimeElapsed)
{
	for (int j = 0; j < m_nObjects; j++)
	{
		dynamic_cast<CBulletObject*>(m_ppObjects[j])->Animate(fTimeElapsed);
		dynamic_cast<CBulletObject*>(m_ppObjects[j])->UpdateBoundingBox();
	}
}

void CMenuShader1::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	std::vector<XMFLOAT3> positions = {
		XMFLOAT3(-46, 17, -1),
		XMFLOAT3(-47, 15, -1),
		XMFLOAT3(-48, 13, -1),
		XMFLOAT3(-44, 15, -1),
		XMFLOAT3(-44, 13, -1),
		XMFLOAT3(-40, 15, -1),
		XMFLOAT3(-40, 13, -1),
		XMFLOAT3(-40, 17, -1),
		XMFLOAT3(-34, 17, -1),
		XMFLOAT3(-35, 15, -1),
		XMFLOAT3(-36, 13, -1),
		XMFLOAT3(-32, 15, -1),
		XMFLOAT3(-32, 13, -1),
		XMFLOAT3(-28, 15, -1),
		XMFLOAT3(-28, 13, -1),
		XMFLOAT3(-28, 17, -1),
		XMFLOAT3(-34, 19, -1),
		XMFLOAT3(-36, 19, -1),
		XMFLOAT3(-32, 19, -1),
		XMFLOAT3(-32, 10, -1),
		XMFLOAT3(-34, 10, -1),
		XMFLOAT3(-30, 10, -1),
		XMFLOAT3(-28, 8, -1),
		XMFLOAT3(-28, 6, -1),
		XMFLOAT3(-28, 10, -1),
		XMFLOAT3(-26, 15, -1),
		XMFLOAT3(-16, 15, -1),
		XMFLOAT3(-18, 15, -1),
		XMFLOAT3(-16, 17, -1),
		XMFLOAT3(-18, 19, -1),
		XMFLOAT3(-20, 19, -1),
		XMFLOAT3(-16, 19, -1),
		XMFLOAT3(-18, 11, -1),
		XMFLOAT3(-20, 11, -1),
		XMFLOAT3(-16, 11, -1),
		XMFLOAT3(-20, 15, -1),
		XMFLOAT3(-20, 13, -1),
		XMFLOAT3(-12, 15, -1),
		XMFLOAT3(-12, 13, -1),
		XMFLOAT3(-12, 17, -1),
		XMFLOAT3(-14, 15, -1),
		XMFLOAT3(-9, 15, -1),
		XMFLOAT3(-9, 13, -1),
		XMFLOAT3(-9, 17, -1),
		XMFLOAT3(-1, 15, -1),
		XMFLOAT3(-3, 15, -1),
		XMFLOAT3(-1, 17, -1),
		XMFLOAT3(-1, 13, -1),
		XMFLOAT3(-5, 19, -1),
		XMFLOAT3(-1, 19, -1),
		XMFLOAT3(-3, 11, -1),
		XMFLOAT3(-5, 11, -1),
		XMFLOAT3(-1, 11, -1),
		XMFLOAT3(-5, 15, -1),
		XMFLOAT3(-5, 13, -1),
		XMFLOAT3(-5, 17, -1),
		XMFLOAT3(3, 15, -1),
		XMFLOAT3(3, 13, -1),
		XMFLOAT3(3, 17, -1),
		XMFLOAT3(1, 15, -1),
		XMFLOAT3(6, 15, -1),
		XMFLOAT3(6, 13, -1),
		XMFLOAT3(6, 17, -1),
		XMFLOAT3(2, 4, -1),
		XMFLOAT3(0, 4, -1),
		XMFLOAT3(2, 6, -1),
		XMFLOAT3(0, 8, -1),
		XMFLOAT3(-2, 8, -1),
		XMFLOAT3(2, 8, -1),
		XMFLOAT3(0, 0, -1),
		XMFLOAT3(-2, 0, -1),
		XMFLOAT3(2, 0, -1),
		XMFLOAT3(-2, 4, -1),
		XMFLOAT3(-2, 2, -1),
		XMFLOAT3(11, 15, -1),
		XMFLOAT3(11, 13, -1),
		XMFLOAT3(11, 17, -1),
		XMFLOAT3(11, 9, -1),
		XMFLOAT3(11, 7, -1),
		XMFLOAT3(11, 11, -1),
		XMFLOAT3(20, 15, -1),
		XMFLOAT3(18, 15, -1),
		XMFLOAT3(20, 17, -1),
		XMFLOAT3(18, 19, -1),
		XMFLOAT3(16, 19, -1),
		XMFLOAT3(20, 19, -1),
		XMFLOAT3(18, 11, -1),
		XMFLOAT3(16, 11, -1),
		XMFLOAT3(20, 11, -1),
		XMFLOAT3(16, 15, -1),
		XMFLOAT3(16, 13, -1),
		XMFLOAT3(24, 15, -1),
		XMFLOAT3(24, 13, -1),
		XMFLOAT3(24, 17, -1),
		XMFLOAT3(22, 15, -1),
		XMFLOAT3(27, 15, -1),
		XMFLOAT3(27, 13, -1),
		XMFLOAT3(27, 17, -1),
		XMFLOAT3(35, 15, -1),
		XMFLOAT3(33, 15, -1),
		XMFLOAT3(35, 17, -1),
		XMFLOAT3(35, 13, -1),
		XMFLOAT3(31, 19, -1),
		XMFLOAT3(35, 19, -1),
		XMFLOAT3(33, 11, -1),
		XMFLOAT3(31, 11, -1),
		XMFLOAT3(35, 11, -1),
		XMFLOAT3(31, 15, -1),
		XMFLOAT3(31, 13, -1),
		XMFLOAT3(31, 17, -1),
		XMFLOAT3(39, 15, -1),
		XMFLOAT3(39, 13, -1),
		XMFLOAT3(39, 17, -1),
		XMFLOAT3(37, 15, -1),
		XMFLOAT3(42, 15, -1),
		XMFLOAT3(42, 13, -1),
		XMFLOAT3(42, 17, -1),
		XMFLOAT3(38, 4, -1),
		XMFLOAT3(36, 4, -1),
		XMFLOAT3(38, 6, -1),
		XMFLOAT3(36, 8, -1),
		XMFLOAT3(34, 8, -1),
		XMFLOAT3(38, 8, -1),
		XMFLOAT3(36, 0, -1),
		XMFLOAT3(34, 0, -1),
		XMFLOAT3(38, 0, -1),
		XMFLOAT3(34, 4, -1),
		XMFLOAT3(34, 2, -1),
		XMFLOAT3(51, 14, -1),
		XMFLOAT3(49, 14, -1),
		XMFLOAT3(51, 16, -1),
		XMFLOAT3(49, 18, -1),
		XMFLOAT3(47, 18, -1),
		XMFLOAT3(51, 18, -1),
		XMFLOAT3(49, 10, -1),
		XMFLOAT3(47, 10, -1),
		XMFLOAT3(51, 10, -1),
		XMFLOAT3(47, 14, -1),
		XMFLOAT3(47, 12, -1),
	};
	const int numPositions = positions.size();

	// 정육면체 메쉬 생성 (12x12x12)
	CCubeMeshDiffused* pCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList);

	m_nObjects = numPositions;
	m_ppObjects = new CGameObject * [m_nObjects];

	for (int i = 0; i < m_nObjects; ++i)
	{
		CRotatingObject* pRotatingObject = new CRotatingObject();
		pRotatingObject->SetMesh((CMesh*)pCubeMesh);
		pRotatingObject->SetPosition(positions[i]);
		m_ppObjects[i] = pRotatingObject;
	}

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}
