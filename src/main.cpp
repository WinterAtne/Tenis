#include <emscripten.h>
#include <raylib.h>
#include <sstream>

#include "ball.hpp"

const int screen_width = 800;
const int screen_height = 450;

const int paddle_edge_padding = 10;
const Vector2 paddle_dimensions = {10, 50};

const float paddle_speed = 5.0f;

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

Rectangle left_paddle = {
	paddle_edge_padding, screen_height/2.0f,
	paddle_dimensions.x, paddle_dimensions.y
};

Rectangle right_paddle = {
	screen_width - paddle_edge_padding - paddle_dimensions.x, screen_height/2.0f,
	paddle_dimensions.x, paddle_dimensions.y
};

Vector2 center = {
	screen_width/2.0f - 2.5, screen_height/2.0f - 2.5,
};

Ball ball = Ball(center, right_point + left_point);

int sign(int a) {
	if (a > 0) { return 1; }
	if (a < 0) { return -1; }
	return 0;
}

void move_paddle(Rectangle &rect, KeyboardKey up, KeyboardKey down) {

	if (IsKeyDown(up)) {
		rect.y-=paddle_speed;
		if (rect.y < 0) {
			rect.y = 0;
		} 
	}

	if (IsKeyDown(down)) {
		rect.y+=paddle_speed;
		if (rect.y > screen_height - paddle_dimensions.y) {
			rect.y = screen_height - paddle_dimensions.y;
		}
	}

}

void update() {
	move_paddle(left_paddle, KEY_W, KEY_S);
	move_paddle(right_paddle, KEY_I, KEY_K);

	SCORE point = ball.Move(play_field, (Rectangle[2]){left_paddle, right_paddle}, 2);
	if (point == POINT_RIGHT) {
		right_point++;
		ball = Ball(center, right_point + left_point);
	} else if (point == POINT_LEFT) {
		left_point++;
		ball = Ball(center, right_point + left_point);
	}
}

void render() {
	BeginDrawing();
		DrawRectangleRec(left_paddle, RAYWHITE);
		DrawRectangleRec(right_paddle, RAYWHITE);
		DrawRectangleRec(center_line, LIGHTGRAY);	
		ball.Draw();

		std::ostringstream score;
		score << left_point << " / " << right_point;

		DrawText(score.str().c_str(), 0, 0, 20, RAYWHITE);

	EndDrawing();
}

void loop() {
	update();
	render();
}

int main(void) {
	srand((time(0)));
	InitWindow(screen_width, screen_height, "Pong!");
	emscripten_set_main_loop(loop, 60, true);
	CloseWindow();
	return 0;
}
