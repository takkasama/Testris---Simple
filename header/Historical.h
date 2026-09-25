#pragma once
#include "TetriPiece.h"

struct Historical
{
	TetriPiece tetriPiece;
	
	//indicador de la pocicion del nodo a lo largo de la lisa
	//se hace con el objetivo para recortar la lista en el caso de que se necesite modificar un desde - hasta 
	int pos;

	//manejo del tamanno total de la lista;
	int size;
	
	Historical * next , * prev;
};


Historical * buildHistoric();

bool isEmptyHistorical(Historical * historic);

bool equalPosToSize(Historical * historicSize , Historical * historicPos);
	
bool moveToNextHistorical(Historical *& current);

bool moveToPrevHistorial(Historical *& current);

void addHistoric(Historical *& historic ,TetriPiece tetripiece);
	
Historical * getLastHistoric(Historical * historic);
	
Historical * getHistorical(Historical *& historic, int pos);
	
void removeHistoricalFrom(Historical *& historic , int pos);
	



