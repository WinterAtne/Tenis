#include "ball.hpp"

#include <cmath>
#include <cstdlib>
#include <raylib.h>

bool Ball::paddle_collision(const Paddle &paddle) {
	if (CheckCollisionRecs(rect, paddle.rect)) {
		rect.x -= velocity.x * GetFrameTime() * 60;
		rect.y -= velocity.y * GetFrameTime() * 60;
		velocity.x *= -1;
		PlaySound(hit_sound);
		return true;
	}

	return false;
}

Ball::Ball(Vector2 position, int round) {
	rect = {position.x - 2.5f, position.y - 2.5f, 5.0f, 5.0f};

	int x_sign = ((round % 2 == 0) ? -1 : 1);
	int y_sign = ((round % 3 == 0) ? -1 : 1);

	float slope = y_sign * ((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + 1.0f) / 2.0f;
	float angle = std::atan(slope);


	float speed = (speed_increase * round) + min_speed;
	if (speed > max_speed) { speed = max_speed; }

	velocity.x = x_sign * std::cos(angle) * (speed);
	velocity.y = std::sin(angle) * (speed);
}

// Literally every bug in this game exists in this one function;
SCORE Ball::Move(const Rectangle &play_field, const Paddle &left_paddle, const Paddle &right_paddle) {
	rect.x += velocity.x * GetFrameTime() * 60;
	rect.y += velocity.y * GetFrameTime() * 60;

	/* Paddles */
	bool collided = false;
	if (velocity.x > 0) {
		collided = paddle_collision(right_paddle);
	} else {
		collided = paddle_collision(left_paddle);
	}

	/* Play Field */
	if (!collided && (rect.y <= play_field.y || rect.y >= play_field.height - rect.height)) {
		rect.x -= velocity.x * GetFrameTime() * 60;
		rect.y -= velocity.y * GetFrameTime() * 60;
		velocity.y *= -1;
		PlaySound(hit_sound);
	}

	/* Get Point */
	if (rect.x <= play_field.x) {
		return POINT_RIGHT;
	} else if (rect.x >= play_field.width) {
		return POINT_LEFT;
	} else {
		return NO_POINT;
	}
}

void Ball::Draw() {
	DrawRectangleRec(rect, COLOR);
}
