#pragma once
#include "HistoricalPiece.h"
#include "Bag.h"
#include "HoldTetri.h"
// PARA ALMACENAR UNA PIEZA Y REPRESENTAR UN ESPACIO DE COLUMNA
struct Cell
{
	// SE DEJA EL TIPO UNICAMENTE DEBIDO A QUE UNA CELDA NO DEBE CONTENER LA PIEZA COMPLETA
	// DE MODO QUE LA RESPONSABILIDAD DE MANEJO DE POCIONES Y EL HISTORIAL DE ESTE SE ENCARGAR LA
	// LISTA DE REPRODUCCION
	char type;

	// INDICADOR DE SI CELDA ESTA SELECIONADAS
	bool isSelected;
};
Cell buildCell()
{
	Cell cell;
	cell.type = 'D';
	cell.isSelected = false;

	return cell;
}

void updateCell(Cell &cell, char type, bool isSelected)
{
	cell.isSelected = isSelected;
	cell.type = type;
}


void cleanCell(Cell &cell)
{
	cell.isSelected = false;
	cell.type = 'D';
}

// LISTA DOBLEMENTE ENLAZADA REQUERIDA PARA LA CONSTRUCCION DEL TABLERO
struct Row
{
	const static int MAX_COLUMNS = 10;
	Cell cell[MAX_COLUMNS];

	Row *next, *prev;
};

bool isEmptyRow(Row *row) { return row == nullptr; }

Row *buildRow()
{

	Row *row = new Row;
	row->next = nullptr;
	row->prev = nullptr;

	for (int i = 0; i < row->MAX_COLUMNS; i++)
		row->cell[i] = buildCell();

	return row;
}
bool isSelectedCell(Row *row, int posX)
{
	if (isEmptyRow(row))
		return false;

	return row->cell[posX].isSelected;
}

bool isFillRow(Row *row, int pos)
{

	if (isEmptyRow(row))
		return false;

	if (pos == 0)
		return true;
	
	return row->cell[pos].isSelected && isFillRow(row, 0);
}

void addRow(Row *&top, Row *&botton, Row *newRow)
{
	if (isEmptyRow(top))
	{
		top = newRow;
		botton = newRow;
		return;
	}

	newRow->next = top;
	top->prev = newRow;
	top = newRow;
}




// ORGANIZACION DE LAS FILAS ADEMAS DE ACCESO A LA PARTE INFERIOR PARA LA LECTURA DE LA VERFICACIONES DE ESTADO DE LAS FILAS
//ELEMENTO CENTRAL DE LA LOGICA DE JUEGO	
struct Board
{
	const static int MAX_ROWS = 20;	
	
	QueueBag * queueBag;
	
	
	HoldTetri * hold;
	
	//no se puede intercambiar si el tipo anterior es igual al nuevo
	TetriPiece currentPiece;
	
	bool isActiveCurrentPiece;
	HistoricalPiece * historical;
	
	Row *top, *bottom;
};

Board buildBoard()
{
	Board board;
	board.top = nullptr;
	board.bottom = nullptr;
	
	
	//SE CAMBIA EL VALOR UNA VEZ EMPIEZA EL JUEGO
	//ESTO SERVIRA PARA LLEVAR EL CONTROL DE LA PIEZA ACTUAL
	board.isActiveCurrentPiece = false;
	
	//GESTORES DE PIEZAS
	board.queueBag =  buildQueueBag();
	board.hold = buildHoldTetri();
	
	board.historical = nullptr;
	board.currentPiece = getNextPiece(board.queueBag);
	
	
	
	for (int i = 0; i < board.MAX_ROWS; i++)
		addRow(board.top, board.bottom, buildRow());

	return board;
}

void cleanRow(Board & board , Row *&row)
{
	if (!isFillRow(row, 0))
		return;
	
	Row * save  = row;
	if(save->next != nullptr)
		save ->next->prev = save->prev;
	if(save->prev != nullptr)
		save ->prev->next = save->next;
	
	delete save;
	
	Row * newRow = buildRow();
	newRow->next = board.top;
	board.top = newRow;
	
	
}

Row * getRow(Board & board , int y)
{
	if(y < 0 || y >= Board::MAX_ROWS)		
		return nullptr;
	
	Row * current = board.top;
	
	for(int i = 0; i < y && current != nullptr; i++)
		current = current->next;
	
	return current;
}

