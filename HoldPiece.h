#pragma once
#include "TetriPiece.h"

struct HoldTetri{
	
	TetriPiece tetriPiece;
	
	HoldTetri *top;
};


void pushHold(HoldTetri *& node,TetriPiece tetriPiece){
	
	HoldTetri *newHold = new HoldTetri;
	newHold->tetriPiece = tetriPiece;
	newHold->top = nullptr;
	
	if(node == nullptr)
		node = newHold;
}
	
	TetriPiece* popHold(HoldTetri *& node){
		
		if(node == nullptr)
			return nullptr;
		
		TetriPiece * save = new TetriPiece(node->tetriPiece);
		
		delete node;
		node = nullptr;
		
		return save;
	}
		
