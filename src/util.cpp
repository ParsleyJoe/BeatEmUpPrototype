#include <util.hpp>
#include <raylib.h>

Vector2 operator-(Vector2 og, Vector2 other)
{
	return Vector2{ og.x - other.x, og.y - other.y };
}
