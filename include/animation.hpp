#pragma once

struct Rectangle;

enum Action {
	NONE,
	ATTACK
};


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

	Action action;
	int actionFrame = -1;
};

void AnimationUpdate(Animation *self);
Rectangle AnimationFrame(Animation *self, int numFramesPerRow);

bool IsCurFrameAction(Animation* self);
