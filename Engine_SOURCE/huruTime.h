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
		static LARGE_INTEGER CPUFrequency; // CPU ���� ������
		static LARGE_INTEGER PrevFrequency; // ���α׷� ���� �� ������
		static LARGE_INTEGER CurrentFrequency; // ���� ������
		static float DeltaTimeValue;
	};
}

