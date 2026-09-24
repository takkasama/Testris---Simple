#pragma once
#include "../Board/TetriPiece.h"

struct HistoricalPiece
{
	TetriPiece tetriPiece;
	
	//indicador de la pocicion del nodo a lo largo de la lisa
	//se hace con el objetivo para recortar la lista en el caso de que se necesite modificar un desde - hasta 
	int pos;

	//manejo del tamanno total de la lista;
	int size;
	
	HistoricalPiece * next , * prev;
};


HistoricalPiece * buildHistoric()
{
	HistoricalPiece * historic = new HistoricalPiece;
	historic->tetriPiece = buildDefault();
	historic->next = nullptr;
	historic->prev = nullptr;
	
	historic->pos = 0;
	historic->size = 0;
	return historic;
}

bool isEmptyHistorical(HistoricalPiece * historic){ return historic == nullptr; }	

bool equalPosToSize(HistoricalPiece * historicSize , HistoricalPiece * historicPos)
{
	if(historicSize == nullptr || historicPos == nullptr)
		return false;
	
	return historicSize->size - 1 == historicPos->pos;
	
}

	
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
		historic->size = 1;
		return;
	}
	
	HistoricalPiece * current = historic;
	
	while(moveToNextHistorical(current));
	
	newHistoric->prev = current;
	current->next = newHistoric;
	
	//ASIGNACION DE POSICION Y AUMENTO DE TAMANNO;
	newHistoric->pos = historic->size;
	historic->size++;
}
	
	
HistoricalPiece * getLastHistoric(HistoricalPiece * historic)
{
	if(historic == nullptr)
		return nullptr;
	
	
	HistoricalPiece * current  = historic;
	
	while(moveToNextHistorical(current));	
	
	return current;
}	
	

HistoricalPiece * getHistoricalPiece(HistoricalPiece *& historic, int pos)
{
	if(isEmptyHistorical(historic) || pos < 0 || pos > historic->size)
		return nullptr;
	
	if(historic->pos == pos)
		return historic;
	
	HistoricalPiece * current = historic;
	
	while(moveToNextHistorical(current)){
		if(current->pos == pos)
			return current;
	}
	
	return nullptr;
}


void removeHistoricalFrom(HistoricalPiece *& historic , int pos)
{
	if(historic == nullptr)
		return;
		
	
	
	//GUARDO LA POSICION DEL NODO PREVIO A LOS QUE SE VAN A ELIMINAR
	HistoricalPiece * save = getHistoricalPiece(historic , pos);

	if(save == nullptr) return;
	
	//ELEMENTO A ELIMINAR
	HistoricalPiece * current = save->next;
	
	//EVITAMOS QUE EL ULTIMO NODO ANTES DE BORRAR APUNTE A NADA
	save->next = nullptr;
	
	while(current->next != nullptr){
		
		HistoricalPiece * next = current->next;
	
		delete current;
		
		current = next; 
	}
	
	//CORREGIMOS EL SIZE GENERAL
	historic->size = pos + 1;
	
}	
	


