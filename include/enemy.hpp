#pragma once
#include <raylib.h>
#include <raymath.h>

class Player;
enum class Direction;

// HIT means got hit
enum class EnemyState {
	MOVING, HIT, ATTACK
};

class Enemy
{
private:
	Direction dir;
	int health = 50;
	EnemyState state = EnemyState::MOVING;
	bool active = true;
public:
	Vector2 pos = { 500, 300 };

	Rectangle attackBox = {-100, -100, 10.0f, 10.0f};
	float attackOffset = 30.0f;
	bool attacking = false;
	float lastAttack = 0.0f;
	float attackTimer = 0.3f;
	float attackFor = 0.5f;
	float attackingTimer = 0.0f;

	int speed = 150;

	void Draw();
	void Update(float dt,Player& player);
	void Move(float dt, Player& player);
	void Attack(float dt);
	void DamageRecoil();
};
