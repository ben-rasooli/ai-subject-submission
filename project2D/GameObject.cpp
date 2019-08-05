#include "GameObject.h"

GameObject::GameObject()
{
	_type = "";
	_texture = nullptr;
	_parent = nullptr;
	_collider = nullptr;
}

GameObject::GameObject(const char * textureName)
{
	_type = "";
	_texture = new aie::Texture(("./textures/" + std::string(textureName)).c_str());
	_parent = nullptr;
	_collider = nullptr;
}

GameObject::~GameObject()
{
	for (int i = 0; i < _childList.Count(); i++)
		if (_childList[i])
			delete _childList[i];

	if (_texture)
	{
		delete _texture;
		_texture = nullptr;
	}

	if (_collider)
	{
		delete _collider;
		_collider = nullptr;
	}
}

void GameObject::Update(float deltaTime)
{
	for (int i = 0; i < _childList.Count(); i++)
		_childList[i]->Update(deltaTime);
}

void GameObject::Draw(aie::Renderer2D * renderer)
{
	renderer->SetRenderColour(0xFFFFFFFF);

	if (_texture && _isActive)
		renderer->DrawSpriteTransformed3x3(_texture, _globalTransform);

	for (int i = 0; i < _childList.Count(); i++)
		_childList[i]->Draw(renderer);
}

void GameObject::OnCollision(GameObject * other)
{
}

void GameObject::UpdateGlobalTransform()
{
	if (_parent)
		_globalTransform = _parent->_globalTransform * _localTransform;
	else
		_globalTransform = _localTransform;

	for (int i = 0; i < _childList.Count(); i++)
		_childList[i]->UpdateGlobalTransform();
}

void GameObject::SetActive(bool value)
{
	_isActive = value;
}

void GameObject::SetPosition(Vector2 pos)
{
	_localTransform.setPosition(pos);

	if (_collider)
		_collider->SetPosition(GetPosition());
}

void GameObject::SetPosition(float x, float y)
{
	_localTransform.setPosition(x, y);

	if (_collider)
		_collider->SetPosition(GetPosition());
}

void GameObject::SetRotation(float radians)
{
	_localTransform.setRotateZ(radians);
}

void GameObject::SetScale(Vector2 scale)
{
	_localTransform.setScale(scale);
}

void GameObject::Translate(Vector2 translation)
{
	Vector2 currentPos = GetPosition();
	SetPosition(currentPos.x + translation.x, currentPos.y + translation.y);
}

void GameObject::Rotate(float radians)
{
	SetRotation(GetRotation() + radians);
}

void GameObject::SetParent(GameObject * parent)
{
	_parent = parent;
	parent->AddChild(this);
}

void GameObject::AddChild(GameObject * child)
{
	_childList.PushBack(child);
}

Vector2 GameObject::GetPosition()
{
	return _localTransform.getPosition();
}

float GameObject::GetRotation()
{
	return _localTransform.getRotation();
}

Vector2 GameObject::GetScale()
{
	return Vector2();
}

GameObject * GameObject::GetParent()
{
	return _parent;
}
