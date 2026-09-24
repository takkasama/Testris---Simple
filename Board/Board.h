#pragma once
#include "HistoricalPiece.h"
#include "Bag.h"
#include "HoldTetri.h"
#include "Row.h"

// ORGANIZACION DE LAS FILAS ADEMAS DE ACCESO A LA PARTE INFERIOR PARA LA LECTURA DE LA VERFICACIONES DE ESTADO DE LAS FILAS
//ELEMENTO CENTRAL DE LA LOGICA DE JUEGO	



struct Board
{
	const static int MAX_ROWS = 20;	
		
	QueueBag * queueBag;
	HoldTetri * hold;
	
	TetriPiece currentPiece;
	
	HistoricalPiece * historical;
	HistoricalPiece * currentHistorical;
	
	Row *top, *bottom;
};

Board buildBoard()
{
	Board board;
	board.top = nullptr;
	board.bottom = nullptr;
	
	
	//GESTORES DE PIEZAS
	board.queueBag =  buildQueueBag();
	board.hold = buildHoldTetri();
	
	board.currentPiece = getNextPiece(board.queueBag);
		
	board.historical = nullptr;
	board.currentHistorical = nullptr;
	
	for (int i = 0; i < board.MAX_ROWS; i++)
		addRow(board.top, board.bottom, buildRow());

	return board;
}

void cleanRow(Board & board , Row *&row)
{		
	if(row->next != nullptr)
		row->next->prev = row->prev;
	else 
		board.bottom = row->prev;
	
	
	if(row->prev != nullptr)
		row->prev->next = row->next;
	else 
		board.top = row->next;
	
	row->next = nullptr;
	row->prev = nullptr;
	
	delete row;
		Row * newRow = buildRow();

	addRow(board.top , board.bottom , newRow);
	
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
	
	Row *current = board.bottom;
	
	int sumFullRows = 0;
	
	while(current != nullptr)
	{
		Row *prev = current->prev;
		
		if(isFillRow(current)){
			cleanRow(board, current);
			sumFullRows++;
		}
		
		current = prev;
	}
	
	return sumFullRows;
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

//CUANDO SE RETROCEDE UN PASO SE HABILITARA UN TIEMPO DE ESPERA PARA AVANZAR Y RETROCEDER EN ESE TIEMPO SI NO SE ENCUENTRA EN LA PARTE FINAL DE LA
//LISTA SE BORRARA TODOS LOS ELEMENTOS SIGUIENTES DEL HISTORICO 


void goToNext(Board & board)
{
	if(board.currentHistorical == nullptr){
		board.currentHistorical = getLastHistoric(board.historical);
		return;
	}
	
	if(moveToNextHistorical(board.currentHistorical))
		board.currentPiece = board.currentHistorical->tetriPiece;
}
	
void goToPrev(Board & board)
{
	if(board.currentHistorical == nullptr)
		board.currentHistorical = getLastHistoric(board.historical);
	
	if(moveToPrevHistorial(board.currentHistorical))
		board.currentPiece = board.currentHistorical->tetriPiece;
}



//METODO DE ACTUALIZACION DE LA LISTA REPRODUCCION 
//LA FUNCION DE ESTA ES SIMPLE, SI EL currentHistorical ES NULO SE ASUME QUE NO ESTA REPRODUCIENDO
//SI NO ES NULO Y SE ASUME QUE SE VA A MODIFICAR LA LISTA DADO QUE SE HIZO UN MOVIMIENTO AJENO A historical
//POR LO QUE SE ELIMINAR TODO LOS ELEMENTOS DE LAS LISTA DESPUES DEL ACTUAL

//EL METODO SE LLAMARA POR CADA MODIFICACION DE LA LOCALIZACION DE LA PIEZA DE MODO QUE 
//QUE SE COLOCARA ANTES DE HACER EL MOVIENTO , PARA LUEGO HACER EL MOVIMIENTO Y COLOCARLO EN EL HISTORIAL MODIFICADO
void updateHistorial(Board & board)
{	
	if(board.currentHistorical == nullptr)
		return;
		
	if(equalPosToSize(board.historical, board.currentHistorical)){
		board.currentHistorical = nullptr;
		return;
	}
	
	removeHistoricalFrom(board.historical , board.currentHistorical->pos);
	board.currentHistorical = nullptr;
}


void loadNextPiece(Board & board)
{
	TetriPiece nextPiece = getNextPiece(board.queueBag);
	
	addHistoric(board.historical , nextPiece); 
	
	board.currentPiece = nextPiece;
	
}


void holdPiece(Board & board)
{
	bool isValid = board.hold->lastPiece != board.currentPiece.type;
	
	if(isValid){
		
		updateHistorial(board);
		
		HoldTetri *  save = popHold(board.hold);
		
		pushHold(board.hold , board.currentPiece);
		
		board.currentPiece = save != nullptr ? save->tetriPiece : getNextPiece(board.queueBag);
		
		addHistoric(board.historical , board.currentPiece);
		
		return;
	}
	
}

void moveRight(Board & board)
{
	if(!canMoveRight(board))
		return;
	
	updateHistorial(board);
	
	movePieceRight(board.currentPiece);
	
	addHistoric(board.historical , board.currentPiece);
}

void moveLeft(Board & board)
{
	if(!canMoveLeft(board))
		return;
	
	updateHistorial(board);
	
	movePieceLeft(board.currentPiece);
	
	addHistoric(board.historical , board.currentPiece);
}

void rotate(Board & board)
{
	if(!canRotate(board))
		return;
	
	updateHistorial(board);
	
	rotatePiece(board.currentPiece);
	
	addHistoric(board.historical , board.currentPiece);
}

void moveDown(Board & board)
{
	if(!canMoveDown(board))
		return;
	
	updateHistorial(board);
	
	movePieceDown(board.currentPiece);
	
	addHistoric(board.historical , board.currentPiece);
}


void updateBoard(Board & board)
{
	if(canMoveDown(board)){
		moveDown(board);
		return;
	}
	
	lockCurrentPiece(board);
	
	getFullRows(board);
	
	loadNextPiece(board);
		
}

//COLOCA LA PIEZA EN LA PARTE BAJA SI NO SE DESEA ESPERAR A QUE BASE EN EL CICLO NORMAL
void moveToBottom(Board & board)
{	
	while(canMoveDown(board))
		moveDown(board);
	
}

void cleanCellsToHistorical(Board & board)
{
	for(int i = 0 ; i < TetriPiece::SIZE ; i++){
		Piece piece = board.currentPiece.pieces[i];
		Row * row = getRow(board, piece.y);
		
		if(row->cell[piece.x].isSelected)
			row->cell[piece.x].isSelected = false;
	}
}



