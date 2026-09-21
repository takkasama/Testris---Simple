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
				   IsKeyDown(KEY_LEFT) , IsKeyDown(KEY_RIGHT),
				   IsKeyDown(KEY_R), IsKeyDown(KEY_SPACE),
				   deltaTime);
		
		
		
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		drawBackground(game);
		drawButtonsBoard(game);
		drawPiecesTextures(game);
		drawLastRow(game);
		drawCurrentPiece(game);
		drawNextPieces(game);
		

		EndDrawing();
	}
	
	return 0;
}


//for(int y = 0; y < Board::MAX_ROWS; y++)
//{
//	Position pos = getTexturePosition(0, y);
//	
//	DrawText(
//			 TextFormat("%d", y),
//			 (int)pos.x,
//			 (int)pos.y,
//			 14,
//			 RED
//			 );
//}

