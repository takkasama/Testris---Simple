#pragma once
#include "TextureGame.h"
#include "Board.h"

// CONSTANTE QUE INCARA CUANTO IRA DISMINUYENDO POR NIVEL
const float SPEED_MODIFIER = 0.007f;

// VELOCIDAD BASE
const float INITIAL_SPEED = 2.0f;

// FORMULA DE CALCULO DE PUNTOS POR FILA EN RELACION AL NIVEL ACTUAL Y LA LA CANTIDAD DE PUNTOS BASE

// PARA CADA MOVIENTO HECHO SIN NECESIDAD DE ELMINAR UNA PIEZA
const int POINTS_NONE = 10;

const int POINTS_SIMPLE = 40;
const int POINTS_DOUBLE = 100;
const int POINTS_TRIPLE = 300;
const int POINTS_TETRIS = 1200;

// CONDICION PARA SUBIR DE NIVEL , LA CUAL SERIA EL NIVEL MULTIPLICADO POR LAS FILAS SI LAS FILAS ACTUALES SON MAYORES A ELLO SE AUMENTA EL NIVEL
const int CONDITION_UPLEVEL = 10;

const float BOARD_X = 59.0f;
const float BOARD_Y = 51.0f;
const float BOARD_WIDTH = 363.0f;
const float BOARD_HEIGHT = 770.0f;

const int TOTAL_COLUMNS = 10;
const int TOTAL_ROWS = 20;

const float CELL_WIDTH = BOARD_WIDTH / TOTAL_COLUMNS;
const float CELL_HEIGHT = BOARD_HEIGHT / TOTAL_ROWS;

struct Position
{
	float x;
	float y;
};

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

	addTexture(game.textures, "tetriI", true);
	addTexture(game.textures, "tetriJ", true);
	addTexture(game.textures, "tetriL", true);
	addTexture(game.textures, "tetriO", true);
	addTexture(game.textures, "tetriS", true);
	addTexture(game.textures, "tetriT", true);
	addTexture(game.textures, "tetriZ", true);

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
	Position position;

	position.x = BOARD_X + (x * CELL_WIDTH);
	position.y = BOARD_Y + (y * CELL_HEIGHT);

	return position;
}

void drawPiecesTextures(Game &game)
{
	Row *currentRow = game.board.top;
	int y = 0;
	while (currentRow != nullptr)
	{
		for (int x = 0; x < Row::MAX_COLUMNS; x++)
		{
			
			if (!currentRow->cell[x].isSelected)
				continue;
			
			string nameImg = "tetri" + string(1, currentRow->cell[x].type);
			TextureGame *texture = getTexture(game.textures, nameImg);
			
			if (texture != nullptr)
			{
				
				Position pos = getTexturePosition(x, y);
				
				DrawTexture(texture->texture, pos.x, pos.y, WHITE);
			}
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
	string nameImg = "tetri" + string(1, piece.type);

	TextureGame *texture = getTexture(game.textures, nameImg);

	if (texture == nullptr)
		return;

	for (int i = 0; i < TetriPiece::SIZE; i++)
	{
		int x = piece.pieces[i].x;
		int y = piece.pieces[i].y;
	 
		Position pos = getTexturePosition(x, y);
	 
		DrawTexture(texture->texture, pos.x, pos.y, WHITE);
	}
}

void drawBackground(Game &game)
{
}

void updateGame(Game &game)
{
	if (game.updateTimer >= game.level.speed)
	{
		updateBoard(game.board);
		updateLevel(game.level, getFullRows(game.board));
	}
}
