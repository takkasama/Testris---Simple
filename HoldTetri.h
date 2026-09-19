#pragma once
#include "TetriPiece.h"

struct HoldTetri
{
	TetriPiece tetriPiece;
};

HoldTetri * buildHoldTetri()
{
	HoldTetri * holdTetri;
	holdTetri->tetriPiece = buildDefault();
	
	return holdTetri;
}


//	PUSH CON INDICADOR QUE SI TIENE UN PIEZA DEVULVE UN FALSE PARA INDICAR QUE NO SE PUEDE COLOCAR UN PIEZA
//	las condiciones bajo las cuales no puede guardar la pieza son , ya tiene un pieza o la pieza enviada es DEFAULT
bool pushHold(HoldTetri *&node, TetriPiece tetriPiece)
{	
	if(tetriPiece.type == 'D')
		return false;
	
	
	HoldTetri *newHold = buildHoldTetri();
	newHold->tetriPiece = tetriPiece;

	node = newHold;
	
	return true;
}

HoldTetri * popHold(HoldTetri *& node)
{
	if(node == nullptr)
		return nullptr;
	
	if(node->tetriPiece.type == 'D')
		return nullptr;
	
	HoldTetri * save = node;
	
	node = nullptr;
	
	return save;
	
}

