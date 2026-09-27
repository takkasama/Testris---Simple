#pragma once


#include "TetriPiece.h"
#include "Bag.h"
#include "Hold.h"
#include "Historical.h"
#include "Row.h"
#include "Event.h"


// ORGANIZACION DE LAS FILAS ADEMAS DE ACCESO A LA PARTE INFERIOR PARA LA LECTURA DE LA VERFICACIONES DE ESTADO DE LAS FILAS
//ELEMENTO CENTRAL DE LA LOGICA DE JUEGO	
struct Board
{
	const static int MAX_ROWS = 20;	
	
	QueueBag * queueBag;
	Hold * hold;
	
	TetriPiece currentPiece;
	
	Historical * historical;
	Historical * currentHistorical;
	
	Row *top, *bottom;
};

Board buildBoard();

void cleanRow(Board & board, Row *& row);
void cleanTopRow(Board & board);
	

Row * getRow(Board & board, int y);
bool isUsedCell(Board & board, int x, int y);
int getFullRows(Board & board);

void randSpecialPiece(Board & board , bool isBlockPiece);


//SE USARA POR CADA CICLO DE JUEGO PARA ACTUALIZAR LA POS DE LAS PIEZAS
bool canMoveDown(Board & board);
bool canMoveRight(Board & board);
bool canMoveLeft(Board & board);
bool canRotate(Board & board);

void lockCurrentPiece(Board & board);

//CUANDO SE RETROCEDE UN PASO SE HABILITARA UN TIEMPO DE ESPERA PARA AVANZAR Y RETROCEDER EN ESE TIEMPO SI NO SE ENCUENTRA EN LA PARTE FINAL DE LA
//LISTA SE BORRARA TODOS LOS ELEMENTOS SIGUIENTES DEL HISTORICO 

void goToNext(Board & board);
void goToPrev(Board & board);

//METODO DE ACTUALIZACION DE LA LISTA REPRODUCCION 
//LA FUNCION DE ESTA ES SIMPLE, SI EL currentHistorical ES NULO SE ASUME QUE NO ESTA REPRODUCIENDO
//SI NO ES NULO Y SE ASUME QUE SE VA A MODIFICAR LA LISTA DADO QUE SE HIZO UN MOVIMIENTO AJENO A historical
//POR LO QUE SE ELIMINAR TODO LOS ELEMENTOS DE LAS LISTA DESPUES DEL ACTUAL

//EL METODO SE LLAMARA POR CADA MODIFICACION DE LA LOCALIZACION DE LA PIEZA DE MODO QUE 
//QUE SE COLOCARA ANTES DE HACER EL MOVIENTO , PARA LUEGO HACER EL MOVIMIENTO Y COLOCARLO EN EL HISTORIAL MODIFICADO
void updateHistorial(Board & board);
void loadNextPiece(Board & board);
void holdPiece(Board & board);
void applyEvent(Board & board , Event event);

void moveRight(Board & board);
void moveLeft(Board & board);
void rotate(Board & board);
void moveDown(Board & board);
void moveToBottom(Board & board);

//INDICA QUE SI UNA PIEZA QUE ESTA MARCADA SE ENCUENTRA EN EL TOP DEL BOARD
bool isBoardFull(Board & board);
bool updateBoard(Board & board);

//COLOCA LA PIEZA EN LA PARTE BAJA SI NO SE DESEA ESPERAR A QUE BASE EN EL CICLO NORMAL
void cleanCellsToHistorical(Board & board);
