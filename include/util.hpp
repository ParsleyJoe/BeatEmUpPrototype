#pragma once

enum class Direction {
	LEFT, RIGHT
};


// I dont even know how this works tbh
Vector2 operator-(Vector2 og, Vector2 other)
{
	return Vector2{ og.x - other.x, og.y - other.y };
}