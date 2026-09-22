#pragma once

struct HoldTetri
{
	TetriPiece tetriPiece;
	char lastPiece;
	
	HoldTetri * next;
};

HoldTetri * buildHoldTetri()
{
	HoldTetri * holdTetri = new HoldTetri;
	
	holdTetri->tetriPiece = buildDefault();
	holdTetri->next = nullptr;
	holdTetri->lastPiece = 'D';
	
	return holdTetri;
}


//	PUSH CON INDICADOR QUE SI TIENE UN PIEZA DEVULVE UN FALSE PARA INDICAR QUE NO SE PUEDE COLOCAR UN PIEZA
//	las condiciones bajo las cuales no puede guardar la pieza son , ya tiene un pieza o la pieza enviada es DEFAULT
void pushHold(HoldTetri *&node, TetriPiece tetriPiece)
{
	if(node == nullptr)
		return;
	
	if(tetriPiece.type == 'D')
		return;
	
	if(node->next != nullptr)
		return;
	
	HoldTetri *newHold = buildHoldTetri();
	
	newHold->tetriPiece = tetriPiece;
	
	node->next = newHold;
}

HoldTetri * popHold(HoldTetri *& node)
{
	if(node == nullptr)
		return nullptr;
	
	if(node->next == nullptr)
		return nullptr;
	
	HoldTetri * save = node->next;
	
	node->next = nullptr;

	return save;
	
}

