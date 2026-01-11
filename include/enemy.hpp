#pragma once
#include "animation.hpp"
#include <raylib.h>
#include <raymath.h>

class Player;
enum Direction;

// HIT means got hit
enum class EnemyState {
	MOVING, HIT, ATTACK
};

class Enemy
{
private:
	Direction dir;
	int health = 20;
	EnemyState state = EnemyState::MOVING;
	bool active = true;

	Texture2D idleTexture;
	Texture2D attackTexture;
	Texture2D hitTexture;

	Animation attackAnim;
public:
	Vector2 pos = { 500, 300 };
	int speed = 100;

	Rectangle hitBox = {0, 0, 50.0f, 50.0f};
	Rectangle attackBox = {-100, -100, 10.0f, 10.0f};

	// Attacking Vars
	float attackOffset = 30.0f;
	bool attacking = false;
	float lastAttack = 0.0f;
	float attackTimer = 0.0f;
	float attackFor = 0.1f;
	float attackingTimer = 0.0f;

	void LoadTextures();

	void Draw();
	void Update(float dt,Player& player);

	void Move(float dt, Player& player);

	void Attack(float dt);
	// Reset attacking vars and set state
	void ResetAttackLogic();

	void TakeDamage(int damage);
	void DamageRecoil();
};
