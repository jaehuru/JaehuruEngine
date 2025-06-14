#pragma once

#include "Common/huruEntity.h"

namespace huru
{
	class Resource : public Entity // 추상 클래스
	{
	public:
		Resource(eResourceType type);
		virtual ~Resource() = default;

		// 순수 가상 함수
		virtual HRESULT Load(const wstring& path) = 0;

		const wstring& GetPath() const { return mPath; }
		void SetPath(const wstring& path) { mPath = path; }

	private:
		const eResourceType mType;
		wstring mPath;
	};
}
