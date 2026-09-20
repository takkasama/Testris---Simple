#pragma once
#include "TetriPiece.h"

struct HistoricalPiece
{
	TetriPiece tetriPiece;
	
	
	HistoricalPiece * next , * prev;
};


HistoricalPiece * buildHistoric()
{
	HistoricalPiece * historic = new HistoricalPiece;
	historic->tetriPiece = buildDefault();
	historic->next = nullptr;
	historic->prev = nullptr;
	return historic;
}


void addHistoric(HistoricalPiece *& historic ,TetriPiece tetripiece){
	HistoricalPiece * newHistoric = buildHistoric();
	
	if(historic == nullptr){		
		historic = nullptr;
		return;
	}
	
	newHistoric->next = historic;
	historic->next->prev = newHistoric;
	historic = newHistoric;
}
	
	
TetriPiece  removeFirstHistoric(HistoricalPiece *& historic){
	
	if(historic == nullptr)
		return buildDefault();
	
	
	HistoricalPiece * saveToRemove = historic;
	TetriPiece save  = historic->tetriPiece;
	
	historic = historic->next;
	historic->prev = nullptr;
	saveToRemove->next = nullptr;
	
	delete saveToRemove;
	
	return save;
	
}
		
		
