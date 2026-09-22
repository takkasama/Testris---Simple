#include "Game.h"

struct Player 
{
	string alias;
	int points;
	int maxRecord;
};

Player buildPlayer()
{
	Player player;
	player.alias = "NONE";
	player.points = 0;
	player.maxRecord = 0;
	
	return player;
}








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
				   IsKeyDown(KEY_R), IsKeyDown(KEY_SPACE),
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



