#pragma once

#include <raylib.h>
class Paddle {
private:
	static constexpr float max_speed = 9.0f;
	static constexpr float acceloration = 0.25f;
	static constexpr float decceloration = 0.3f;

	float velocity = 0.0f;

	KeyboardKey up, down;

public:
	Rectangle rect = {0.0f, 0.0f, 10.0f, 50.0f};

	Paddle(Vector2 position, KeyboardKey up, KeyboardKey down);

	void Update();
	void Draw();
};
