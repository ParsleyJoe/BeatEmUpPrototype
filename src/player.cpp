#include "raylib.h"
#include "imgui.h"
#include "util.hpp"
#include <animation.hpp>
#include <player.hpp>
#include <iostream>


Player::Player()
	: speed(200), attackOffset(13), attackCooldown(0.7f),
	lastAttacked(0), attackBox({0, 0, 10, 10}),
	hitBox({300, 300, 50, 50}), state(PlayerState::MOVING)
{
	attackAnim = {1, 3, 0, 0.07f, 0.0f, ONESHOT};
}

void Player::LoadTextures()
{
	playerIdleText = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/player.png");
	playerAttackSheet = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/playerAttack.png");
}

void Player::Update(float dt)
{
        if (IsKeyPressed(KEY_SPACE) && !attacking)
	{
		state = PlayerState::ATTACKING;
	}

	switch(state)
	{
	case PlayerState::MOVING:
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
	if (attacking)
	{
		AnimationUpdate((Animation*)&attackAnim);
		Rectangle frame = AnimationFrame((Animation*)&attackAnim, attackAnim.last);

		// Base it on direction
		frame.width *= dir;
		DrawTexturePro(playerAttackSheet, frame, hitBox, {0}, 0.0f, WHITE);
	}
	else 
	{
		DrawTexturePro(playerIdleText, {0, 0, (float)playerIdleText.width * dir, (float)playerIdleText.height}, hitBox, {0, 0}, 0.0f, WHITE);
	}
	
	// Debug Draw Player hitbox
	DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, BLUE);

	// DEBUG PLAYER ATTACK
	// -------------------
	ImGui::SliderFloat("Player attackFor", (float*)&attackFor, 0.0f, 2.0f);
	ImGui::Text("Player Attacking: %s", attacking ? "true" : "false");

	bool space = IsKeyPressed(KEY_SPACE);
	ImGui::Text("Space Bar pressed: %s", space ? "true" : "false");
	ImGui::SliderFloat("Attack Anim speed: ", (float*)&attackAnim.speed, 0.0f, 2.0f);
	ImGui::SliderFloat("Attack Anim duration: ", (float*)&attackAnim.durationLeft, 0.0f, 2.0f);
	// -------------------

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
		hitBox.x -= speed * dt;
		dir = Direction::LEFT;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		hitBox.x += speed * dt;
		dir = Direction::RIGHT;
	}
	if (IsKeyDown(KEY_UP))
	{
		hitBox.y -= speed * dt;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		hitBox.y += speed * dt;
	}
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
			attackAnim.cur = 0;
			state = PlayerState::MOVING;
			attackingTimer = 0.0f;
			lastAttacked = GetTime();
		}
	}
	else if (!attacking)// NOTE: GETTING RID OF COOLDOWN FIXED LAGGY ATTACK && (GetTime() - lastAttacked) > attackCooldown) 
	{ 
		attacking = true;

		// Start the attack from center of player
		Vector2 attackOrigin = { (hitBox.x + (hitBox.width / 2)), (hitBox.y + (hitBox.height / 2))};
		attackBox = { attackOrigin.x + (dir * attackOffset), attackOrigin.y , attackBox.width, attackBox.height};
	}
}

Vector2 Player::GetPosition() const
{
	return {hitBox.x, hitBox.y};
}
