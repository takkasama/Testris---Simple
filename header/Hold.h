#pragma once

#include "TetriPiece.h"

struct Hold
{
	TetriPiece tetriPiece;
	char lastPiece;
	
	Hold * next;
};
Hold * buildHold();


//	PUSH CON INDICADOR QUE SI TIENE UN PIEZA DEVULVE UN FALSE PARA INDICAR QUE NO SE PUEDE COLOCAR UN PIEZA
//	las condiciones bajo las cuales no puede guardar la pieza son , ya tiene un pieza o la pieza enviada es DEFAULT
void pushHold(Hold *&node, TetriPiece tetriPiece);
Hold * popHold(Hold *& node);
