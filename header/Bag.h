#pragma once
#include "TetriPiece.h"

struct Bag
{
	const static int MAX_SIZE = 7;
	const static int WAIT_SIZE = 3;
	
	
	//SE USA PARA PODER MOSTAR LOS SIGUIENTES '3' TETRIS
	TetriPiece waitPieces[WAIT_SIZE];
	int currentWaitPiece;
	
	TetriPiece tetriPieces[MAX_SIZE];
	int curentPieces;
	
	Bag *next;
};

bool isEmptyBag(Bag bag);

bool isEmptyWaitPiecesToBag(Bag bag);

TetriPiece getTetripieceToBag(Bag &bag);

TetriPiece getNextPieceBag(Bag & bag);

Bag generateBag();

// ESTA ESTRUCTRA SIRVE PARA LLEVAR EL CONTROL DE LAS BOLSAS DE MODO QUE FUNCIONA COMO UNA COLA
// Y LLEVA LA COLA ACTUAL ACTUALIZANDO ESTA SI ESTA VACIA, DONDE LA ESTRUCTURA NO SE APUNTO A SU SIGUIENTE
// SI NO QUE QUE APUNTA LA COLA DE LA BOLSA, SIRVE COMO UN ENVOLTORIO
struct QueueBag
{
	Bag *currentBag;
	
	Bag *queue, *top;
};

QueueBag * buildQueueBag();

void queueCurrentBag(QueueBag *&node);

Bag *desqueBag(QueueBag *& node);

void verifyCurrentBag(QueueBag *& node);

TetriPiece getNextPiece(QueueBag *&  node);
