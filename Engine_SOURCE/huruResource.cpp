#include "huruResource.h"

namespace huru
{
	Resource::Resource(enums::eResourceType type) :
		mType(type)
	{

	}

	HRESULT Resource::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
}