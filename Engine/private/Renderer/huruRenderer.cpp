#include "Renderer/huruRenderer.h"
#include "Common/huruGraphics.h"
#include "Resource/huruResources.h"
#include "Resource/Graphics/huruShader.h"

namespace huru::renderer
{
	Camera* mainCamera = nullptr;

	vector<Vertex> vertexes = {};
	vector<UINT> indices;

	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	ConstantBuffer constantBuffers[(UINT)eCBType::End] = {};

	ID3D11Buffer* constantBuffer = nullptr;
	ID3D11InputLayout* inputLayouts = nullptr;

	void LoadTriangleMesh()
	{
		renderer::vertexes.resize(3);
		renderer::vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		renderer::vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		renderer::vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		renderer::vertexes[1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		renderer::vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		renderer::vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);
	}

	void LoadMeshes()
	{
		LoadTriangleMesh();
	}

	void LoadShaders()
	{
		map<eShaderStage, wstring> shaderPaths = {
		{ eShaderStage::VS, L"../JaehuruEngine/Engine/Shaders/VS/TriangleVS.hlsl" },
		{ eShaderStage::PS, L"../JaehuruEngine/Engine/Shaders/PS/TrianglePS.hlsl" }
		};

		Resources::Load<Shader>(L"TriangleShader", shaderPaths);
	}

	void LoadConstantBuffers()
	{
		constantBuffers[(UINT)eCBType::Transform].Create(eCBType::Transform, sizeof(Vector4));
	}

	void Initialize()
	{
		LoadMeshes();
		LoadShaders();
		LoadConstantBuffers();
	}

	void Release()
	{
		inputLayouts->Release();
	}
}