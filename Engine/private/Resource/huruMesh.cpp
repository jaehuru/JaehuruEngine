#include "Resource/huruMesh.h"

namespace huru
{
	Mesh::Data::Data()
		: mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, vertices{}
		, indices{}
	{

	}

	Mesh::Data::~Data()
	{

	}

	Mesh::Mesh()
		: Resource(enums::eResourceType::Mesh)
	{

	}

	Mesh::~Mesh()
	{

	}

	HRESULT Mesh::Save(const wstring& path)
	{
		return S_OK;
	}

	HRESULT Mesh::Load(const wstring& path)
	{

		return S_OK;
	}

	bool Mesh::CreateVB(const vector<graphics::Vertex>& vertices)
	{
		mData.vertices = vertices;
		return mVB.Create(vertices);
	}

	bool Mesh::CreateIB(const vector<UINT>& indices)
	{
		mData.indices = indices;
		return mIB.Create(indices);
	}

	void Mesh::Bind()
	{
		mVB.Bind();
		mIB.Bind();

		graphics::GetDevice()->BindPrimitiveTopology(mData.mTopology);
	}
}