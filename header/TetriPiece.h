#pragma once
struct Piece
{
	int x;
	int y;
};

struct TetriPiece
{

	const static int SIZE = 4;
	Piece pieces[SIZE];

	// TENDRA LOS VALORES BASE DE S - Z - I - 0 - J - L - T  ADEMAS DE LOS VALORES DE D(DEFAULT) y B(BOM-SPECIAL)
	char type;
};

Piece buildPiece(int x, int y);

//MOVIMIENTO DE LA PIEZA
void rotatePiece(TetriPiece &tetriPiece);
void movePieceRight(TetriPiece &tetriPiece);
void movePieceLeft(TetriPiece &tetriPiece);
void movePieceDown(TetriPiece &tetriPiece);
void movePIeceUp(TetriPiece &tetriPiece);


//CONTRUCCINO DE PIEZAS 
TetriPiece buildZ();
TetriPiece buildI();
TetriPiece buildS();
TetriPiece buildT();
TetriPiece buildL();
TetriPiece buildJ();
TetriPiece buildO();
TetriPiece buildDefault();
TetriPiece buildBomb();
	
//RESET DE LA POSICION DE LA PIEZA A LA INICIAL PARA EL HOLD
void resetPosition(TetriPiece &tetriPiece);
