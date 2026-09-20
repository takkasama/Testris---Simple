#include "Game.h"

int main()
{
	srand(0);
	
	InitWindow(800, 450, "TETRIS");
	while (!WindowShouldClose()) {

		
		BeginDrawing();
		ClearBackground(RAYWHITE);

		EndDrawing();
	}
	
	return 0;
}


