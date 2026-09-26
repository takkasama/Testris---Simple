#pragma once


//MANEJO DE ESTADOS DE JUEGO PARA EL CONTROL DEL FLUJO DE ESTE
struct State
{
	
	//ESTADOS DE JUEGO 
	//congela el juego hasta que se vuelva activar el mismo estado
	const static int PAUSE = 0;
	//estado para indicar que se va a comenzar el juego, por lo que carga el jugador
	const static int START_GAME = 1;
	//ciclo de juego normal
	const static int PLAY = 2;
	//cuando se acciona el boton de avanzar y retroceder para dar un tiempo de avanzar o retroceder libremente
	const static int REPRODUCE = 3;
	//acciones y flujo de menu
	const static int MENU = 4;
	//reproducir toda una partida despues de un gameover
	const static int REPRODUCE_GAME = 5;
	
	//ESTADOS DE NAVEGACION DE MENU
	
	
	
	int currentState;
};

