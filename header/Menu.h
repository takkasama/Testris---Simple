#pragma once
#include<iostream>
#include "Player.h"
#include "TextureGame.h"
#include "State.h"

using namespace std;

//MENU BUTTONS 
const int BUTTON_MENU_Y = 813.0f;
const int BUTTON_MENU_X_1 = 51.5f;
const int BUTTON_MENU_X_2 = 270.0f;
const int BUTTON_MENU_X_3 = 489.0f;

//ESPACIOS DE TOP RECORDS DE JUGADORES 
const float RECORD_BOX_X = 68.0f;
const float RECORD_BOX_Y_INITIAL = 50.0f;
const float RECORD_BOX_SPACING = 63.0f;

const float TEXT_RECORD_Y_INITIAL = 70.0f;
const float TEXT_RECORD_SPACING = 63.8f;
const float TEXT_RECORD_X =100.0f;

const float TEXT_NAME_BOX_X = 70.0f;
const float TEXT_NAME_BOX_Y = 700.0f;
const float TEXT_NAME_X = 100.0f;
const float TEXT_NAME_Y = 720.0f;

const float CLEAN_BUTTON_BOX_X = 502.0f;
const float CLEAN_BUTTON_BOX_Y = 712.0f;


const float FONT_SIZE_MENU_H1 = 40.0;
const float FONT_SIZE_MENU_H3 = 20.0;


//ESPACIOS PARA CONFIGURACIONES 
const float SETTINGS_BACKGROUND_X = 95.0f;
const float SETTINGS_BACKGROUND_Y = 200.0f;

const float BUTTON_TYPE_SORT_Y = 480.0f;
const float BUTTON_TYPE_SORT_X_1 = 130.0f;
const float BUTTON_TYPE_SORT_X_2 = 390.0f;

const float TEXT_TYPE_SORT_Y = 500.0f;
const float TEXT_TYPE_SORT_X_1 = 150.0f;
const float TEXT_TYPE_SORT_X_2 = 410.0f;

const float TITLE_B0X_X = 130.0f;
const float TITLE_B0X_Y = 300.0f;

const float TITLE_TEXT_X = 220.0f;
const float TITLE_TEXT_Y = 340.0f;


struct Menu
{
	const static int MAX_LENGHT = 10;
	
	int totalPlayers;
	Player * players;
	
	string textNameBox;	
	string saveNameToModify;
	int saveSelectedPos;
	
	bool isQuickSort;
	
	Player selectedPlayer;
	TextureGame * textures;
};


void loadMenuTextures(Menu & menu);
Menu buildMenu();

//en caso de que no se encuentre en el top 10 - se buscara en el archivo para encontrar el archivo para ver si existe o no
void loadPlayerToFile();


//MENU ACCION
void verifyButtonsMenu(Menu & menu , State & state);
void verifyButtonsSettings(Menu & menu , State & state);
void verifyBoxRecords(Menu & menu);
void verifyTextInputNameBox(Menu & menu);

void verifyMenu(Menu & menu , State & state);

//DIBUJO DE MENU
void drawBackgroundMenu(Menu & menu);
void drawTopRecordPlayers(Menu & menu);
void drawSettings(Menu & menu);

void drawMenu(Menu & menu, State  & state);

