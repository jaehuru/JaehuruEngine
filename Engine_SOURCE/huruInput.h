#pragma once

#include "CommonInclude.h"

namespace huru
{
	enum class eKeyState
	{
		None,
		Pressed,
		Down,
		Up,
	};

	enum class eKeyCode
	{
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,
		Left, Right, Up, Down,
		LButton, RButton,
		End,
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode	keyCode;
			eKeyState	state;
			bool		bPressed;
		};

		static void Initialize();
		static void Update();

		static bool GetKeyDown(eKeyCode code) 
		{
			return Keys[(UINT)code].state == eKeyState::Down;
		}
		static bool GetKeyUp(eKeyCode code)
		{
			return Keys[(UINT)code].state == eKeyState::Up;
		}
		static bool GetKey(eKeyCode code)
		{ 
			return Keys[(UINT)code].state == eKeyState::Pressed;
		}

	private:
		static void createKeys();
		static void updateKeys();
		static void updateKey(Key& key);
		static void updateKeyDown(Key& key);
		static void updateKeyUp(Key& key);

	private:
		static std::vector<Key> Keys;
	};
}

