#include <animation.hpp>
#include <raylib.h>

void AnimationUpdate(Animation *self)
{
	float dt = GetFrameTime();

	self->durationLeft -= dt;

	if (self->durationLeft <= 0.0f) {
		self->durationLeft = self->speed;
		self->cur++;

		if (self->cur > self->last) {
			switch(self->type)
			{
			case AnimationType::REPEATING:
				self->cur = self->first;
				break;
			case AnimationType::ONESHOT:
				self->cur = self->last;
				break;
			}
		}
	}

}

Rectangle AnimationFrame(Animation *self, int numFramesPerRow)
{
	int x = (self->cur % numFramesPerRow) * 16;
	int y = (self->cur / numFramesPerRow) * 16;

	return {
		.x = (float)x,
		.y = (float)y,
		.width = 16,
		.height = 16
	};
}
