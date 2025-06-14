#pragma once

#include "Common/huruEntity.h"

namespace huru
{
	class Resource : public Entity // �߻� Ŭ����
	{
	public:
		Resource(eResourceType type);
		virtual ~Resource() = default;

		// ���� ���� �Լ�
		virtual HRESULT Load(const wstring& path) = 0;

		const wstring& GetPath() const { return mPath; }
		void SetPath(const wstring& path) { mPath = path; }

	private:
		const eResourceType mType;
		wstring mPath;
	};
}
