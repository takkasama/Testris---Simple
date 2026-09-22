#pragma once
#include "Board.h"
#include "GameGraphic.h"
#include "Level.h"
#include "Player.h"



// CONECCION ENTRE BOARD Y LAS TEXTURAS
struct Game
{
	Board board;
	Level level;

	GameGraphic graphic;
	
	// PARA EL MANEJO DE LAS PERSITENCIA LOCAL EL GUARDADO DE PUNTOS POR JUEGADOR
	Player player;
};


Game builGame()
{
	Game game;
	game.board = buildBoard();
	game.level = buildLevel();
	game.graphic = buildGameGraphic();
	game.player = buildPlayer();

	return game;
}



void updateGame(Game &game, float deltaTime)
{
	
	game.graphic.updateTimer += deltaTime;
	
	if (game.graphic.updateTimer >= game.level.speed)
	{
		
		game.graphic.updateTimer -= game.level.speed;
		updateBoard(game.board);
		updateLevel(game.level, getFullRows(game.board));
	}
	
	
}

void movePieces(Game & game, bool left , bool right ,
				bool rotate, bool isToBottom, 
				bool isKeep ,float deltaTime)
{
	game.graphic.keyTimer += deltaTime;
	
	if(game.graphic.keyTimer >= KEY_DELAY)
	{
		game.graphic.keyTimer = 0.0f;
		
		if(left)
			moveLeft(game.board);
		if(right)
			moveRight(game.board);
		if(rotate && canRotate(game.board))
			rotatePiece(game.board.currentPiece);
		if(isToBottom)
			moveToBottom(game.board);
		if(isKeep)
			holdPiece(game.board);
	}
}

void validateButtons(Game & game)
{
	if(isPressTexture(game.graphic.textures , buildPosition(BUTTON_1_X , BUTTON_Y) , "back"))
		goToPrev(game.board);

	if(isPressTexture(game.graphic.textures , buildPosition(BUTTON_2_X , BUTTON_Y) , "advance"))
		goToNext(game.board);

}



void drawPiecesTextures(Game & game)
{
	Row *currentRow = game.board.top;
	int y = 0;
	while (currentRow != nullptr)
	{
		for (int x = 0; x < Row::MAX_COLUMNS; x++)
		{
			
			if (!currentRow->cell[x].isSelected)
				continue;
			
			
			string nameImg = "Tetri" + string(1, currentRow->cell[x].type);			
			Position pos = getTexturePosition(x, y);
			drawTexture(game.graphic.textures, nameImg , pos);
			
		}
		y++;
		currentRow = currentRow->next;
	}
}

void drawCurrentPiece(Game & game)
{
	TetriPiece piece = game.board.currentPiece;
	
	if (piece.type == 'D')
		return;
	string nameImg = "Tetri" + string(1, piece.type);
	
	for (int i = 0; i < TetriPiece::SIZE; i++)
	{
		int x = piece.pieces[i].x;
		int y = piece.pieces[i].y;
		
		Position pos = getTexturePosition(x, y);
		
		drawTexture(game.graphic.textures , nameImg , pos);
	}
}



void drawBackground(Game & game)
{
	
	Position pos = buildPosition(0.0f , 0.0f);
	drawTexture(game.graphic.textures , "board" , pos);
	
}

void drawButtonsBoard(Game & game)
{	
	drawTexture(game.graphic.textures, "back" ,buildPosition(BUTTON_1_X, BUTTON_Y));
	drawTexture(game.graphic.textures, "advance" ,buildPosition(BUTTON_2_X, BUTTON_Y));
	drawTexture(game.graphic.textures, "pause" ,buildPosition(BUTTON_3_X, BUTTON_Y));
	drawTexture(game.graphic.textures, "retry" ,buildPosition(BUTTON_4_X, BUTTON_Y));
}


void drawHoldPiece(Game & game)
{
	
	Position pos  = buildPosition(HOLD_X , HOLD_Y);
	
	TetriPiece piece = game.board.hold->next != nullptr ? 
		game.board.hold->next->tetriPiece : buildDefault();
	
	string nameImg  = "TetriC" + string(1 , piece.type);
	
	drawTexture(game.graphic.textures , nameImg , pos);
	
}


//SE CONTRUYO EL TABLERO CON UNA FILA DE MAS, POR LO QUE DICHA FILA SE CONTRUYE CON UN FILA DE TETRI DEFAULT 
void drawLastRow(Game & game)
{
	TetriPiece defaultPiece = buildDefault();
	defaultPiece.pieces[0].y = 20;
	
	for(int i = 0; i < Row::MAX_COLUMNS; i++){
		
		Position pos = buildPosition(defaultPiece.pieces[0].x , defaultPiece.pieces[0].y);
		
		pos  = getTexturePosition(pos.x , pos.y);
		drawTexture(game.graphic.textures, "TetriD" , pos);
		
		defaultPiece.pieces[0].x++;
	}
}

void drawNextPieces(Game & game)
{
	
	for(int i = 0; i < Bag::WAIT_SIZE; i++){
		TetriPiece piece = game.board.queueBag->currentBag->waitPieces[i];
		
		string nameImg  = "TetriC" + string(1 , piece.type);
		
		drawTexture(game.graphic.textures, nameImg, getTexturePositionToNextPieces(i));
		
	}
}





