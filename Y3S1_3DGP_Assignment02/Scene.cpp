#include "stdafx.h"
#include "Scene.h"

void Scene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseUploadBuffers();
}

ID3D12RootSignature* Scene::GetGraphicsRootSignature()
{
	return(m_pd3dGraphicsRootSignature);
}
