#pragma once

#include<iostream>
#include "TetriPiece.h"
#include "Board.h"
#include "GameGraphic.h"
#include "Level.h"
#include "Player.h"

using namespace std;


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
	const static int MAX_PLAYERS = 10;
	
	Board board;
	Level level;

	GameGraphic graphic;
	
	Player * players;
	Player currentPlayer;
	
	
	State state;
};

Game builGame();


//VERIFICAINOES Y ACTUALIZACION DEL JUEGO
void verifyKeys(Game & game, KeyPressed & key ,float time);
void verifyButtons(Game & game);
void updateGame(Game &game, KeyPressed & key ,float time);

//DIBUJO DE JUEGO 
void drawPiecesTextures(Game & game);
void drawCurrentPiece(Game & game);
void drawBackground(Game & game);
void drawButtonsBoard(Game & game);
void drawHoldPiece(Game & game);
void drawLastRow(Game & game);
void drawNextPieces(Game & game);
void drawBoardTextSpaces(Game & game);
void drawGame(Game & game);
