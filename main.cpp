#include "header/Game.h"

int main()
{
	srand(time(nullptr));	
	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_TRANSPARENT);
	
	const static int WIDTH = 710;
	const static int HEIGHT = 990;
	
	
	
	InitWindow(WIDTH, HEIGHT, "TETRIS");
	SetTargetFPS(60);
	
	Game game = builGame();
	KeyPressed key;
	
	while (!WindowShouldClose()) {
		float time = GetFrameTime();
		
		if(IsKeyDown(KEY_J)) key.currentKey = KeyPressed::KEY_J;
		else if(IsKeyDown(KEY_L)) key.currentKey = KeyPressed::KEY_L;
		else if(IsKeyDown(KEY_K)) key.currentKey = KeyPressed::KEY_K;
		else if(IsKeyDown(KEY_H)) key.currentKey = KeyPressed::KEY_H;
		else if(IsKeyDown(KEY_SPACE)) key.currentKey = KeyPressed::KEY_SPACE;
		else if(IsKeyDown(KEY_O)) key.currentKey = KeyPressed::KEY_O;
		else if(IsKeyDown(KEY_U)) key.currentKey = KeyPressed::KEY_U;
		
		
		updateGame(game, key , time);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		drawGame(game);
		EndDrawing();
		
	}
	
	return 0;
}



