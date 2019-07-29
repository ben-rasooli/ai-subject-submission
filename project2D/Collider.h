#pragma once
#include "Renderer2D.h"
#include "Vector2.h"

class Collider
{
public:
	Collider(Vector2 extend);

	void Draw(aie::Renderer2D* renderer);

	void SetPosition(Vector2 position);
	Vector2 GetPosition() { return _position; }
	Vector2 GetMin();
	Vector2 GetMax();
	Vector2 GetExtend() { return _extend; }

	bool IsCollidingWith(Collider* other);

private:
	Vector2 _position;
	Vector2 _extend;
};

