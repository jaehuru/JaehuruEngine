#include "UI/huruUIHUD.h"
#include "Resource/huruTexture.h"
#include "Resource/huruResources.h"

namespace huru
{
	UIHUD::UIHUD()
		: UIBase(enums::eUIType::HUD)
	{
	}

	UIHUD::~UIHUD()
	{
	}

	void UIHUD::OnInit()
	{
		mTexture = Resources::Find<graphics::Texture>(L"HUD");
	}

	void UIHUD::OnActive()
	{
		
	}

	void UIHUD::OnInActive()
	{
	}

	void UIHUD::OnUpdate()
	{
	}

	void UIHUD::OnLateUpdate()
	{
	}

	void UIHUD::OnRender(HDC hdc)
	{
		TransparentBlt(
			hdc,
			0, 0,
			mTexture->GetWidth(),
			mTexture->GetHeight(),
			mTexture->GetHdc(),
			0, 0,
			mTexture->GetWidth(),
			mTexture->GetHeight(),
			RGB(255, 0, 255));
	}

	void UIHUD::OnClear()
	{
		
	}
}