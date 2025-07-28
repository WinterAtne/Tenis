#include "paddle.hpp"
#include <raylib.h>

Paddle::Paddle(Vector2 position, KeyboardKey up, KeyboardKey down) {
	rect.x = position.x;
	rect.y = position.y;
	this->up = up;
	this->down = down;
}

void Paddle::Update() {
	if (IsKeyDown(up)) {
		rect.y-=max_speed;
		if (rect.y < 0) {
			rect.y = 0;
		} 
	}

	if (IsKeyDown(down)) {
		rect.y+=max_speed;
		if (rect.y > GetScreenHeight() - rect.height) {
			rect.y = GetScreenHeight() - rect.height;
		}
	}
}

void Paddle::Draw() {
	DrawRectangleRec(rect, RAYWHITE);
}
