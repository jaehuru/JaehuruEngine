#include "Resource/huruTexture.h"
#include "HighLevelInterface/huruApplication.h"
#include "Resource/huruResources.h"

extern Application application;

namespace huru::graphics
{
	Texture* Texture::Create(const wstring& name, UINT width, UINT height)
	{
		Texture* image = Resources::Find<Texture>(name);
		if (image)
			return image;

		image = new Texture();
		image->SetName(name);
		image->SetWidth(width);
		image->SetHeight(height);

		Resources::Insert(name + L"Image", image);

		return image;
	}

	Texture::Texture() :
		Resource(eResourceType::Texture),
		mbAlpha(false)
	{

	}

	Texture::~Texture()
	{

	}

	HRESULT Texture::Load(const wstring& path)
	{
		wstring ext = path.substr(path.find_last_of(L".") + 1);
		
		return S_OK;
	}
}