#pragma once


//CONSTANTES MODIFICADORAS O DE CONTROL DE JUEGO

// CONSTANTE QUE INCARA CUANTO IRA DISMINUYENDO POR NIVEL
const float SPEED_MODIFIER = 0.007f;// VELOCIDAD BASE
const float INITIAL_SPEED = 1.5f;

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
