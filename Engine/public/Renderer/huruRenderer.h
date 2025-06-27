#pragma once

#include "Component/Camera/huruCamera.h"
#include "GraphicDevice/huruGraphicDevice_DX11.h"


namespace huru::renderer
{
	extern Camera* mainCamera;

	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[3];
	extern vector<UINT> indices;

	extern ID3D11Buffer* vertexBuffer;
	extern ID3D11Buffer* indexBuffer;
	extern ID3D11Buffer* constantBuffer;

	extern ID3D11InputLayout* inputLayouts;

	void Initialize();
	void Release();
}

