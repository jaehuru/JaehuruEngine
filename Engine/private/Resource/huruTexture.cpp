#include "Resource/huruTexture.h"
#include "HighLevelInterface/huruApplication.h"
#include "Resource/huruResources.h"

extern Application application;

namespace huru::graphics
{
	Texture* Texture::Create(const wstring& name, UINT width, UINT height)
	{
		Texture* image = Resources::Find<Texture>(name);
		if (image)
			return image;

		image = new Texture();
		image->SetName(name);
		image->SetWidth(width);
		image->SetHeight(height);

		HDC hdc = application.GetHDC();

		image->mBitmap = CreateCompatibleBitmap(hdc, width, height);
		image->mHdc = CreateCompatibleDC(hdc);

		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);
		Rectangle(image->mHdc, -1, -1, image->GetWidth() + 1, image->GetHeight() + 1);
		SelectObject(hdc, oldBrush);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(oldBitmap);

		Resources::Insert(name + L"Image", image);

		return image;
	}

	Texture::Texture() :
		Resource(eResourceType::Texture),
		mbAlpha(false)
	{

	}

	Texture::~Texture()
	{

	}

	HRESULT Texture::Load(const wstring& path)
	{
		wstring ext = path.substr(path.find_last_of(L".") + 1);
		if (ext == L"bmp")
		{
			//bmp
			mType = eTextureType::Bmp;
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr)
				return S_FALSE;

			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);
			
			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			if (info.bmBitsPixel == 32)
				mbAlpha = true;
			else if (info.bmBitsPixel == 24)
				mbAlpha = false;


			HDC mainDC = application.GetHDC();
			mHdc = CreateCompatibleDC(mainDC);

			HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(oldBitmap);
		}
		else if (ext == L"png")
		{
			//png
			mType = eTextureType::Png;
			mImage = Gdiplus::Image::FromFile(path.c_str());

			if (mImage == nullptr)
				return S_FALSE;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}
		return S_OK;
	}

	COLORREF Texture::GetPixel(int x, int y)
	{
		return ::GetPixel(mHdc, x, y);
	}
}