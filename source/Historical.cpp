#include "../header/Historical.h"


Historical * buildHistoric()
{
	Historical * historic = new Historical;
	historic->tetriPiece = buildDefault();
	historic->next = nullptr;
	historic->prev = nullptr;
	
	historic->pos = 0;
	historic->size = 0;
	return historic;
}

bool isEmptyHistorical(Historical *historic) { return historic == nullptr; }

bool equalPosToSize(Historical *historicSize, Historical *historicPos)
{
	if (historicSize == nullptr || historicPos == nullptr)
		return false;

	return historicSize->size - 1 == historicPos->pos;
}

bool moveToNextHistorical(Historical *&current)
{
	if (current == nullptr || current->next == nullptr)
		return false;

	current = current->next;
	return true;
}

bool moveToPrevHistorial(Historical *&current)
{
	if (current == nullptr || current->prev == nullptr)
		return false;

	current = current->prev;

	return true;
}

void addHistoric(Historical *&historic, TetriPiece tetripiece)
{
	Historical *newHistoric = buildHistoric();
	newHistoric->tetriPiece = tetripiece;

	if (isEmptyHistorical(historic))
	{
		historic = newHistoric;
		historic->size = 1;
		return;
	}

	Historical *current = historic;

	while (moveToNextHistorical(current))
		;

	newHistoric->prev = current;
	current->next = newHistoric;

	// ASIGNACION DE POSICION Y AUMENTO DE TAMANNO;
	newHistoric->pos = historic->size;
	historic->size++;
}

Historical *getLastHistoric(Historical *historic)
{
	if (historic == nullptr)
		return nullptr;

	Historical *current = historic;

	while (moveToNextHistorical(current))
		;

	return current;
}

Historical *getHistorical(Historical *&historic, int pos)
{
	if (isEmptyHistorical(historic) || pos < 0 || pos > historic->size)
		return nullptr;

	if (historic->pos == pos)
		return historic;

	Historical *current = historic;

	while (moveToNextHistorical(current))
	{
		if (current->pos == pos)
			return current;
	}

	return nullptr;
}

void removeHistoricalFrom(Historical *&historic, int pos)
{
	if (historic == nullptr)
		return;

	// GUARDO LA POSICION DEL NODO PREVIO A LOS QUE SE VAN A ELIMINAR
	Historical *save = getHistorical(historic, pos);

	if (save == nullptr)
		return;

	// ELEMENTO A ELIMINAR
	Historical *current = save->next;

	// EVITAMOS QUE EL ULTIMO NODO ANTES DE BORRAR APUNTE A NADA
	save->next = nullptr;

	while (current->next != nullptr)
	{

		Historical *next = current->next;

		delete current;

		current = next;
	}

	// CORREGIMOS EL SIZE GENERAL
	historic->size = pos + 1;
}
