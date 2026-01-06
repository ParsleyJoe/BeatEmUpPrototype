#include "raylib.h"
#include "imgui.h"
#include <animation.hpp>
#include <player.hpp>
#include <iostream>


Player::Player()
	: pos(Vector2{ 100, 300 }), speed(200), attackOffset(13),
	attackCooldown(0.7f), lastAttacked(0), attackBox({0, 0, 10, 10}), hitBox({300, 300, 120, 120}),
	state(PlayerState::MOVING)
{
	playerIdleText = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/player.png");
	playerAttackSheet = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/playerAttack.png");
	attackAnim = {1, 3, 0, 0.2f, 0.5f, ONESHOT};
}

void Player::Update(float dt)
{
        switch(state)
	{
	case PlayerState::MOVING:
		if (IsKeyPressed(KEY_SPACE) && !attacking)
		{
			state = PlayerState::ATTACKING;
			break;
		}
		Move(dt);
		break;
	case PlayerState::ATTACKING:
		Attack(dt);
		break;
	case PlayerState::HIT:
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
		Rectangle frame = AnimationFrame((Animation*)&attackAnim, attackAnim.last);
		DrawTexturePro(playerAttackSheet, frame, hitBox, {0}, 0.0f, WHITE);
	}
	
	// Debug Draw Player hitbox
	DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, BLUE);
	ImGui::SliderFloat("Player attackFor", (float*)&attackFor, 0.0f, 2.0f);
	ImGui::Text("Player Attacking: %s", attacking ? "true" : "false");

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
	hitBox = {pos.x, pos.y, hitBox.width, hitBox.height};
}

void Player::Attack(float dt)
{
	if (attacking)
	{
		if (attackingTimer < attackFor)
		{
			attackingTimer += dt;
			// [DEBUG] Attack Point Rectangle
			DrawRectangle(attackBox.x, attackBox.y, 5, 5, DARKBROWN);
		}
		else
		{
			attacking = false;
			attackAnim.cur = 0.0f;
			state = PlayerState::MOVING;
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
