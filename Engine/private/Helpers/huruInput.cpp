#include "Helpers/huruInput.h"
#include "HighLevelInterface/huruApplication.h"

extern huru::Application application;

namespace huru
{

	std::vector<Input::Key> Input::Keys = { };
	math::Vector2 huru::Input::mMousePosition = math::Vector2::One;

	int ASCII[(int)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_MBUTTON ,VK_RBUTTON
	};

	void Input::Initialize()
	{
		createKeys();
	}

	void Input::Update()
	{
		updateKeys();
	}

	void Input::createKeys()
	{
		for (size_t i = 0; i < (UINT)eKeyCode::End; ++i)
		{
			Key key;
			key.state = eKeyState::None;
			key.keyCode = (eKeyCode)i;
			key.bPressed = false;
			Keys.push_back(key);
		}
	}

	void Input::updateKeys()
	{
		std::for_each(Keys.begin(), Keys.end(),
			[](Key& key) -> void { updateKey(key); });		
	}

	void Input::updateKey(Key& key)
	{
		if (GetFocus())
		{
			isKeyDown(key.keyCode) ? updateKeyDown(key) : updateKeyUp(key);
			getMousePositionByWindow();
		}
		else
		{
			clearKey();
		}
	}

	bool Input::isKeyDown(eKeyCode code)
	{
		return GetAsyncKeyState(ASCII[(UINT)code]) & 0x8000;
	}

	void Input::updateKeyDown(Key& key)
	{
		if (key.bPressed == true)
			key.state = eKeyState::Pressed;
		else
			key.state = eKeyState::Down;

		key.bPressed = true;
	}

	void Input::updateKeyUp(Key& key)
	{
		if (key.bPressed == true)
			key.state = eKeyState::Up;
		else
			key.state = eKeyState::None;

		key.bPressed = false;
	}

	void Input::getMousePositionByWindow()
	{
		POINT mousePos = {  };
		GetCursorPos(&mousePos);
		ScreenToClient(application.GetHwnd(), &mousePos);

		UINT width = application.GetWidth();
		UINT height = application.GetHeight();

		mMousePosition.x = -1.0f;
		mMousePosition.y = -1.0f;

		if (mousePos.x > 0 && mousePos.x < width)
			mMousePosition.x = mousePos.x;

		if (mousePos.y > 0 && mousePos.y < height)
			mMousePosition.y = mousePos.y;
	}

	void Input::clearKey()
	{
		for (Key& key : Keys)
		{
			if (key.state == eKeyState::Down ||
				key.state == eKeyState::Pressed)
				key.state = eKeyState::Up;
			else if (key.state == eKeyState::Up)
				key.state = eKeyState::None;

			key.bPressed = false;
		}
	}
}
