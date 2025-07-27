#include <emscripten.h>
#include <raylib.h>

void loop() {
	BeginDrawing();
		DrawText("Hello, World!", 200, 200, 20, RAYWHITE);
	EndDrawing();
}

int main(void) {
	InitWindow(800, 450, "Pong!");
	emscripten_set_main_loop(loop, 60, true);
	CloseWindow();
	return 0;
}
