#include <enemy.hpp>
#include <player.hpp>
#include <util.hpp>
#include <util.hpp>
#include <iostream>
#include <imgui.h>

// Draw the enemy
void Enemy::Draw() 
{
	DrawRectangle(pos.x, pos.y, 30, 30, RED);
	
	ImGui::Checkbox("Activate Enemy", &active);
}

// Handles the Actual AI of the enemy
void Enemy::Update(float dt, Player& player)
{
	if (!active) { return; }

	float dist = Vector2Distance({ player.GetPosition() }, { pos });
	switch (state)
	{
	case EnemyState::MOVING:
		Move(dt, player);
		if (dist < 30.0f) { state = EnemyState::ATTACK; }
		break;
	case EnemyState::HIT:
		DamageRecoil();
		break;
	case EnemyState::ATTACK:
		Attack(dt);
		if (!attacking && dist > 30.0f) { state = EnemyState::MOVING; }
		break;
	}
	std::cout << "Enemy State " << static_cast<int>(state) << std::endl;
	std::cout << "Timer " << attackingTimer << std::endl;

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
	dir = ((playerPos.x < pos.x)) ? Direction::LEFT : Direction::RIGHT;
	
	Vector2 moveDir = playerPos - pos;
	moveDir = Vector2Normalize(moveDir);
	// Multiply speed corresponding to direction
	pos.x += moveDir.x * speed * dt; 
	pos.y += moveDir.y * speed * dt;

}

// Attack Logic
void Enemy::Attack(float dt)
{
	if (attacking)
	{
		if (attackingTimer < attackFor)
		{
			attackingTimer += dt;
		}
		else
		{
			attacking = false;
			attackingTimer = 0.0f;
			lastAttack = GetTime(); // Sets the reset time for attack
		}

	}
	
	if (!attacking && (GetTime() - lastAttack) > attackTimer)
	{
		// Initiate attack, and keep attacking for "attackFor" var
		attacking = true;
		int dirInt = ((dir == Direction::LEFT) ? -1 : 1);
		attackBox = { pos.x + (attackOffset * dirInt), pos.y , attackBox.width, attackBox.height };
	}

}

// Damaged Animation
void Enemy::DamageRecoil()
{
	if (state == EnemyState::MOVING)
	{
		state = EnemyState::HIT;
	}


	static float animationTime = 0.3f;
	if (animationTime >= 0.0f)
	{
		pos.x += speed;
	}
	else
	{
		state = EnemyState::MOVING;
		animationTime = 0.3f;
	}

}
