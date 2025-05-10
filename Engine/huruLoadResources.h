#pragma once

#include "..//Engine_SOURCE/huruResources.h"
#include "..//Engine_SOURCE/huruTexture.h"


namespace huru
{
	void LoadResources()
	{
		Resources::Load<graphics::Texture>
			(L"Map", L"..\\Resources\\img\\map\\map_pure.png");
		Resources::Load<graphics::Texture>
			(L"PacMan", L"..\\Resources\\img\\pacman\\0.png");
		Resources::Load<graphics::Texture>
			(L"Cat", L"..\\Resources\\Cat.bmp");
		Resources::Load<graphics::Texture>
			(L"Bubble", L"..\\Resources\\Bubble.png");
		Resources::Load<graphics::Texture>
			(L"MapleEffect", L"..\\Resources\\ezgif.com-gif-maker.png");
			
		
	}
}