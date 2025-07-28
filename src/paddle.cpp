#include "paddle.hpp"

#include <cmath>
#include <raylib.h>

Paddle::Paddle(Vector2 position, KeyboardKey up, KeyboardKey down) {
	rect.x = position.x;
	rect.y = position.y;
	this->up = up;
	this->down = down;
}

void Paddle::Update() {
	if (IsKeyDown(up)) {
		velocity = std::lerp(velocity, -max_speed, acceloration);
	} else if (IsKeyDown(down)) {
		velocity = std::lerp(velocity, max_speed, acceloration);
	} else {
		velocity = std::lerp(velocity, 0, decceloration);
	}

	rect.y += velocity * GetFrameTime() * 60;

	if (rect.y < 0) {
		rect.y = 0;
	} else if (rect.y > GetScreenHeight() - rect.height) {
		rect.y = GetScreenHeight() - rect.height;
	}
}

void Paddle::Draw() {
	DrawRectangleRec(rect, RAYWHITE);
}
