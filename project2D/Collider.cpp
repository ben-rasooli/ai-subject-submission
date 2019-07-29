#include "Collider.h"
#include "Vector2.h"
#include "Renderer2D.h"

Collider::Collider(Vector2 extend)
{
	_extend = extend;
}

void Collider::Draw(aie::Renderer2D * renderer)
{
	Vector2 min = GetMin();
	Vector2 max = GetMax();

	renderer->SetRenderColour(1.0f, 0.0f, 0.0f, 0.1f);
	renderer->DrawBox(min.x + _extend.x, min.y + _extend.y, max.x - min.x, max.y - min.y);
}

void Collider::SetPosition(Vector2 position)
{
	_position = position;
}

Vector2 Collider::GetMin()
{
	return _position - _extend;
}

Vector2 Collider::GetMax()
{
	return _position + _extend;
}

bool Collider::IsCollidingWith(Collider * other)
{
	Vector2 myMin = GetMin();
	Vector2 myMax = GetMax();
	Vector2 otherMin = other->GetMin();
	Vector2 otherMax = other->GetMax();

	//any gap
	if (myMax.x < otherMin.x || otherMax.x < myMin.x ||
		myMax.y < otherMin.y || otherMax.y < myMin.y)
		return false;

	return true;
}