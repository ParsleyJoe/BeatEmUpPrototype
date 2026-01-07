#pragma once
#include <raylib.h>
#include <animation.hpp>

enum class PlayerState {
	MOVING,
	HIT,
	ATTACKING
};

class Player
{
private:
	Vector2 pos;
	int speed;

	int attackOffset;
	float attackCooldown;
	float lastAttacked;

	int health = 100;
	float invulTimer = 0.3f;
	float lastDamageTime = 0.0f;
	
	float attackingTimer = 0.0f;
	float attackFor = 0.56f;
	
	Texture2D playerIdleText;
	Texture2D playerAttackSheet;
	Animation attackAnim;

	PlayerState state;
public:
	bool attacking = false;
	Rectangle attackBox;
	Rectangle hitBox; // TODO:  ADD HITBOX

	Player();
	void Draw() const;
	void Update(float dt);

	void DrawHealthBar() const;
	void TakeDamage();
	void Move(float dt);
	void Attack(float dt);
	Vector2 GetPosition() const;
};
