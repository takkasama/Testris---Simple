#include "../header/Menu.h"

void loadMenuTextures(Menu & menu)
{
	addTexture(menu.textures, "boardBackground", false);
	addTexture(menu.textures, "menuBackground", false);
	
	addTexture(menu.textures, "playerBox", false);
	
	addTexture(menu.textures, "replay", false);
	addTexture(menu.textures, "exit", false);
	addTexture(menu.textures, "settings", false);
	addTexture(menu.textures, "start", false);
	
	addTexture(menu.textures, "playerNameBox", false);
	addTexture(menu.textures, "playerRecordBox", false);
	
	
}

Menu buildMenu()
{
	Menu menu;
	menu.totalPlayers = 0;
	menu.textNameBox = "";
	
	menu.players = getTopPlayer(true , menu.totalPlayers);
	menu.selectedPlayer = buildPlayer();
	
	loadMenuTextures(menu);
	
	return menu;
}

void verifyButtonsMenu(Menu & menu , State & state)
{
	if(isPressTexture(menu.textures , buildPosition(BUTTON_MENU_X_1 , BUTTON_MENU_Y) , "exit")){
		CloseWindow();
		return;
	}
	
	if(isPressTexture(menu.textures , buildPosition(BUTTON_MENU_X_2 , BUTTON_MENU_Y) , "start")){
		state.currentState = State::START_GAME;
		return;
	}
	
	if(isPressTexture(menu.textures , buildPosition(BUTTON_MENU_X_3 , BUTTON_MENU_Y) , "replay")){
		state.currentState = State::REPRODUCE_GAME;
		return;
	}
	
}

void verifyBoxRecords(Menu & menu)
{
	float pos = RECORD_BOX_Y_INITIAL;
	
	for(int i = 0; i < menu.totalPlayers; i++)
	{
		if(isPressTexture(menu.textures , {RECORD_BOX_X , pos}, "playerRecordBox")){
			drawText(menu.textures , menu.players[i].name , FONT_SIZE_MENU , {TEXT_NAME_BOX_X, TEXT_NAME_BOX_Y});	
		}
		
		pos += RECORD_BOX_SPACING;
	}
	
	
	
}


void drawBackgroundMenu(Menu & menu)
{	
	drawTexture(menu.textures , "menuBackground" , {0.0f ,0.0f});
	drawTexture(menu.textures , "exit" , {BUTTON_MENU_X_1 ,BUTTON_MENU_Y});
	drawTexture(menu.textures , "start" , {BUTTON_MENU_X_2 ,BUTTON_MENU_Y});
	drawTexture(menu.textures , "replay" , {BUTTON_MENU_X_3 ,BUTTON_MENU_Y});
	
	drawTexture(menu.textures , "playerNameBox" , {TEXT_NAME_BOX_X , TEXT_NAME_BOX_Y});
	drawText(menu.textures , menu.textNameBox , FONT_SIZE_MENU , {TEXT_NAME_BOX_X , TEXT_NAME_BOX_Y});
		
}
void drawTopRecordPlayers(Menu & menu)
{
	float pos = RECORD_BOX_Y_INITIAL;
	float posText = TEXT_RECORD_Y_INITIAL;
	
	for(int i = 0 ; i < menu.totalPlayers; i++)
	{
		string text = "NAME : " + menu.players[i].name + "\t RECORD POINTS : " + to_string(menu.players[i].record);
		
		drawTexture(menu.textures , "playerRecordBox", {RECORD_BOX_X , pos});
		drawText(menu.textures , text , 22 , {TEXT_RECORD_X , posText});
		pos += RECORD_BOX_SPACING;
		posText += TEXT_RECORD_SPACING;
	}
}


void drawMenu(Menu & menu)
{
	drawBackgroundMenu(menu);
	drawTopRecordPlayers(menu);
}
