#include <iostream>
#include <string>
#include <ctime>

#include "raygui.h"
#include "raylib.h"
#include "raymath.h" // incluye Lerp, Vector2Lerp, etc.

#include "Board.h"

using namespace std;


const string PATH_PIECES = "Assets/TetriPieces";
const string PATH_BUTTONS = "Assets/Buttons";	


	

int main()
{
	
	InitWindow(800, 450, "TETRIS");
	SetTargetFPS(60);
	
	Vector2 origen  = { 0.0f, 0.0f };
	Vector2 destino = { 200.0f, 0.0f };
	float t = 0.0f;          // progreso de 0.0 a 1.0
	float duracion = 0.5f;   // segundos que tarda el movimiento
	
	Vector2 posicionActual = origen;
	
	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		
		if (t < 1.0f) {
			t += dt / duracion;
			if (t > 1.0f) t = 1.0f;
			posicionActual.x = Lerp(origen.x, destino.x, t);
			posicionActual.y = Lerp(origen.y, destino.y, t);
		}
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectangleV(posicionActual, Vector2{40, 40}, RED);
		EndDrawing();
	}
	
	return 0;
}


