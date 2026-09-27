#include<ctime>
#include "header/Game.h"

int main()
{
	srand(time(nullptr));	
	SetConfigFlags( FLAG_WINDOW_TOPMOST | FLAG_WINDOW_TRANSPARENT);
	
	const static int WIDTH = 710;
	const static int HEIGHT = 990;
	
	InitWindow(WIDTH, HEIGHT, "TETRIS");
	SetTargetFPS(60);
	
	Game game = builGame();
	KeyPressed key;
	
	while (!WindowShouldClose()) {
		float time = GetFrameTime();
		
		if(IsKeyPressed(KEY_J)) key.currentKey = KeyPressed::KEY_J;
		else if(IsKeyPressed(KEY_L)) key.currentKey = KeyPressed::KEY_L;
		else if(IsKeyPressed(KEY_K)) key.currentKey = KeyPressed::KEY_K;
		else if(IsKeyPressed(KEY_H)) key.currentKey = KeyPressed::KEY_H;
		else if(IsKeyPressed(KEY_SPACE)) key.currentKey = KeyPressed::KEY_SPACE;
		else if(IsKeyPressed(KEY_O)) key.currentKey = KeyPressed::KEY_O;
		else if(IsKeyPressed(KEY_U)) key.currentKey = KeyPressed::KEY_U;
		
		
		updateGame(game, key , time);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		drawGame(game);
		EndDrawing();
		
	}
	
	return 0;
}



