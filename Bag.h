#pragma once
#include "TetriPiece.h"

struct Bag
{
	const static int MAX_SIZE = 7;
	TetriPiece tetriPieces[MAX_SIZE];
	int curentPieces;

	Bag *next;
};

Bag generateBag()
{
	Bag bag;
	bag.curentPieces = bag.MAX_SIZE - 1;

	bag.tetriPieces[0] = buildTetriPiece('Z');
	bag.tetriPieces[1] = buildTetriPiece('S');
	bag.tetriPieces[2] = buildTetriPiece('T');
	bag.tetriPieces[3] = buildTetriPiece('I');
	bag.tetriPieces[4] = buildTetriPiece('L');
	bag.tetriPieces[5] = buildTetriPiece('J');
	bag.tetriPieces[6] = buildTetriPiece('O');

	bag.next = nullptr;
	return bag;
}

TetriPiece getTetripieceToBag(Bag &bag)
{
	int randPos = rand() % (bag.curentPieces + 1); // SE RESTA UNO DEBIDO AL TOTAL DECLARADO COMO ACTUAL DE PIEZAS

	TetriPiece save = bag.tetriPieces[randPos];
	bag.tetriPieces[randPos] = bag.tetriPieces[bag.curentPieces];
	bag.tetriPieces[bag.curentPieces] = save;

	bag.curentPieces--;

	return save;
}

bool isEmptyBag(Bag bag) { return bag.curentPieces < 0; }

// ESTA ESTRUCTRA SIRVE PARA LLEVAR EL CONTROL DE LAS BOLSAS DE MODO QUE FUNCIONA COMO UNA COLA
// Y LLEVA LA COLA ACTUAL ACTUALIZANDO ESTA SI ESTA VACIA, DONDE LA ESTRUCTURA NO SE APUNTO A SU SIGUIENTE
// SI NO QUE QUE APUNTA LA COLA DE LA BOLSA, SIRVE COMO UN ENVOLTORIO
struct QueueBag
{
	Bag *currentBag;

	Bag *queue, *top;
};

QueueBag * buildQueueBag()
{
	QueueBag * queueBag;

	queueBag->currentBag = new Bag(generateBag());

	queueBag->queue = nullptr;
	queueBag->top = nullptr;

	return queueBag;
}

void queueCurrentBag(QueueBag *&node)
{

	Bag *current = node->currentBag;
	if (node->top == nullptr)
	{
		node->top = current;
		node->queue = current;
		return;
	}

	node->top->next = current;
	node->top = current;
}

Bag *desqueBag(QueueBag *& node)
{
	if (node->queue == nullptr)
		return nullptr;

	Bag *save = node->queue;
	node->queue = save->next;

	save->next = nullptr;

	if (node->top == nullptr)
		return nullptr;

	return save;
}

void verifyCurrentBag(QueueBag * & node)
{
	if(node == nullptr)
		return;
	
	if (isEmptyBag(*node->currentBag))
		queueCurrentBag(node);	
}


TetriPiece getNextPiece(QueueBag *&  node)
{
	verifyCurrentBag(node);
	
	TetriPiece piece = getTetripieceToBag(*node->currentBag);
	
	return piece;
	
}
