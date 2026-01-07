#include <collission.hpp>
#include "enemy.hpp"
#include "player.hpp"

void CheckCollisions(Enemy &enemy, Player &player)
{
	// Check Collisions
	if (CheckCollisionRecs(enemy.attackBox, player.hitBox))
	{
		// enemy damage player
		player.TakeDamage();
	}
}
