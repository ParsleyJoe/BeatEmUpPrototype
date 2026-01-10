#pragma once

enum Direction {
	LEFT = -1, RIGHT = 1
};

struct Vector2;

// I dont even know how this works tbh
Vector2 operator-(Vector2 og, Vector2 other);

