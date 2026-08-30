#include <iostream>
#include <string>

#include "raygui.h"
#include "raylib.h"

using namespace std;




const string PATH_TETRIMINOS = "Assets/Tetriminos";
const string PATH_BUTTONS = "Assets/Buttons"

struct TetriminoPiece{
	
	//TENDRA LOS VALORES BASE DE S - Z - I - 0 - J - L - T  ADEMAS DE LOS VALORES DE D(DEFAULT) y B(BOM-SPECIAL) 
	char type;
	
	//CONTRUIDA POR TYPE + .png
	string texturePath;
	
	//INDICADOR PARA EL TETRIMINO BOMBA O ESPECIAL DE MODO QUE SE PUEDA USAR COMO BADENRA
	bool isSpecial;
	
	/*
		INDICADOR PARA EL NUMERO DE LA PIEZA Y LA CONSTRUCCION DE ESTA DONDE EL NUMERO INDICARA LA DIRECCION DE LA SIGUIENTE PIEZA
		LOS VALORES DE LA PIEZAS PUEDEN SER :
			0 ( IZQUIERDA ) 
			1 ( ARRIBA )
			2 ( DERECHA )
			3 ( ABAJO )
			4 (NONE) -> SOLO SI LA PIEZA ES LA DEL MISMO NUMERO
	*/
	int sigTetri;
	
	
	/*
		INDICADOR DEL NUMERO DE PIEZA DE CONSTRUCCION, LA PIEZAS SE LEERAN DEL MAYOR AL MENOR PARA LA CONTRUCCION DE ESTAS
		LOS VALORES SERAN : 
			1 : PIEZA UNO
			2 : PIEZA DOS
			3 : PIEZA TRES
			4 : PIEZA CUATRO
	*/
	int numberTetri;
	
	
	
	//PARA LA RECREACION DE MOVIMIENTOS
	int posX;
	int posY;
};


//PILA PARA LA CONTRUCCION Y ORGANIZACION DE LA PIEZA, DE MODO QUE SE LEE DE 
// DE DERECHA A IZQUIERDA CONVIENE LEERLA COMO UNA PILA
struct Tetrimino {
	
	TetriminoPiece piece;
	
	Tetrimino * top;
	
};


//BOLSA PARA GUARDAR LA PIEZAS A CARGAR
struct Bag{
	const int MAX_SIZE = 7;
	
	Tetrimino Tetrimino;
	
	Bag * queue;
	
};









//ELEMENTOS BASICOS PARA EL BOARD 
struct NodeTetri{
	
	Tetrimino tetrimonio;
	
	NodeTetri * next;
	NodeTetri * prev;
	
};

struct NodeBoard{
	
	NodeTetri * row;
		
	NodeBoard * next;
	NodeBoard * prev;
};



//LISTA DE ESPERA
struct NextTetri{
	
	Bag bag;
	
	NextTetri * queue;
	
};




int main() {

	return 0;
}




//	InitWindow(400, 300, "Cargar PNG");
//	SetTargetFPS(60);
//	
//	Texture2D sprite = LoadTexture("Assets/Gem1.png");
//	
//	while (!WindowShouldClose()) {
//		BeginDrawing();
//		ClearBackground(RAYWHITE);
//		DrawTexture(sprite, 150, 100, WHITE);
//		EndDrawing();
//	}
//	
//	UnloadTexture(sprite); // liberar antes de cerrar
//	CloseWindow();












































































































