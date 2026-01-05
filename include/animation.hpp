#pragma once

struct Rectangle;

enum AnimationType {
	REPEATING,
	ONESHOT
};

struct Animation {
	int first;
	int last;
	int cur;

	float speed;
	float durationLeft;

	AnimationType type;
};

void AnimationUpdate(Animation *self);
Rectangle AnimationFrame(Animation *self); 
