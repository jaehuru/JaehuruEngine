#pragma once

#include "GraphicDevice/huruGraphicDevice_DX11.h"


namespace huru::graphics
{
	class VertexBuffer : public GpuBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		bool Create(const std::vector<Vertex>& vertexes);
		void Bind();

	private:
	};
}

