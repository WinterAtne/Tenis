#pragma once
#include <raylib.h>

#include "paddle.hpp"

typedef enum SCORE {
	POINT_RIGHT,
	POINT_LEFT,
	NO_POINT,
} SCORE;

extern Sound hit_sound;

class Ball {
private:
	static constexpr Color COLOR = RAYWHITE;
	static constexpr float min_speed = 4.4f;
	static constexpr float max_speed = 6.0f;
	static constexpr float speed_increase = 0.4f;

	Rectangle rect;
	Vector2 velocity;

	bool paddle_collision(const Paddle &paddle);

public:
	Ball(Vector2 position, int round);

	// Takes in the array of colliders to collide against
	// Returns whether a point has been scored
	SCORE Move(const Rectangle &play_field, const Paddle &left_paddle, const Paddle &right_paddle);

	void Draw();
};
