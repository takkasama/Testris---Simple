#include "../header/GameGraphic.h"

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
