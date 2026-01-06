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

	Player player;
	Enemy enemy;

	while (!WindowShouldClose())
	{
		// Updating Entities
		// -----------------
		float dt = GetFrameTime();

		CheckCollisions(enemy, player);

		enemy.Update(dt, player);
		player.Update(dt);
		// ----------
		// END UPDATE

		// DRAWING FUNCTIONS 
		// -----------------
		BeginDrawing();
		game.ImGuiDrawBegin();

		ClearBackground(RAYWHITE);

		player.Draw();
		enemy.Draw();

		game.ImGuiDrawEnd();

		EndDrawing();

		// -----------
		// END DRAWING
	}

	game.Shutdown();

	return 0;
}

void CheckCollisions(Enemy &enemy, Player &player)
{
	// Check Collisions
	if (CheckCollisionRecs(enemy.attackBox, player.hitBox))
	{
		// enemy damage player
		player.TakeDamage();
	}
}
