#include "Game.h"






int main()
{
	srand(time(nullptr));	
	
	InitWindow(710, 990, "TETRIS");
	
	Game game = builGame();
	
	while (!WindowShouldClose()) {
		float deltaTime = GetFrameTime();
		
		updateGame(game, deltaTime);
		
		movePieces(game , 
				   IsKeyDown(KEY_J) , IsKeyDown(KEY_L),
				   IsKeyDown(KEY_K), IsKeyDown(KEY_SPACE),
				   IsKeyDown(KEY_F),
				   deltaTime);
		
		validateButtons(game);
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		drawBackground(game);
		drawButtonsBoard(game);
		drawPiecesTextures(game);
		drawLastRow(game);
		drawCurrentPiece(game);
		drawNextPieces(game);
		drawHoldPiece(game);

		EndDrawing();
	}
	
	return 0;
}



