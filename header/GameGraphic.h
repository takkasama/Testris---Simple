#pragma once
#include "TextureGame.h"


const float BOARD_X = 59.0f;
const float BOARD_Y = 51.0f;

const float BOARD_WIDTH  = 363.0f;
const float BOARD_HEIGHT = 734.0f;

const int TOTAL_COLUMNS = 10;
const int TOTAL_ROWS = 20;

const float CELL_WIDTH = BOARD_WIDTH / TOTAL_COLUMNS;
const float CELL_HEIGHT = BOARD_HEIGHT / TOTAL_ROWS;

//CONSTANTES PARA BOTONES 
const float BUTTON_Y = 875.0f;
const float BUTTON_1_X = 153.0f;
const float BUTTON_2_X = 265.0f;
const float BUTTON_3_X = 377.0f;
const float BUTTON_4_X = 489.0f;


const float KEY_DELAY = 0.3f;

//CONSTANTES DE LOS RECUADROS PARA MOSTRAR SIGUIENTE DE LA FICHA
const float NEXT_X = 510.0f;
const float NEXT_1_Y = 210.0f;
const float NEXT_2_Y = 340.0f;
const float NEXT_3_Y = 465.0f;


//CONSTANTES PARA EL ESPACIO DE HOLD_PIECE
const float HOLD_X = 510.0f;
const float HOLD_Y = 640.0f;

//CONSTANTES DE LOS ESPACION DE TEXTO DEL BOARD.
const float TEXT_X = 470.0f;
const float TEXT_Y_1 = 55.0F;
const float TEXT_Y_2 = 125.f;


//FONT SIZE DEFUALT PARA EL BOARD
const float FONT_SIZE = 50.0f;




struct GameGraphic
{
	float updateTimer;
	
	float keyTimer;
	
	TextureGame *textures;
};



void loadTextures(GameGraphic & graphic);
GameGraphic buildGameGraphic();

Position getTexturePosition(int x, int y);
Position getTexturePositionToNextPieces(int numbrePiece);



