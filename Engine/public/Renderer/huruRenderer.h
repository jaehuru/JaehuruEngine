#pragma once

#include "Component/Camera/huruCamera.h"
#include "GraphicDevice/huruGraphicDevice_DX11.h"
#include "GraphicDevice/GPUBuffer/huruVertexBuffer.h"
#include "GraphicDevice/GPUBuffer/huruIndexBuffer.h"
#include "GraphicDevice/GPUBuffer/huruConstantBuffer.h"


namespace huru::renderer
{
	extern Camera*				mainCamera;

	extern vector<Vertex>		vertexes;
	extern vector<UINT>			indices;

	extern VertexBuffer			vertexBuffer;
	extern IndexBuffer			indexBuffer;
	extern ConstantBuffer		constantBuffers[(UINT)eCBType::End];

	extern ID3D11Buffer*		constantBuffer;
	extern ID3D11InputLayout*	inputLayouts;

	void	Initialize();
	void	Release();
}

