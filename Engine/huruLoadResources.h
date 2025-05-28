#pragma once

#include "..//Engine_SOURCE/huruResources.h"
#include "..//Engine_SOURCE/huruTexture.h"


namespace huru
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>
			(L"Player", L"..\\Resources\\Player.bmp");
		Resources::Load<graphics::Texture>
			(L"Cat", L"..\\Resources\\Cat.bmp");
		Resources::Load<graphics::Texture>
			(L"SpringFloor", L"..\\Resources\\SpringFloor.bmp");
		Resources::Load<graphics::Texture>(L"HPBAR", L"..\\Resources\\HPBAR.bmp");
			
	}
}