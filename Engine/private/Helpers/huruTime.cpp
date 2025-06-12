#include "Helpers/huruTime.h"

namespace huru
{
	
	LARGE_INTEGER Time::CPUFrequency =		{};
	LARGE_INTEGER Time::PrevFrequency =		{};
	LARGE_INTEGER Time::CurrentFrequency =	{};
	float Time::DeltaTimeValue =					0.f;

	void Time::Initialize()
	{
		// CPU 고유 진동수
		QueryPerformanceFrequency(&CPUFrequency);

		// 프로그램이 시작 했을 때 현재 진동수
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		QueryPerformanceCounter(&CurrentFrequency);

		float differenceFrequency = 
			static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);

		DeltaTimeValue = 
			differenceFrequency / static_cast<float>(CPUFrequency.QuadPart);

		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
	}
	void Time::Render(HDC hdc)
	{
		static float time = 0.f;

		time += DeltaTimeValue;
		float fps = 1.0f / DeltaTimeValue;	
		
		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"fps : %d", (int)fps);
		int len = static_cast<int>(wcsnlen_s(str, 50));

		TextOut(hdc, 0, 0, str, len);
	}
}