#pragma once

#include "..//Engine_SOURCE/huruResources.h"
#include "..//Engine_SOURCE/huruTexture.h"


namespace huru
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>(L"BG", L"C:\\Users\\USER-PC\\Documents\\CODING\\CPP\\JaehuruEngine\\Resources\\bg2.png");
	}
}