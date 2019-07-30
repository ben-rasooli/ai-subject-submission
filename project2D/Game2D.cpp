#include "Game2D.h"

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	// Create some textures for testing.
	m_font = new aie::Font("./font/consolas.ttf", 18);

	// Create a player object.
	_level = new Level();
}

Game2D::~Game2D()
{
	// Delete player.
	delete _level;

	// Deleted the textures.
	delete m_font;

	// Delete the renderer.
	delete m_2dRenderer;
}

void Game2D::Update(float deltaTime)
{
	// Update the player.

	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();

	// Exit the application if escape is pressed.
	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	// Draw the player.
	_level->Draw(m_2dRenderer);

	// Demonstrate animation.
	float animSpeed = 10.0f;
	int frame = ((int)(time * animSpeed) % 6);
	float size = 1.0f / 6.0f;
	m_2dRenderer->SetUVRect(frame * size, 0.0f, size, 1.0f);
	m_2dRenderer->SetUVRect(0.0f, 0.0f, 1.0f, 1.0f);
	
	// Draw some text.

	m_2dRenderer->SetRenderColour(1.0f, 1.0f, 1.0f, 0.5f);
	float windowHeight = (float)application->GetWindowHeight();
	m_2dRenderer->DrawText2D(m_font, "Press ESC to quit!", 15.0f, windowHeight - 25.0f);

	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}