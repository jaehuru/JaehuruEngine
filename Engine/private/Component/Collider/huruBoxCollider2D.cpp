#include "Component/Collider/huruBoxCollider2D.h"
#include "Component/Transform/huruTransform.h"
#include "Component/Camera/huruCamera.h"
#include "GameObject/huruGameObject.h"
#include "Renderer/huruRenderer.h"

namespace huru
{
	BoxCollider2D::BoxCollider2D() :
		Collider(eColliderType::Rect2D)
	{

	}

	BoxCollider2D::~BoxCollider2D()
	{

	}

	void BoxCollider2D::Initialize()
	{

	}

	void BoxCollider2D::Update()
	{

	}

	void BoxCollider2D::LateUpdate()
	{

	}

	void BoxCollider2D::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Vector2 offset = GetOffset();
		Vector2 size = GetSize();

		if (renderer::mainCamera)
			pos = renderer::mainCamera->CalculatePosition(pos);


		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

	
		Vector2 leftTop = pos + offset - size / 2.f;

		Rectangle(hdc,
			leftTop.x,
			leftTop.y,
			leftTop.x + size.x,
			leftTop.y + size.y);

		SelectObject(hdc, oldBrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
	}
}