bool isUsedCell(Board & board, int x , int y)
{
	if(x < 0 || x >= Row::MAX_COLUMNS)
		return true;
	
	if(y < 0 || y >= Board::MAX_ROWS)
		return true;
	
	Row * row = getRow(board , y);
	
	if(row == nullptr)
		return true;
	
	return row->cell[x].isSelected;
}


int getFullRows(Board & board)
{
	
	Row * current = board.bottom;
	
	int sumFullRows = 0;
	while(current->prev != nullptr){
		
		//POR SI SE LLEGA A ELIMNIAR UNA FILA GUARDAR EL PREVIO DE ESTE
		Row * prev = current->prev;
		
		if(isFillRow(current, 0)){
			cleanRow(board, current);
			sumFullRows++;
		}
		current = prev;
	}
	
	
	return sumFullRows;
	//calculo de los puntos er relacion a las filas elimanas en un movimiento 
}
	
//SE USARA POR CADA CICLO DE JUEGO PARA ACTUALIZAR LA POS DE LAS PIEZAS
bool canMoveDown(Board & board)
{
	TetriPiece piece = board.currentPiece;
	for(int i = 0; i < TetriPiece::SIZE; i++){
		int x = piece.pieces[i].x;
		int y = piece.pieces[i].y + 1;
		
		if(isUsedCell(board , x, y))
			return false;
		
	}
	
	return true;
}

bool canMoveRight(Board & board)
{
	TetriPiece piece = board.currentPiece;
	
	for(int i = 0; i < TetriPiece::SIZE; i++){
		int x = piece.pieces[i].x + 1;
		int y = piece.pieces[i].y;
		
		if(isUsedCell(board , x, y))
			return false;
		
	}
	return true;
}
	


bool canMoveLeft(Board & board)
{
	TetriPiece piece = board.currentPiece;
	
	for(int i = 0; i < TetriPiece::SIZE; i++){
		int x = piece.pieces[i].x - 1;
		int y = piece.pieces[i].y;
		
		if(isUsedCell(board , x, y))
			return false;
			
	}
	return  true;
}	
	
bool canRotate(Board & board)
{
	TetriPiece piece = board.currentPiece;
	
	int auxX = piece.pieces[1].x;
	int auxY = piece.pieces[1].y;
 	
	for(int i = 0; i < TetriPiece::SIZE; i++){
		
		int x = auxX + (piece.pieces[i].y - auxY);
		int y = auxY - (piece.pieces[i].x - auxX);
		
		if(isUsedCell(board, x, y))
			return false;
	}
	
	return true;
}

void lockCurrentPiece(Board & board)
{
	TetriPiece piece = board.currentPiece;
	
	for(int i =0 ; i < TetriPiece::SIZE; i++)
	{
		int x = piece.pieces[i].x;
		int y = piece.pieces[i].y;
		
		updateCell(getRow(board, y)->cell[x] , piece.type , true);
		
	}
	
	
}

void loadNextPiece(Board & board)
{
	TetriPiece nextPiece = getNextPiece(board.queueBag);
	
	addHistoric(board.historical , board.currentPiece);
	addHistoric(board.historical , nextPiece); 
	
	board.currentPiece = nextPiece;

}


void holdPiece(Board & board)
{
	
	pushHold(board.hold, board.currentPiece);
	loadNextPiece(board);
}


void updateBoard(Board & board)
{
	if(canMoveDown(board)){
		movePieceDown(board.currentPiece);
		addHistoric(board.historical , board.currentPiece);		
		return;
	}
	
	lockCurrentPiece(board);

	getFullRows(board);
	
	
	loadNextPiece(board);

	
}
void moveRight(Board & board)
{
	if(!canMoveRight(board))
		return;

	movePieceRight(board.currentPiece);
	
	
	addHistoric(board.historical , board.currentPiece);
}
	
void moveLeft(Board & board)
{
	if(!canMoveLeft(board))
		return;
	
	movePieceLeft(board.currentPiece);
	
	
	addHistoric(board.historical , board.currentPiece);
}

void rotate(Board & board)
{
	if(!canRotate(board))
		return;
	
	rotatePiece(board.currentPiece);
	
	addHistoric(board.historical , board.currentPiece);
}




	
void moveToBottom(Board & board)
{
	while(canMoveDown(board)){
		for(int i = 0; i < TetriPiece::SIZE; i++)
			board.currentPiece.pieces[i].y++;
	}
		
	updateBoard(board);
}

	
	
	
	
	
	
	
