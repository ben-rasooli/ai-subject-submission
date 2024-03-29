//----------------------------------------------------------------------------
// This is the entry-point for your game.
// Creates and runs the Game2D class which contains the game loop.
//----------------------------------------------------------------------------
#include "Game2D.h"
#include <time.h>

int main() 
{
	// Check for memeory leaks.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::srand(time(nullptr));

	// Create the Application.
	Game2D* game = new Game2D("AIE", 1280, 720, false);

	// Run the game loop.
	game->Run();

	// Clean up.
	delete game;

	return 0;
}