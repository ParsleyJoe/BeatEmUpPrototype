#include "raylib.h"
#include <animation.hpp>
#include <player.hpp>
#include <iostream>


Player::Player()
	: pos(Vector2{ 100, 300 }), speed(200), attackOffset(13),
	attackCooldown(0.7f), lastAttacked(0), attackBox({0, 0, 10, 10}), hitBox({300, 300, 120, 120}),
	state(PlayerState::MOVING)
{
	playerIdleText = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/player.png");
	attackAnim = {0, 2, 0, 0.2f, 0.5f, REPEATING};
}

void Player::Update(float dt)
{
	if (IsKeyDown(KEY_SPACE) && !attacking)
	{
		state = ATTACKING;
	}

        switch(state)
	{
	case MOVING:
		Move(dt);
		break;
	case ATTACKING:
		Attack(dt);
		break;
	case HIT:
		break;
	}
}

void Player::Draw() const
{
	if (!attacking)
	{
		DrawTexturePro(playerIdleText, {0, 0, (float)playerIdleText.width, (float)playerIdleText.height}, hitBox, {0, 0}, 0.0f, WHITE);
	}
	else
	{
		AnimationUpdate((Animation*)&attackAnim);
	}
	
	// Debug Draw Player hitbox
	DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, BLUE);


	DrawHealthBar();
}

void Player::DrawHealthBar() const
{
	DrawRectangleLines(10, 10, 70, 20, BLACK);
	DrawRectangle(10, 10, 70.0f * (health / 100.0f), 20, RED);
}

void Player::TakeDamage()
{
	if (GetTime() - lastDamageTime >= invulTimer)
	{
		lastDamageTime = GetTime();
		health -= 20;
		std::cout << "Player hit" << health << std::endl;
	}
}

void Player::Move(float dt)
{
	if (IsKeyDown(KEY_LEFT))
	{
		pos.x -= speed * dt;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		pos.x += speed * dt;
	}
	if (IsKeyDown(KEY_UP))
	{
		pos.y -= speed * dt;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		pos.y += speed * dt;
	}
	hitBox = {pos.x, pos.y, 30, 30};
}

void Player::Attack(float dt)
{
	if (attacking)
	{
		if (attackingTimer < attackFor)
		{
			// [DEBUG] Attack Point Rectangle
			attackingTimer += dt;
			DrawRectangle(attackBox.x, attackBox.y, 5, 5, DARKBROWN);
		}
		else
		{
			attacking = false;
			state = MOVING;
			attackingTimer = 0.0f;
			lastAttacked = GetTime();
		}
	}


	if (!attacking && (GetTime() - lastAttacked) > attackCooldown) 
	{ 
		attacking = true;
		attackBox = { pos.x + 30 + attackOffset, pos.y + 15 , attackBox.width, attackBox.height};
	}
}

Vector2 Player::GetPosition() const
{
	return pos;
}
