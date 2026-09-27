#include "../header/Level.h"

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
	if(rows == 0) return;
	
	level.currentRows += rows;
	
	switch (rows)
	{
	case -1:
		level.points -= POINTS_TETRIS;
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
	case 4:
		level.points += POINTS_TETRIS;
		break;
	}
}

void updateSpeed(Level & level)
{
	level.speed = INITIAL_SPEED - ((level.currentLevel - 1) * SPEED_MODIFIER);

}
