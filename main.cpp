#include <iostream>
#include <string>
#include <ctime>

#include "raygui.h"
#include "raylib.h"

#include "TetriPiece.h"

using namespace std;


const string PATH_PIECES = "Assets/TetriPieces";
const string PATH_BUTTONS = "Assets/Buttons";


struct NodeTetri
{
	TetriPiece tetriPiece;
	NodeTetri * next;
	NodeTetri * prev;
};

NodeTetri * buildNodeTetri(TetriPiece tetriPiece){
	NodeTetri * node;
	node->tetriPiece = tetriPiece;
	node->next = nullptr;
	node->prev = nullptr;
	return node;
}


struct Bag{
	const static int MAX_SIZE = 7;
	TetriPiece tetriPieces[MAX_SIZE];
	int curentPieces;	
	
};


Bag generateBag(){
	Bag bag;
	bag.curentPieces = 6;
	
	bag.tetriPieces[0] = buildTetriPiece('Z'); 
	bag.tetriPieces[1] = buildTetriPiece('S'); 
	bag.tetriPieces[2] = buildTetriPiece('T'); 
	bag.tetriPieces[3] = buildTetriPiece('I'); 
	bag.tetriPieces[4] = buildTetriPiece('L'); 
	bag.tetriPieces[5] = buildTetriPiece('J'); 
	bag.tetriPieces[6] = buildTetriPiece('O'); 	
	
	return bag;
}
	
TetriPiece getTetripieceToBag(Bag bag)
{
	srand(static_cast<unsigned int>(time(0)));
	
	int randPos = rand() % bag.curentPieces; //SE RESTA UNO DEBIDO AL TOTAL DECLARADO COMO ACTUAL DE PIEZAS

	TetriPiece save = bag.tetriPieces[randPos];
	bag.tetriPieces[randPos] = bag.tetriPieces[bag.curentPieces]; 
	bag.tetriPieces[bag.curentPieces] = save;
	
	bag.curentPieces--;
	
	return save;
}

bool isEmptyBag(Bag bag){ return bag.curentPieces < 0; }



Bag buildBag(){
	Bag bag;
	
	bag.size = 0;
	
	return bag;
}
	
struct 
	
	

struct Board
{	
	NodeTetri *row;

	Board *next;
	Board *prev;
};


int main()
{

	return 0;
}


