#include "raylib.h"
#include <iostream>
#include <enemy.hpp>
#include <player.hpp>
#include <util.hpp>
#include <util.hpp>
#include <imgui.h>

void Enemy::LoadTextures()
{
	idleTexture = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/enemy.png");
	attackTexture = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/enemyAttack.png");
	attackAnim = { .first = 0,
		.last = 2, .cur = 0, .speed = 0.7f, .durationLeft = 0.0f,
		.type = ONESHOT, .action = ATTACK, .actionFrame = 2};

	hitTexture = LoadTexture("E:/RonitCodeStuff/GameDev/BeatEmUpPrototype/art/sprites/enemyHit.png");
}

// Draw the enemy
void Enemy::Draw() 
{
	// Cannot declare variables inside switch
	Rectangle frame;

	switch (state) 
	{
	case EnemyState::MOVING:
		DrawTexturePro(idleTexture, {0.0f, 0.0f, static_cast<float>(idleTexture.width), static_cast<float>(idleTexture.height)}, hitBox, {0}, 0.0f, WHITE);
		break;

	case EnemyState::ATTACK:
		frame = AnimationFrame(&attackAnim, 3);
		frame.width *= dir;
		DrawTexturePro(attackTexture, frame, hitBox, {0.0f}, 0.0f, WHITE);
		break;
	case EnemyState::HIT:
		Rectangle source =  {0.0f, 0.0f, static_cast<float>(hitTexture.width), static_cast<float>(hitTexture.height)};
		DrawTexturePro(hitTexture, source, hitBox, {0}, 0.0f, WHITE);
		std::cout << "(DrawingFunction)Enemy got hit" << std::endl;
		break;
	}
	
	DrawRectangleLines(hitBox.x, hitBox.y, hitBox.width, hitBox.height, RED);
	
	ImGui::Checkbox("Activate Enemy", &active);
}

// Handles the Actual AI of the enemy
void Enemy::Update(float dt, Player& player)
{
	if (!active) { return; }

	float dist = Vector2Distance({ player.GetPosition() }, { hitBox.x, hitBox.y });
	switch (state)
	{
	case EnemyState::MOVING:
		if (dist < 60.0f) { state = EnemyState::ATTACK; break; }
		Move(dt, player);
		break;
	case EnemyState::ATTACK:
		AnimationUpdate(&attackAnim);
		std::cout << attackAnim.cur << std::endl;
		Attack(dt);

		if (!attacking && dist > 60.0f) { 
			ResetAttackLogic(); 
			state = EnemyState::MOVING; 
		}
		break;
	case EnemyState::HIT:
		DamageRecoil();
		break;
	}

	// -- DEBUG DRAW ---
	if (attacking)
	{
		DrawRectangleRec(attackBox, RED);
	}


}

// Movement Function
void Enemy::Move(float dt, Player& player)
{
	Vector2 playerPos = player.GetPosition();
	dir = ((playerPos.x < hitBox.x)) ? Direction::LEFT : Direction::RIGHT;
	
	Vector2 moveDir = playerPos - Vector2{hitBox.x, hitBox.y};
	moveDir = Vector2Normalize(moveDir);
	// Multiply speed corresponding to direction
	hitBox.x += moveDir.x * speed * dt; 
	hitBox.y += moveDir.y * speed * dt;

}

// Attack Logic
void Enemy::Attack(float dt)
{
	if (attacking)
	{
		attackingTimer += dt;
		if (GetTime() - attackFor >= attackingTimer)
		{
			ResetAttackLogic();
			std::cout << "SET TO ZERO AAAAAAAAAAAAAAAAHHH!!" << std::endl;
		}
	}

	if (!attacking && IsCurFrameAction(&attackAnim))// && (GetTime() - lastAttack) > attackTimer)
	{
		// Initiate attack, and keep attacking for "attackFor" var
		attackingTimer = 0.0f;
		attacking = true;
		attackBox = { hitBox.x + (attackOffset * dir), hitBox.y , attackBox.width, attackBox.height };
	}

}

void Enemy::ResetAttackLogic()
{
	attacking = false;
	attackingTimer = 0.0f;
	attackAnim.cur = 0;
	lastAttack = GetTime(); // Sets the reset time for attack
	state = EnemyState::MOVING;
}

void Enemy::TakeDamage(int damage)
{
	health -= damage;
	DamageRecoil();
}

// Damaged Animation
void Enemy::DamageRecoil()
{
	if (state != EnemyState::HIT)
	{
		state = EnemyState::HIT;
	}

	float dt = GetFrameTime();
	static float animationTime = 0.3f;
	if (animationTime >= 0.0f)
	{
		hitBox.x -= speed * dir * dt;
		animationTime -= dt;
	}
	else
	{
		// States will be handled once it is set back to moving
		state = EnemyState::MOVING;
		animationTime = 0.3f;
	}

}
