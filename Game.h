#pragma once
#include "Board.h"
#include "GameGraphic.h"
#include "Level.h"
#include "Player.h"

//MANEJO DE ESTADOS DE JUEGO PARA EL CONTROL DEL FLUJO DE ESTE
struct State
{
	//congela el juego hasta que se vuelva activar el mismo estado
	const static int PAUSE = 0;
	//ciclo de juego normal
	const static int PLAY = 1;
	//cuando se acciona el boton de avanzar y retroceder para dar un tiempo de avanzar o retroceder libremente
	const static int REPRODUCE = 2;
	//acciones y flujo de menu
	const static int MENU = 3;
	//reproducir toda una partida despues de un gameover
	const static int REPRODUCE_GAME = 4;
	
	int currentState;
};



//FORMA DE ABREVIAR PARAMETROS DE LAS KEY USADAS PARA EL JUGO
struct KeyPressed
{
	const static int ANY = -1;
	
	const static int KEY_L = 0; //DERECHA
	const static int KEY_K = 1; //ROTAR
	const static int KEY_J = 2; //IZQUIERDA
	const static int KEY_H = 3; //MANTENER PIEZA
	
	const static int KEY_O = 4; //AVANZAR
	const static int KEY_U = 5;  //RETROCEDER
	
	const static int KEY_ESCAPE = 6; //PAUSA
	const static int KEY_SPACE = 7; //MOVER HASTA ABAJO UNA PIEZA
	
	int currentKey = ANY; // ACTUAL PRESIONADO
	
};




// CONECCION ENTRE BOARD Y LAS TEXTURAS
struct Game
{
	Board board;
	Level level;

	GameGraphic graphic;
	
	State state;
};



Game builGame()
{
	Game game;
	game.board = buildBoard();
	game.level = buildLevel();
	game.graphic = buildGameGraphic();
	
	game.state.currentState = State::PLAY;

	return game;
}




void verifyKeys(Game & game, KeyPressed & key ,float time)
{
	game.graphic.keyTimer += time;
	
	if(game.graphic.keyTimer >= KEY_DELAY)
	{
		game.graphic.keyTimer = 0.0f;
		
		if(key.currentKey == KeyPressed::ANY)
			return;
		
		switch(key.currentKey){
			case KeyPressed::KEY_L:
				moveRight(game.board);
				key.currentKey = KeyPressed::ANY;
				break;
			case KeyPressed::KEY_J:
				moveLeft(game.board);
				key.currentKey = KeyPressed::ANY;
				break;
			case KeyPressed::KEY_K:
				rotate(game.board);
				key.currentKey = KeyPressed::ANY;
				break;
			case KeyPressed::KEY_H:
				holdPiece(game.board);
				key.currentKey = KeyPressed::ANY;
				break;
			case KeyPressed::KEY_SPACE:
				moveToBottom(game.board);
				key.currentKey = KeyPressed::ANY;
				break;
			case KeyPressed::KEY_ESCAPE:
				game.state.currentState = State::PAUSE;
				key.currentKey = KeyPressed::ANY;
				break;
			case KeyPressed::KEY_U:
				goToPrev(game.board);
				game.graphic.updateTimer = 0.0f;
				game.state.currentState = State::REPRODUCE;
				key.currentKey = KeyPressed::ANY;
				break;
			case KeyPressed::KEY_O:
				goToNext(game.board);
				game.graphic.updateTimer = 0.0f;
				game.state.currentState = State::REPRODUCE;
				key.currentKey = KeyPressed::ANY;
				break;	
		}
		
		
	}
}

void verifyButtons(Game & game)
{
	if(isPressTexture(game.graphic.textures , buildPosition(BUTTON_1_X , BUTTON_Y) , "back")){
		goToPrev(game.board);
		game.graphic.updateTimer = 0.0f;
		game.state.currentState = State::REPRODUCE;
		return;
	}
	if(isPressTexture(game.graphic.textures , buildPosition(BUTTON_2_X , BUTTON_Y) , "advance")){
		goToNext(game.board);
		game.graphic.updateTimer = 0.0f;
		game.state.currentState = State::REPRODUCE;
		return;
	}
	if(isPressTexture( game.graphic.textures , buildPosition(BUTTON_3_X , BUTTON_Y) , "pause")){		
		game.state.currentState =State::PAUSE;
		return;
	}
	if(isPressTexture(game.graphic.textures , buildPosition(BUTTON_4_X , BUTTON_Y) , "exit")){		
		game.state.currentState = State::MENU;
		return;
	}

}

void updateGame(Game &game, KeyPressed & key ,float time)
{
	
	verifyKeys(game , key , time);
	verifyButtons(game);
	
	if(game.state.currentState == State::PLAY){
		game.graphic.updateTimer += time;
		
		if (game.graphic.updateTimer >= game.level.speed)
		{
			game.graphic.updateTimer -= game.level.speed;
			updateBoard(game.board);
			updateLevel(game.level, getFullRows(game.board));
			
		}
		return;
	}
	if(game.state.currentState == State::PAUSE){
		
		
		//PUASE ACTION
		return;
	}
	if(game.state.currentState == State::REPRODUCE){
		game.graphic.updateTimer += time;
		cleanCellsToHistorical(game.board);
		if(game.graphic.updateTimer >= 4.0f){
			game.state.currentState = State::PLAY;
		}
		return;
	}
	if(game.state.currentState == State::MENU){
		//menu actions
		return;
	}
	
	
}













//DIBUJO DE JUEGO 


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


void drawGame(Game & game)
{
	drawBackground(game);
	drawButtonsBoard(game);
	drawPiecesTextures(game);
	drawLastRow(game);
	drawCurrentPiece(game);
	drawNextPieces(game);
	drawHoldPiece(game);
}
