#include "raylib.h"

#include <enemy.hpp>
#include <game.hpp>
#include <player.hpp>

int main() 
{
	Game game;
	game.Init();
	game.Start();

	while (!WindowShouldClose())
	{
		// Updating Entities
		// -----------------
		game.Update();
		// ----------
		// END UPDATE

		// DRAWING FUNCTIONS
		// -----------------
		BeginDrawing();
		game.ImGuiDrawBegin();

		game.Draw();

		game.ImGuiDrawEnd();

		EndDrawing();
		// -----------
		// END DRAWING
	}

	game.Shutdown();
	return 0;
}
