#pragma once

#include "Resource/huruResource.h"
#include "GraphicDevice/GPUBuffer/huruVertexBuffer.h"
#include "GraphicDevice/GPUBuffer/huruIndexBuffer.h"

namespace huru
{
	class Mesh : public Resource
	{
	public:
		struct Data
		{
			Data();
			~Data();

			D3D11_PRIMITIVE_TOPOLOGY mTopology;
			vector<Vertex> vertices;
			vector<UINT> indices;
		};

		Mesh();
		~Mesh();

		virtual HRESULT Save(const wstring& path) override;
		virtual HRESULT Load(const wstring& path) override;


		bool CreateVB(const vector<Vertex>& vertices);
		bool CreateIB(const vector<UINT>& indices);
		void Bind();

	private:
		VertexBuffer mVB;
		IndexBuffer mIB;

		Data mData;

	};
}

