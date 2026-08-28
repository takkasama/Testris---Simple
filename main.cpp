#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main() {
	InitWindow(400, 300, "Ventana con boton (raygui)");
	SetTargetFPS(60);
	
	int clicks = 0;
	
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		if (GuiButton(Rectangle{ 150, 120, 100, 40 }, "Presionar")) {
			clicks++;
		}
		
		DrawText(TextFormat("Clicks: %d", clicks), 150, 200, 20, DARKGRAY);
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}
