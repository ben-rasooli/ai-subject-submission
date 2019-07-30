#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Game.h"
#include "Font.h"
#include "Input.h"
#include "Level.h"

class Game2D : public aie::Game
{
public:
	Game2D(const char* title, int width, int height, bool fullscreen);
	virtual ~Game2D();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:
	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Level* _level;
};