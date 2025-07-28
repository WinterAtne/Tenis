#pragma once
#include <raylib.h>

typedef enum SCORE {
	POINT_RIGHT,
	POINT_LEFT,
	NO_POINT,
} SCORE;

class Ball {
private:
	static constexpr Color COLOR = RAYWHITE;
	static constexpr float min_speed = 2.0f;
	static constexpr float max_speed = 5.8f;
	static constexpr float speed_increase = 0.4f;
	Rectangle rect;
	Vector2 velocity;

public:
	Ball(Vector2 position, int round);

	// Takes in the array of colliders to collide against
	// Returns whether a point has been scored
	SCORE Move(const Rectangle &play_field, const Rectangle colliders[], const int num_colliders);

	void Draw();
};
