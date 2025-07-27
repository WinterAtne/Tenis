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
	Rectangle rect;
	Vector2 velocity = {-2.0f, 2.0f};

public:
	Ball(Vector2 position) {
		rect = {position.x - 2.5f, position.y - 2.5f, 5.0f, 5.0f};
	}

	// Takes in the array of colliders to collide against
	// Returns whether a point has been scored
	SCORE Move(const Rectangle &play_field, const Rectangle colliders[], const int num_colliders) {
		rect.x += velocity.x;
		rect.y += velocity.y;

		/* Paddles */
		for (int i = 0; i < num_colliders; i++) {
			if (CheckCollisionRecs(rect, colliders[i])) {
				Rectangle overlap = GetCollisionRec(rect, colliders[i]);

				rect.x = colliders[i].x + ((velocity.x < 0) ? colliders[i].width + rect.width: -rect.width);

				// rect.y -= velocity.y;

				if (overlap.width < overlap.height) {
					velocity.x *= -1;
				} else {
					velocity.y *= -1;
				}
			}
		}

		/* Play Field */
		if (rect.y <= play_field.y || rect.y >= play_field.height - rect.height) {
			velocity.y *= -1;
		}

		/* Get Point */
		if (rect.x <= play_field.x) {
			return POINT_LEFT;
		} else if (rect.x >= play_field.width) {
			return POINT_RIGHT;
		} else {
			return NO_POINT;
		}
	}


	void Draw() {
		DrawRectangleRec(rect, COLOR);
	}
};
