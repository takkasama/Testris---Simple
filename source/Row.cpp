#include "../header/Row.h"



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

bool isFillRow(Row *row)
{
	for(int i = 0 ; i < Row::MAX_COLUMNS ; i++)
		if(!row->cell[i].isSelected)
		return false;
	
	return true;
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


