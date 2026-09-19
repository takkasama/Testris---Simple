#pragma once

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

bool isFillRow(Row *row, int totalCells)
{

	if (isEmptyRow(row))
		return false;

	if (totalCells == 0)
		return row->cell[totalCells].isSelected;
	return row->cell[totalCells - 1].isSelected && isFillRow(row, totalCells - 1);
}

void addRow(Row *&top, Row *&botton, Row *newRow)
{
	if (isEmptyRow(top))
	{
		top = newRow;
		botton = newRow;
	}

	newRow->next = top;
	top->prev = newRow;
	top = newRow;

	Row *current = top;

	while (current->next != nullptr)
		current = current->next;

	botton = current;
}

void cleanRow(Row *&row)
{
	if (isFillRow(row, row->MAX_COLUMNS))
		for (int i = 0; i < row->MAX_COLUMNS; i++)
			cleanCell(row->cell[i]);
}


// ORGANIZACION DE LAS FILAS ADEMAS DE ACCESO A LA PARTE INFERIOR PARA LA LECTURA DE LA VERFICACIONES DE ESTADO DE LAS FILAS
struct Board
{
	const static int MAX_ROWS = 20;	
	
	TetriPiece currentPiece;
	bool isActiveCurrentPiece;
	
	Row *top, *bottom;
};

Board buildBoard()
{
	Board board;
	board.top = nullptr;
	board.bottom = nullptr;
	
	
	//SE CAMBIA EL VALOR UNA VEZ EMPIEZA EL JUEGO
	//ESTO SERVIRA PARA LLEVAR EL CONTROL DE LA PIEZA ACTUAL
	board.currentPiece = buildDefault();
	board.isActiveCurrentPiece = false;

	for (int i = 0; i < board.MAX_ROWS; i++)
		addRow(board.top, board.bottom, buildRow());

	return board;
}

void verifyBoard(Board & board){
	
	Row * current = board.bottom;
	
	int sumFillRows = 0;
	while(current->prev != nullptr){
		if(isFillRow(current)){
			cleanRow();
			sumFillRows++;
		}
	}
	
	//calculo de los puntos er relacion a las filas elimanas en un movimiento 
}
	
	
bool verifyPosToCurrentPiece(Board & board)
{
	Row * currentRow = board.top;
	TetriPiece currentPiece = board.currentPiece;
	for(int i = 0; i < Board::MAX_ROWS && !board.isActiveCurrentPiece; i++){
		
		for(int j = 0; j < TetriPiece::SIZE && !board.isActiveCurrentPiece; j++){
			if(currentRow->cell[currentPiece.pieces[j]].isSelected){
				board.isActiveCurrentPiece = true;
				
				//FIJAR POCIIONES 
			}
			
		}
	}
}
//SE USARA POR CADA CICLO DE JUEGO PARA ACTUALIZAR LA POS DE LAS PIEZAS
void updateBoard(Board & board) 
{
	if(board.currentPiece.type != 'D'){
		
		verifyPosToCurrentPiece();
		
		movePieceBottom(board.currentPiece);
	}
	
}
	
	
	

