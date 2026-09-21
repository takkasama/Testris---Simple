#pragma once
#include "TextureGame.h"
#include "Board.h"

//CONSTANTES MODIFICADORAS O DE CONTROL DE JUEGO

// CONSTANTE QUE INCARA CUANTO IRA DISMINUYENDO POR NIVEL
const float SPEED_MODIFIER = 0.007f;// VELOCIDAD BASE
const float INITIAL_SPEED = 2.0f;

// FORMULA DE CALCULO DE PUNTOS POR FILA EN RELACION AL NIVEL ACTUAL Y LA LA CANTIDAD DE PUNTOS BASE
// PARA CADA MOVIENTO HECHO SIN NECESIDAD DE ELMINAR UNA PIEZA
const int POINTS_NONE = 10;

const int POINTS_SIMPLE = 40;
const int POINTS_DOUBLE = 100;
const int POINTS_TRIPLE = 300;
const int POINTS_TETRIS = 1200;


// CONTANTES EL BOARD Y LOS TETRIS
// CONDICION PARA SUBIR DE NIVEL , LA CUAL SERIA EL NIVEL MULTIPLICADO POR LAS FILAS SI LAS FILAS ACTUALES SON MAYORES A ELLO SE AUMENTA EL NIVEL
const int CONDITION_UPLEVEL = 10;

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



struct Level
{
	int currentLevel;

	int currentRows;
	int points;
	float speed;
};

Level buildLevel()
{
	Level level;
	level.currentLevel = 1;

	level.currentRows = 0;

	level.points = 0;
	level.speed = INITIAL_SPEED;

	return level;
}

void updateLevel(Level &level, int rows)
{
	level.currentRows += rows;

	if (level.currentRows >= level.currentLevel * CONDITION_UPLEVEL)
	{
		level.currentLevel++;
		level.speed = INITIAL_SPEED - ((level.currentLevel - 1) * SPEED_MODIFIER);
	}

	switch (rows)
	{
	case 0:
		level.points += POINTS_NONE;
		break;
	case 1:
		level.points += POINTS_SIMPLE;
		break;
	case 2:
		level.points += POINTS_DOUBLE;
		break;
	case 3:
		level.points += POINTS_TRIPLE;
		break;
	default:
		level.points += POINTS_TETRIS;
		break;
	}
}

// CONECCION ENTRE BOARD Y LAS TEXTURAS

struct Game
{
	TextureGame *textures;

	Board board;

	Level level;
	
	float updateTimer;

	// PARA EL MANEJO DE LAS PERSITENCIA LOCAL EL GUARDADO DE PUNTOS POR JUEGADOR
	// Player player;
};

void loadTextures(Game &game)
{

	addTexture(game.textures, "TetriI", true);
	addTexture(game.textures, "TetriJ", true);
	addTexture(game.textures, "TetriL", true);
	addTexture(game.textures, "TetriO", true);
	addTexture(game.textures, "TetriS", true);
	addTexture(game.textures, "TetriT", true);
	addTexture(game.textures, "TetriZ", true);

	addTexture(game.textures, "start", false);
	addTexture(game.textures, "pause", false);
	addTexture(game.textures, "retry", false);
	addTexture(game.textures, "menu", false);

	addTexture(game.textures, "topRecords", false);
	addTexture(game.textures, "info", false);

	addTexture(game.textures, "exit", false);
	addTexture(game.textures, "settings", false);

	addTexture(game.textures, "delete", false);
	addTexture(game.textures, "close", false);

	addTexture(game.textures, "board", false);
	addTexture(game.textures, "background", false);

	addTexture(game.textures, "board", false);
	addTexture(game.textures, "background", false);
}

Game builGame()
{
	Game game;
	game.board = buildBoard();
	game.level = buildLevel();

	game.updateTimer = 0.0f;
	
	game.textures = nullptr;
	loadTextures(game);

	return game;
}

Position getTexturePosition(int x, int y)
{
	 return buildPosition(BOARD_X + x * CELL_WIDTH , BOARD_Y + y * CELL_HEIGHT);
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
			drawTexture(game.textures, nameImg , pos);
			
		}
		y++;
		currentRow = currentRow->next;
	}
}

void drawCurrentPiece(Game &game)
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
	 
		drawTexture(game.textures , nameImg , pos);
	}
}



void drawBackground(Game &game)
{
	
	Position pos = buildPosition(0.0f , 0.0f);
	drawTexture(game.textures , "board" , pos);
	
}

void drawButtonsBoard(Game & game)
{	
	drawTexture(game.textures, "back" ,buildPosition(BUTTON_1_X, BUTTON_Y));
	drawTexture(game.textures, "advance" ,buildPosition(BUTTON_2_X, BUTTON_Y));
	drawTexture(game.textures, "pause" ,buildPosition(BUTTON_3_X, BUTTON_Y));
	drawTexture(game.textures, "retry" ,buildPosition(BUTTON_4_X, BUTTON_Y));
}


void updateGame(Game &game, float deltaTime)
{
	
	game.updateTimer += deltaTime;
	
	if (game.updateTimer >= game.level.speed)
	{
		
		game.updateTimer -= game.level.speed;
		updateBoard(game.board);
		updateLevel(game.level, getFullRows(game.board));
	}
}
