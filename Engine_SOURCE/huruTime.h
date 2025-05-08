#pragma once

#include "CommonInclude.h"

namespace huru
{
	class Time
	{
	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		static float DeltaTime() { return DeltaTimeValue; }

	private:
		static LARGE_INTEGER CPUFrequency; // CPU 고유 진동수
		static LARGE_INTEGER PrevFrequency; // 프로그램 시작 시 진동수
		static LARGE_INTEGER CurrentFrequency; // 현재 진동수
		static float DeltaTimeValue;
	};
}

