#pragma once
#include "raygui.h"
#include "raylib.h"
#include "raymath.h" 
#include<iostream>
using namespace std;

const string PATH_PIECES = "resources/Pieces/";
const string PATH_BUTTONS = "resources/Background/";	

const string FONT_7_SEGMENT_PATH = "resources/7segment.ttf";
//DrawRectangleLines(fontPosition.x, fontPosition.y, textSize.x, textSize.y, RED);
//void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);	
struct Position
{
	float x;
	float y;
};

Position buildPosition(float x, float y);

//ESTRUCTURA QUE MANEJA TODAS LAS TEXTURAS DEL JUEGO 
struct TextureGame
{	
	//identificador para buscar las texturas
	string name;
	
	float x;
	float y;
	
	Texture2D texture;
	
	Font font;
	
	TextureGame * next , * prev;
	
};

TextureGame * buildTextureGame(string nameFile, bool isTetriTexture);

void unloadResource(TextureGame *& texture);

void updatePositionTextureGame(TextureGame & TextureGame, float x, float y);

void addTexture(TextureGame *&texture, string nameFile, bool isTetriTexture);

TextureGame * getTexture(TextureGame *& texture, string nameFile);

void cleanTextures(TextureGame *& texture);

void drawTexture(TextureGame *& texture, string nameFile, Position position);

void dranText(TextureGame *& texture, string text, float fontSize, Position position);

bool isPressTexture(TextureGame *& texture, Position position, string nameFile);
