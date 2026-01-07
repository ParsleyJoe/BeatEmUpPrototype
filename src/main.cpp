#include "raylib.h"

#include <game.hpp>
#include <enemy.hpp>
#include <player.hpp>


// TODO: move collisions out of main
void CheckCollisions(Enemy &enemy, Player &player);

int main(void)
{
	Game game;
	game.Init();
	game.Start();

	while (!WindowShouldClose())
	{
		// Updating Entities
		// -----------------
		game.Update();
//		CheckCollisions(enemy, player);

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

