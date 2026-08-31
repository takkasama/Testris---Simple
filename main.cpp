#include <iostream>
#include <string>

#include "raygui.h"
#include "raylib.h"

using namespace std;




const string PATH_TETRIMINOS = "Assets/Tetriminos";
const string PATH_BUTTONS = "Assets/Buttons";

const int LEFT_VALUE = 0;
const int TOP_VALUE = 1;
const int RIGHT_VALUE = 2;
const int BOTTOM_VALUE = 3;
const int NONE_VALUE = 4;



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

TetriminoPiece buildTetriminoPiece(char type, int sigTetri, int numberTetri){
	TetriminoPiece piece;
	piece.type = type;
	piece.isSpecial = type == 'B';
	piece.numberTetri = numberTetri;
	piece.texturePath = type  + ".png";
	piece.posX = 0;
	piece.posY = 0;
	
	return piece;
}

//PILA PARA LA CONTRUCCION Y ORGANIZACION DE LA PIEZA, DE MODO QUE SE LEE DE 
// DE DERECHA A IZQUIERDA CONVIENE LEERLA COMO UNA PILA
struct Tetrimino {
	
	TetriminoPiece piece;
	
	Tetrimino * top;
	
	Tetrimino * prev;
	
};

bool isEmptyTetrimino(Tetrimino * top){ return top == nullptr; }

TetriminoPiece * popTetrimino(Tetrimino *& top){
	if(isEmptyTetrimino(top)) return nullptr;
	
	Tetrimino *save = top;
	
	top = save -> prev;
	
	TetriminoPiece *piece = new TetriminoPiece(save->piece);	
	delete save;
	
	return piece;
}




void pushTetrimino (Tetrimino *& top, TetriminoPiece piece){
	Tetrimino * t = new Tetrimino();
	
	t->prev = nullptr;
	t->top = nullptr;
	t->piece = piece;
	
	if(isEmptyTetrimino(top))
		t = t;
	else
		t->top = t;
	
	
}	

//CONSTRUYE TODA LA PIECE Y LA ORIENTACION COMPLETA DE ESTA
void buildTetrimino(Tetrimino *& top, int type){	
	
	top = nullptr;
	
	switch(type){
		
	case 1 : 
		pushTetrimino(top, buildTetriminoPiece(type, RIGHT_VALUE, 1));
 		pushTetrimino(top, buildTetriminoPiece(type, TOP_VALUE, 2));
		pushTetrimino(top, buildTetriminoPiece(type, RIGHT_VALUE, 3));
		pushTetrimino(top, buildTetriminoPiece(type, NONE_VALUE, 4));
		
		break;
	case 2 :
		pushTetrimino(top, buildTetriminoPiece(type, TOP_VALUE, 1));
		pushTetrimino(top, buildTetriminoPiece(type, RIGHT_VALUE, 2));
		pushTetrimino(top, buildTetriminoPiece(type, BOTTOM_VALUE, 3));
		pushTetrimino(top, buildTetriminoPiece(type, NONE_VALUE, 4));
		break;
	case 3 :
		pushTetrimino(top, buildTetriminoPiece(type, TOP_VALUE, 1));
		pushTetrimino(top, buildTetriminoPiece(type, TOP_VALUE, 2));
		pushTetrimino(top, buildTetriminoPiece(type, TOP_VALUE, 3));
		pushTetrimino(top, buildTetriminoPiece(type, NONE_VALUE, 4));
		break;
	case 4 :
		pushTetrimino(top, buildTetriminoPiece(type, RIGHT_VALUE, 1));
		pushTetrimino(top, buildTetriminoPiece(type, BOTTOM_VALUE, 2));
		pushTetrimino(top, buildTetriminoPiece(type, RIGHT_VALUE, 3));
		pushTetrimino(top, buildTetriminoPiece(type, NONE_VALUE, 4));
		break;
	case 5 :
		pushTetrimino(top, buildTetriminoPiece(type, BOTTOM_VALUE, 1));
		pushTetrimino(top, buildTetriminoPiece(type, BOTTOM_VALUE, 2));
		pushTetrimino(top, buildTetriminoPiece(type, RIGHT_VALUE, 3));
		pushTetrimino(top, buildTetriminoPiece(type, NONE_VALUE, 4));
		break;
	case 6 :
		pushTetrimino(top, buildTetriminoPiece(type, BOTTOM_VALUE, 1));
		pushTetrimino(top, buildTetriminoPiece(type, BOTTOM_VALUE, 2));
		pushTetrimino(top, buildTetriminoPiece(type, LEFT_VALUE, 3));
		pushTetrimino(top, buildTetriminoPiece(type, NONE_VALUE, 4));
		break;
	case 7 :
		pushTetrimino(top, buildTetriminoPiece(type, RIGHT_VALUE, 1));
		pushTetrimino(top, buildTetriminoPiece(type, BOTTOM_VALUE, 2));
		pushTetrimino(top, buildTetriminoPiece(type, RIGHT_VALUE, 3));
		pushTetrimino(top, buildTetriminoPiece(type, NONE_VALUE, 4));
		break;
	default:
		break;
	}
	

	
}




//BOLSA PARA GUARDAR LA PIEZAS A CARGAR
struct Bag{
	const int MAX_SIZE = 7;
	
	Tetrimino tetrimino;
	
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












































































































