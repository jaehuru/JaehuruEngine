#pragma once

#include "Component/Camera/huruCamera.h"
#include "GraphicDevice/huruGraphicDevice_DX11.h"
#include "GraphicDevice/GPUBuffer/huruVertexBuffer.h"


namespace huru::renderer
{
	extern Camera* mainCamera;

	extern vector<graphics::Vertex> vertexes;
	extern vector<UINT> indices;

	extern graphics::VertexBuffer vertexBuffer;
	extern ID3D11Buffer* indexBuffer;
	extern ID3D11Buffer* constantBuffer;

	extern ID3D11InputLayout* inputLayouts;

	void Initialize();
	void Release();
}

