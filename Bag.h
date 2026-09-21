#pragma once

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



bool isEmptyBag(Bag bag) { return bag.curentPieces < 0; }

bool isEmptyWaitPiecesToBag(Bag bag) { return bag.currentWaitPiece < 0; }


TetriPiece getTetripieceToBag(Bag &bag)
{
	int randPos = rand() % (bag.curentPieces + 1); // SE RESTA UNO DEBIDO AL TOTAL DECLARADO COMO ACTUAL DE PIEZAS
	
	TetriPiece save = bag.tetriPieces[randPos];
	bag.tetriPieces[randPos] = bag.tetriPieces[bag.curentPieces];
	bag.tetriPieces[bag.curentPieces] = save;
	
	bag.curentPieces--;
	
	return save;
}

TetriPiece getNextPieceBag(Bag & bag)
{
	if(isEmptyWaitPiecesToBag(bag))
		return buildDefault();
	
	TetriPiece save  = bag.waitPieces[0];
	bag.waitPieces[0] = bag.waitPieces[1];
	bag.waitPieces[1] = bag.waitPieces[2];
	
	if(!isEmptyBag(bag))
		bag.waitPieces[2] = getTetripieceToBag(bag);
	else{
		bag.waitPieces[2] = buildDefault();
		bag.currentWaitPiece--;
	}
	
	return save;	
	
}



Bag generateBag()
{
	Bag bag;
	bag.curentPieces = bag.MAX_SIZE - 1;
	bag.currentWaitPiece = bag.WAIT_SIZE - 1;
	
	bag.tetriPieces[0] = buildZ();
	bag.tetriPieces[1] = buildS();
	bag.tetriPieces[2] = buildT();
	bag.tetriPieces[3] = buildI();
	bag.tetriPieces[4] = buildL();
	bag.tetriPieces[5] = buildJ();
	bag.tetriPieces[6] = buildO();
	
	bag.waitPieces[0] = getTetripieceToBag(bag);
	bag.waitPieces[1] = getTetripieceToBag(bag);
	bag.waitPieces[2] = getTetripieceToBag(bag);
	
	bag.next = nullptr;
	return bag;
}
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
	QueueBag * queueBag = new QueueBag;

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
		
		node->currentBag = nullptr;
		return;
	}

	node->top->next = current;
	node->top = current;
	
	node->currentBag = nullptr;
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

void verifyCurrentBag(QueueBag *& node)
{
	if(node == nullptr)
		return;
	
	if (isEmptyWaitPiecesToBag(*node->currentBag) &&isEmptyBag(*node->currentBag)){
		queueCurrentBag(node);	
		node->currentBag = new Bag(generateBag());
	}
}


TetriPiece getNextPiece(QueueBag *&  node)
{
	verifyCurrentBag(node);
	
	TetriPiece piece = getNextPieceBag(*node->currentBag);
	
	return piece;
	
}
