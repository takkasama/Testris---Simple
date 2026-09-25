#include "../header/TextureGame.h"

Position buildPosition(float x , float y)
{
	Position position;
	position.x = x;
	position.y = y;
	
	return position;
}

TextureGame * buildTextureGame(string nameFile, bool isTetriTexture)
{
	TextureGame * texture = new TextureGame;
	
	//POR DEFECTO SOLO SE MANEJARA IMAGENES TIPO .png
	string texturePath = isTetriTexture ? PATH_PIECES + nameFile + ".png" :
		PATH_BUTTONS + nameFile + ".png";	
	texture->texture = LoadTexture(texturePath.c_str());
	
	texture->font = LoadFont(FONT_7_SEGMENT_PATH.c_str());
	
	texture->x = 0;
	texture->y = 0;
	
	texture->next = nullptr;
	texture->prev = nullptr;
	
	texture->name = nameFile;
	
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


void addTexture(TextureGame *&texture , string nameFile, bool isTetriTexture)
{
	TextureGame * newTexture = buildTextureGame(nameFile, isTetriTexture);
	if(texture == nullptr){
		texture = newTexture;
		return;
	}
	
	newTexture->next = texture;
	texture ->prev = newTexture;
	texture = newTexture;
}


TextureGame * getTexture(TextureGame *& texture ,  string nameFile)
{
	if(texture == nullptr)
		return nullptr;
	
	if(texture->name == nameFile)
		return texture;
	
	
	TextureGame * current = texture;
	
	while(current->next != nullptr && current->next->name != nameFile)
		current = current->next;
	
	if(current->next != nullptr && current->next->name == nameFile)
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


void drawTexture(TextureGame *& texture , string nameFile , Position position)
{
	TextureGame * aux  = getTexture(texture , nameFile);
	
	if(aux == nullptr)
		return;
	
	DrawTexture(aux->texture , position.x , position.y , WHITE);
}

void dranText(TextureGame *& texture , string text , float fontSize , Position position)
{	
	if(texture == nullptr)
		return;
	
	
	Vector2 pos = {position.x, position.y};
	
	DrawTextEx(texture->font , text.c_str() , pos ,fontSize , 1.0f , BLACK);
}

bool isPressTexture(TextureGame *& texture, Position position , string nameFile)
{	
	TextureGame * aux = getTexture(texture , nameFile);
	
	if(aux == nullptr)
		return false;
	
	Rectangle rectangle = {position.x , position.y , (float) aux->texture.width , (float) aux->texture.height};
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) 
		&& CheckCollisionPointRec(GetMousePosition(), rectangle);
}
