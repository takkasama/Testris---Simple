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
	
	addTexture(menu.textures, "clean", false);
	
}

Menu buildMenu()
{
	Menu menu;
	menu.textNameBox = "";
	
	menu.saveNameToModify = "";
	
	menu.players = getTopPlayer(true , menu.totalPlayers);
	menu.selectedPlayer = buildPlayer();
	menu.saveSelectedPos = -1;
	
	menu.textures = nullptr;
	
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
		if(!menu.saveNameToModify.empty()){
			if(modifyPlayerName(menu.saveNameToModify , menu.textNameBox)){
				menu.selectedPlayer.name = menu.textNameBox;
				menu.players[menu.saveSelectedPos].name = menu.textNameBox;
				menu.saveNameToModify = "";
				menu.saveSelectedPos = -1;
			}
		}
		menu.selectedPlayer.name = menu.textNameBox;
		writePlayerToFile(menu.selectedPlayer);
		
		state.currentState = State::START_GAME;
		return;
	}
	
	if(isPressTexture(menu.textures , buildPosition(BUTTON_MENU_X_3 , BUTTON_MENU_Y) , "settings")){
		
		return;
	}
	
	if(isPressTexture(menu.textures , buildPosition(CLEAN_BUTTON_BOX_X , CLEAN_BUTTON_BOX_Y) , "clean")){
		menu.textNameBox = "";
		menu.saveNameToModify = "";
		menu.selectedPlayer = buildPlayer();
		menu.saveSelectedPos = -1;
		return;
	}
	
}

void verifyBoxRecords(Menu & menu)
{
	float pos = RECORD_BOX_Y_INITIAL;
	
	for(int i = 0; i < menu.totalPlayers; i++)
	{
		if(isPressTexture(menu.textures , {RECORD_BOX_X , pos}, "playerRecordBox")){
			menu.saveNameToModify = menu.players[i].name;
			menu.textNameBox = menu.players[i].name;
			menu.selectedPlayer = menu.players[i];
			menu.saveSelectedPos = i;
		}
		
		pos += RECORD_BOX_SPACING;
	}
}

void verifyTextInputNameBox(Menu & menu)
{	
	if(IsKeyPressed(KEY_DELETE) || IsKeyPressed(KEY_BACKSPACE)){
		if(!menu.textNameBox.empty())
			menu.textNameBox.erase(menu.textNameBox.size() - 1 , 1);
		return;
	}
	
	if(menu.textNameBox.size() >=  Menu::MAX_LENGHT) return;
	
	char newKey = GetCharPressed();
	
	if(newKey == 0) return;
	
	menu.textNameBox += newKey;
}


void drawBackgroundMenu(Menu & menu)
{	
	drawTexture(menu.textures , "menuBackground" , {0.0f ,0.0f});
	drawTexture(menu.textures , "exit" , {BUTTON_MENU_X_1 ,BUTTON_MENU_Y});
	drawTexture(menu.textures , "start" , {BUTTON_MENU_X_2 ,BUTTON_MENU_Y});
	drawTexture(menu.textures , "settings" , {BUTTON_MENU_X_3 ,BUTTON_MENU_Y});
	
	drawTexture(menu.textures , "playerNameBox" , {TEXT_NAME_BOX_X , TEXT_NAME_BOX_Y});
	drawText(menu.textures , menu.textNameBox , FONT_SIZE_MENU_H1 , {TEXT_NAME_X , TEXT_NAME_Y});
	
	drawTexture(menu.textures , "clean" , {CLEAN_BUTTON_BOX_X , CLEAN_BUTTON_BOX_Y});
		
}
void drawTopRecordPlayers(Menu & menu)
{
	float pos = RECORD_BOX_Y_INITIAL;
	float posText = TEXT_RECORD_Y_INITIAL;
	
	for(int i = 0 ; i < menu.totalPlayers; i++)
	{
		string text = "NAME : " + menu.players[i].name + "\t RECORD POINTS : " + to_string(menu.players[i].record);
		
		drawTexture(menu.textures , "playerRecordBox", {RECORD_BOX_X , pos});
		drawText(menu.textures , text , FONT_SIZE_MENU_H3 , {TEXT_RECORD_X , posText});
		pos += RECORD_BOX_SPACING;
		posText += TEXT_RECORD_SPACING;
	}
}


void drawMenu(Menu & menu)
{
	drawBackgroundMenu(menu);
	drawTopRecordPlayers(menu);
}
