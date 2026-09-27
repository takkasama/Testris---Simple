#pragma once

#include<iostream>
#include "TetriPiece.h"
#include "Board.h"
#include "GameGraphic.h"
#include "Level.h"
#include "Player.h"
#include "State.h"
#include "Menu.h"
#include "Event.h"

using namespace std;

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
	Player currentPlayer;
	State state;
	
	
	//LOS EVENTOS LOS MANEJA GAME DEBIDO A QUE SE MANEJAN EN VELOCIDAD DE CAIDA QUE
	//LOS TIENE EL GAME Y LA GENERACION DE PIEZAS QUE LOS TIENE EL BOARD,
	//POR LO QUE MANEJARA DE ARRIBA A ABAJO
	EventQueue * eventQueue;
	
	Menu menu;
};

Game builGame();
void resetGame(Game & game);

void reproduceGame(Game & game);

//VERIFICAINOES Y ACTUALIZACION DEL JUEGO
void verifyKeys(Game & game, KeyPressed & key ,float time);
void verifyButtonsBoard(Game & game);

void verifyButtonsPause(Game & game);
void verifyButtonsGameOver(Game & game);
void verifyEvents(Game & game);


void updateGame(Game &game, KeyPressed & key ,float time);


void drawPause(Game & game);
void drawGameOver(Game & game);	

//DIBUJO DE JUEGO 
void drawPiecesTextures(Game & game);
void drawCurrentPiece(Game & game);
void drawBackground(Game & game);
void drawHoldPiece(Game & game);
void drawNextPieces(Game & game);

void drawGame(Game & game);


