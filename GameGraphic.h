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


const float KEY_DELAY = 0.099f;

//CONSTANTES DE LOS RECUADROS PARA MOSTRAR SIGUIENTE DE LA FICHA
const float NEXT_X = 510.0f;
const float NEXT_1_Y = 210.0f;
const float NEXT_2_Y = 340.0f;
const float NEXT_3_Y = 465.0f;


//CONSTANTES PARA EL ESPACIO DE HOLD_PIECE
const float HOLD_X = 510.0f;
const float HOLD_Y = 640.0f;

struct GameGraphic
{
	float updateTimer;
	
	float keyTimer;
	
	TextureGame *textures;
	
};

void loadTextures(GameGraphic &graphic)
{
	
	addTexture(graphic.textures, "TetriI", true);
	addTexture(graphic.textures, "TetriJ", true);
	addTexture(graphic.textures, "TetriL", true);
	addTexture(graphic.textures, "TetriO", true);
	addTexture(graphic.textures, "TetriS", true);
	addTexture(graphic.textures, "TetriT", true);
	addTexture(graphic.textures, "TetriZ", true);
	addTexture(graphic.textures, "TetriD", true);
	
	
	addTexture(graphic.textures, "TetriCI", true);
	addTexture(graphic.textures, "TetriCJ", true);
	addTexture(graphic.textures, "TetriCL", true);
	addTexture(graphic.textures, "TetriCO", true);
	addTexture(graphic.textures, "TetriCS", true);
	addTexture(graphic.textures, "TetriCT", true);
	addTexture(graphic.textures, "TetriCZ", true);
	
	addTexture(graphic.textures, "start", false);
	addTexture(graphic.textures, "pause", false);
	addTexture(graphic.textures, "retry", false);
	addTexture(graphic.textures, "menu", false);
	
	addTexture(graphic.textures, "topRecords", false);
	addTexture(graphic.textures, "info", false);
	
	addTexture(graphic.textures, "back", false);
	addTexture(graphic.textures, "advance", false);
	
	
	addTexture(graphic.textures, "exit", false);
	addTexture(graphic.textures, "settings", false);
	
	addTexture(graphic.textures, "delete", false);
	addTexture(graphic.textures, "close", false);
	
	addTexture(graphic.textures, "board", false);
	addTexture(graphic.textures, "background", false);
	
	addTexture(graphic.textures, "board", false);
	addTexture(graphic.textures, "background", false);
	
}


//NOTA : TODOS LOS METODOS QUE SE USARAN PERTENECEN A LA LOGICA DE GAMEGRAPHIC 
// 		PERO ESTOS RECIBIRAN EL PARAMETRO DE GAME UNICAMENTE DEBIDO A QUE GAMEGRPAHIC SERA LA INTEGRACION GRAFICA 
//		DEL GAME POR LO QUE GAME TENDRA A GameGraphic


GameGraphic buildGameGraphic()
{
	GameGraphic graphic;
	graphic.updateTimer = 0.0f;
	graphic.keyTimer = 0.0f;
	
	graphic.textures = nullptr;
	loadTextures(graphic);
	
	return graphic;
}



Position getTexturePosition(int x, int y)
{
	return buildPosition(BOARD_X + x * CELL_WIDTH , BOARD_Y + y * CELL_HEIGHT);
}

Position getTexturePositionToNextPieces(int numbrePiece)
{
	if(numbrePiece == 0)
		return buildPosition(NEXT_X , NEXT_1_Y);
	
	if(numbrePiece == 1)
		return buildPosition(NEXT_X , NEXT_2_Y);
	
	return buildPosition(NEXT_X , NEXT_3_Y);
}




