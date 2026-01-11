#include <collission.hpp>
#include "enemy.hpp"
#include "player.hpp"
#include "raylib.h"

void CheckCollisions(Enemy &enemy, Player &player)
{
	// Check Collisions
	if (enemy.attacking)
	{
		if (CheckCollisionRecs(enemy.attackBox, player.hitBox))
		{
			// enemy damage player
			player.TakeDamage();
		}
	}

	if (player.attacking)
	{
		if (CheckCollisionRecs(player.attackBox, enemy.hitBox))
		{
			enemy.TakeDamage(player.damage);
		}
	}
}
