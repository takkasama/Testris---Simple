#pragma once
#include "TetriPiece.h"

struct HistoricalPiece
{
	TetriPiece tetriPiece;
	
	int size;
	
	HistoricalPiece * next , * prev;
};


HistoricalPiece * buildHistoric()
{
	HistoricalPiece * historic = new HistoricalPiece;
	historic->tetriPiece = buildDefault();
	historic->next = nullptr;
	historic->prev = nullptr;
	
	historic->size = 0;
	
	return historic;
}

bool isEmptyHistorical(HistoricalPiece * historic){ return historic == nullptr; }	

	
bool moveToNextHistorical(HistoricalPiece *& current){ 
	if(current == nullptr || current->next == nullptr) 
		return false;
	
	current = current->next;
	return true;
}
	
bool moveToPrevHistorial(HistoricalPiece *& current){
	if(current == nullptr || current->prev == nullptr) 
		return false;
	
	current = current->prev;
	
	return true;
}	
	
	
	
void addHistoric(HistoricalPiece *& historic ,TetriPiece tetripiece){
	HistoricalPiece * newHistoric = buildHistoric();
	newHistoric->tetriPiece = tetripiece;
	
	if(isEmptyHistorical(historic)){		
		historic = newHistoric;
		historic->size++;
		return;
	}
	
	HistoricalPiece * current = historic;
	
	while(current->next != nullptr)
		moveToNextHistorical(current);
	
	newHistoric->prev = current;
	current->next = newHistoric;
	historic->size++;
}
	
	
HistoricalPiece * getLastHistoric(HistoricalPiece * historic)
{
	if(historic == nullptr)
		return nullptr;
	
	
	HistoricalPiece * current  = historic;
	
	while(current->next != nullptr)
		current = current->next;
	
	
	
	return current;
}	
	

TetriPiece  removeLastHistoric(HistoricalPiece *& historic){
	
	if(isEmptyHistorical(historic))
		return buildDefault();
	
	
	HistoricalPiece * saveToRemove = historic;
	TetriPiece save  = historic->tetriPiece;
	
	historic = historic->next;
	historic->prev = nullptr;
	saveToRemove->next = nullptr;
	
	delete saveToRemove;
	
	return save;
	
}
	

TetriPiece getHistoricalPiece(HistoricalPiece *& historic, char type)
{
	if(!isEmptyHistorical(historic))
		return buildDefault();
	
	if(historic->tetriPiece.type == type)
		return historic->tetriPiece;
	
	HistoricalPiece * current = historic;
	
	while(!isEmptyHistorical(current->next) && current->next->tetriPiece.type != type)
		moveToNextHistorical(current);
	
	if(isEmptyHistorical(current->next) || current->next->tetriPiece.type != type)
		return buildDefault();
	
	return current->next->tetriPiece;
	
}


	
	


