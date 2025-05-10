#pragma once

#include "CommonInclude.h"
using namespace huru::math;

namespace huru
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) 
		{
			mName = name;
		}

		std::wstring& GetName() { return mName; }

	private:
		std::wstring mName;
	};
}


