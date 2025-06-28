#pragma once

#include "GraphicDevice/huruGraphicDevice_DX11.h"

namespace huru::graphics
{
	class IndexBuffer : public GpuBuffer
	{
	public:
		IndexBuffer();
		~IndexBuffer();

		bool Create(const std::vector<UINT>& indices);
		void Bind();

	private:
	};
}

