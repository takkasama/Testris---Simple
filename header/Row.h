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
	
	bool isBlockPiece;
	bool isBombPiece;
};

// LISTA DOBLEMENTE ENLAZADA REQUERIDA PARA LA CONSTRUCCION DEL TABLERO
struct Row
{
	const static int MAX_COLUMNS = 10;
	Cell cell[MAX_COLUMNS];
	
	Row *next, *prev;
};



Cell buildCell();

void updateCell(Cell &cell, char type, bool isSelected);
void updateCellToSpecialPiece(Cell &cell, char type, bool isSelected , bool isBlockPiece);

void cleanCell(Cell &cell);


bool isEmptyRow(Row *row);

Row *buildRow();

bool isSelectedCell(Row *row, int posX);

bool isFillRow(Row *row);
bool haveBombPieceOnRow(Row *& row);	

void addRow(Row *&top, Row *&botton, Row *newRow);
