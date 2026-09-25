#include "../header/Hold.h"


Hold * buildHold()
{
	Hold * hold = new Hold;
	
	hold->tetriPiece = buildDefault();
	hold->next = nullptr;
	hold->lastPiece = 'D';
	
	return hold;
}


//	PUSH CON INDICADOR QUE SI TIENE UN PIEZA DEVULVE UN FALSE PARA INDICAR QUE NO SE PUEDE COLOCAR UN PIEZA
//	las condiciones bajo las cuales no puede guardar la pieza son , ya tiene un pieza o la pieza enviada es DEFAULT
void pushHold(Hold *&node, TetriPiece tetriPiece)
{
	if(node == nullptr)
		return;
	
	if(tetriPiece.type == 'D')
		return;
	
	if(node->next != nullptr)
		return;
	
	Hold *newHold = buildHold();
	
	newHold->tetriPiece = tetriPiece;
	
	node->next = newHold;
	
	resetPosition(node->next->tetriPiece);
	
}

Hold * popHold(Hold *& node)
{
	if(node == nullptr)
		return nullptr;
	
	if(node->next == nullptr)
		return nullptr;
	
	Hold * save = node->next;
	
	node->next = nullptr;
	
	return save;
	
}

