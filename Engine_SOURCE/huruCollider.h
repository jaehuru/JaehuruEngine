#pragma once

#include "huruComponent.h"

namespace huru
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		Vector2 GetOffset() { return mOffset; }
		void SetOffset(Vector2 offset) { mOffset = offset; }

	private:
		Vector2 mOffset;
	};
}

