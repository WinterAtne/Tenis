#include "ball.hpp"

#include <cmath>
#include <cstdlib>
#include <raylib.h>

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

SCORE Ball::Move(const Rectangle &play_field, const Rectangle colliders[], const int num_colliders, int play_field_padding) {
	rect.x += velocity.x;
	rect.y += velocity.y;

	/* Paddles */
	for (int i = 0; i < num_colliders; i++) {
		if (CheckCollisionRecs(rect, colliders[i])) {
			Rectangle overlap = GetCollisionRec(rect, colliders[i]);

			rect.x = colliders[i].x + ((velocity.x < 0) ? colliders[i].width + rect.width: -rect.width);
			rect.y -= velocity.y;

			if (overlap.width < overlap.height) {
				velocity.x *= -1;
			} else {
				velocity.y *= -1;
			}

			PlaySound(hit_sound);
		}
	}

	/* Play Field */
	if ((rect.x > play_field_padding + colliders[0].width ||  rect.x < play_field.width - play_field_padding - colliders[0].width) &&
		 (rect.y <= play_field.y || rect.y >= play_field.height - rect.height)) {
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
