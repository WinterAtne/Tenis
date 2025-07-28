#include <emscripten.h>
#include <raylib.h>
#include <sstream>

#include "ball.hpp"
#include "paddle.hpp"

const int screen_width = 800;
const int screen_height = 450;

const int paddle_edge_padding = 10;
const Vector2 paddle_dimensions = {10, 50};

const float paddle_speed = 7.5f;

int left_point = 0;
int right_point = 0;

Rectangle play_field {
	0, 0,
	screen_width, screen_height,
};

Rectangle center_line = {
	screen_width/2.0f - 2.5, 0,
	5, screen_height,
};

Paddle left_paddle = Paddle({paddle_edge_padding, screen_height/2.0}, KEY_W, KEY_S);
Paddle right_paddle = Paddle({screen_width - paddle_edge_padding - paddle_dimensions.x, screen_height/2.0f}, KEY_I, KEY_K);

Vector2 center = {
	screen_width/2.0f - 2.5, screen_height/2.0f - 2.5,
};

Ball ball = Ball(center, right_point + left_point);
Sound hit_sound = {};
Sound point_sound = {};

int sign(int a) {
	if (a > 0) { return 1; }
	if (a < 0) { return -1; }
	return 0;
}

void update() {
	left_paddle.Update();
	right_paddle.Update();

	SCORE point = ball.Move(play_field, (Rectangle[2]){left_paddle.rect, right_paddle.rect}, 2, paddle_edge_padding);
	if (point == POINT_RIGHT) {
		right_point++;
		ball = Ball(center, right_point + left_point);
		PlaySound(point_sound);
	} else if (point == POINT_LEFT) {
		left_point++;
		ball = Ball(center, right_point + left_point);
		PlaySound(point_sound);
	}
}

void render() {
	BeginDrawing();
		left_paddle.Draw();
		right_paddle.Draw();
		DrawRectangleRec(center_line, LIGHTGRAY);	
		ball.Draw();

		std::ostringstream left_text;
		std::ostringstream right_text;
		left_text << left_point;
		right_text << right_point;

		DrawText(
				left_text.str().c_str(),
				(screen_width/2.0f) - 10 - (MeasureText(left_text.str().c_str(), 20)),
				screen_height/2.0f,
				20.0f,
				RAYWHITE);

		DrawText(
				right_text.str().c_str(),
				(screen_width/2.0f) + 8,
				screen_height/2.0f,
				20.0f,
				RAYWHITE);
	EndDrawing();
}

void loop() {
	update();
	render();
}

int main(void) {
	srand((time(0)));
	InitWindow(screen_width, screen_height, "Pong!");
	SetWindowFocused();
	InitAudioDevice();

	hit_sound = LoadSound("resources/hit.wav");
	point_sound = LoadSound("resources/point.wav");

	SetTargetFPS(60);

	emscripten_set_main_loop(loop, 60, true);

	UnloadSound(hit_sound);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
