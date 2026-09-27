#pragma once
#include<iostream>
#include "TextureGame.h"

const  int MAX_ROW = 20;
const  int MAX_COLUMN = 10;


struct Event 
{

	/*
	LOS EventNodeOS MANEJARAN DIRECTAMENTE EN TRES TIPOS 
	A. CADA 5 FILAS SE FILAS SE AUMENTARA LA VELOCIDAD (EventNodeO A O PRIMERO EN SALIR Y EN ENTRAR)
	B. COLOCACION DE BLOQUE EN POSICION ALEATORIA DEL BOARD QUE NO DESAPARECE Y LO PERMITE RELLENAR LA FILA (SE GENERA CADA 5 FILAS DESPUES DE QUE GENERE EL PRIMER EventNodeO)
	C. COLOCA UNA TETRI QUE SI SE ELIMINA QUITA EL TOTAL GANADO AL ELMINAR CUATRO FILAS QUE SUCEDE CADA 10 FILAS
	*/
	
	
	const static int CONDITION_EVENT_BLOCK = 5;
	const static int CONDITION_EVENT_BOMB = 5; 
	const static int CONDITION_EVENT_UPDAGRADE_SPEED = 10; 
	
	const static int RAND_PIECE_BLOCK = 1;
	const static int UPGRADE_SPEED = 2;
	const static int RAND_BOMB = 3;
	const static int NONE = -1;

	int currentEvent;
};

Event buildEvent(int typeEvent);


struct EventNode
{	
	Event event;
	
	EventNode * next;
};

struct EventQueue
{		
	int currentRows;
	
	EventNode * front;
	EventNode * back;
};


bool isValidToActiEvent(Event & event, int currentRows);

void enqueueEvent(EventQueue * queue, Event  event);
EventNode * desqueEvent(EventQueue *& event);
EventNode * getBackToEventQueue(EventQueue * queue);

EventQueue * buildEventQueue();

Event getNextEvent(EventQueue *& queue);

	
