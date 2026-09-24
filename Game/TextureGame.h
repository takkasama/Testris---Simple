#pragma once
#include<string>
#include "raygui.h"
#include "raylib.h"
#include "raymath.h" 

using namespace std;

const string PATH_PIECES = "Assets/Pieces/";
const string PATH_BUTTONS = "Assets/Background/";	


struct Position
{
	float x;
	float y;
};

Position buildPosition(float x , float y)
{
	Position position;
	position.x = x;
	position.y = y;

	return position;
}

//ESTRUCTURA QUE MANEJA TODAS LAS TEXTURAS DEL JUEGO 
struct TextureGame
{	
	//identificador para buscar las texturas
	string name;
	
	float x;
	float y;
	
	Texture2D texture;
	
	TextureGame * next , * prev;
	
};

TextureGame * buildTextureGame(string nameImg, bool isTetriTexture)
{
	TextureGame * texture = new TextureGame;
	
	
	//POR DEFECTO SOLO SE MANEJARA IMAGENES TIPO .png
	string texturePath = isTetriTexture ? PATH_PIECES + nameImg + ".png" :
		PATH_BUTTONS + nameImg + ".png";	
	
	texture->texture = LoadTexture(texturePath.c_str());
	
	texture->x = 0;
	texture->y = 0;
	
	texture->next = nullptr;
	texture->prev = nullptr;
	
	texture->name = nameImg;
	
	return texture;
}

void unloadResource(TextureGame *& texture)
{	
	UnloadTexture(texture->texture);
}

void updatePositionTextureGame(TextureGame & TextureGame, float x , float y)
{
	TextureGame.x = x;
	TextureGame.y = y;
}


void addTexture(TextureGame *&texture , string nameImg, bool isTetriTexture)
{
	TextureGame * newTexture = buildTextureGame(nameImg, isTetriTexture);
	if(texture == nullptr){
		texture = newTexture;
		return;
	}
	
	newTexture->next = texture;
	texture ->prev = newTexture;
	texture = newTexture;
}


TextureGame * getTexture(TextureGame *& texture ,  string nameImg)
{
	if(texture == nullptr)
		return nullptr;
	
	if(texture->name == nameImg)
		return texture;
	
	
	TextureGame * current = texture;
	
	while(current->next != nullptr && current->next->name != nameImg)
		current = current->next;
	
	if(current->next != nullptr && current->next->name == nameImg)
		return current->next;
	
	return nullptr;
	
}

void cleanTextures(TextureGame *& texture)
{
	if(texture == nullptr)
		return;
	
	TextureGame * current = texture;
	
	while(current != nullptr){
		TextureGame * save = current->next;
		
		unloadResource(current);
		
		current->next = nullptr;
		current->prev = nullptr;
		
		delete current;
		
		current = save;
	}
}


void drawTexture(TextureGame *& texture , string nameImg , Position position)
{
	TextureGame * aux  = getTexture(texture , nameImg);
	
	if(aux == nullptr)
		return;
	
	DrawTexture(aux->texture , position.x , position.y , WHITE);
}


bool isPressTexture(TextureGame *& texture, Position position , string nameImg)
{	
	TextureGame * aux = getTexture(texture , nameImg);
	
	if(aux == nullptr)
		return false;
	
	Rectangle rectangle = {position.x , position.y , (float) aux->texture.width , (float) aux->texture.height};
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
		&& CheckCollisionPointRec(GetMousePosition(), rectangle);
}

