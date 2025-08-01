#include <cstdio>
#include <emscripten.h>
#include <ostream>
#include <raylib.h>
#include <sstream>

#include "ball.hpp"
#include "paddle.hpp"

const int screen_width = 630;
const int screen_height = 500;

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
Sound hit_sound0 = {};
Sound hit_sound1 = {};
Sound hit_sound2 = {};
Sound point_sound = {};

int sign(int a) {
	if (a > 0) { return 1; }
	if (a < 0) { return -1; }
	return 0;
}

void update() {
	left_paddle.Update();
	right_paddle.Update();

	SCORE point = ball.Move(play_field, left_paddle, right_paddle);
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
	ClearBackground(BLACK);
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

		/* Uncomment for FPS count */
		// std::ostringstream fps;
		// fps << GetFPS();
		//
		// DrawText(
		// 		fps.str().c_str(),
		// 		(screen_height - 40.0f),
		// 		10.0f,
		// 		20.0f,
		// 		RAYWHITE);
	EndDrawing();
}

void loop() {
	update();
	render();
}

int main(void) {
	srand((time(0)));
	SetRandomSeed(time(0));
	InitWindow(screen_width, screen_height, "¡Tenis!");
	InitAudioDevice();

	hit_sound0 = LoadSound("resources/hit0.wav");
	hit_sound1 = LoadSound("resources/hit1.wav");
	hit_sound2 = LoadSound("resources/hit2.wav");
	point_sound = LoadSound("resources/point.wav");

	printf("INFO: sound may not play till you click the screen, this is a javascript problem.\n");
	emscripten_set_main_loop(loop, 0, true);

	UnloadSound(hit_sound0);
	UnloadSound(hit_sound1);
	UnloadSound(hit_sound2);
	UnloadSound(point_sound);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
