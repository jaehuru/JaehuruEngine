#pragma once

#include "Common/huruEntity.h"

namespace huru
{
	class Resource : public Entity // �߻� Ŭ����
	{
	public:
		Resource(enums::eResourceType type);
		virtual ~Resource() = default;

		// ���� ���� �Լ�
		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetPath() const { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }

	private:
		const enums::eResourceType mType;
		std::wstring mPath;
	};
}
