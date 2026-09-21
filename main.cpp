#include "Game.h"


int main()
{
	srand(0);
	
	InitWindow(710, 990, "TETRIS");
	
	Game game = builGame();
	
	while (!WindowShouldClose()) {

		updateGame(game, GetFrameTime());
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		drawBackground(game);
		drawButtonsBoard(game);
		drawPiecesTextures(game);
		drawCurrentPiece(game);
		
		EndDrawing();
	}
	
	return 0;
}


