#include "../header/Menu.h"

void loadMenuTextures(Menu & menu)
{
	addTexture(menu.textures, "settingsBackground", false);
	addTexture(menu.textures, "menuBackground", false);
	
	
	addTexture(menu.textures, "playerBox", false);
	
	addTexture(menu.textures, "reload", false);
	addTexture(menu.textures, "exit", false);
	addTexture(menu.textures, "settings", false);
	addTexture(menu.textures, "start", false);
	addTexture(menu.textures, "empty", false);
	
	
	addTexture(menu.textures, "playerNameBox", false);
	addTexture(menu.textures, "playerRecordBox", false);
	addTexture(menu.textures, "settingsText", false);
	
	addTexture(menu.textures, "clean", false);
	
}

Menu buildMenu()
{
	Menu menu;
	menu.isQuickSort = true;
	
	menu.textNameBox = "";
	
	menu.saveNameToModify = "";
	menu.players = getTopPlayer(menu.isQuickSort , menu.totalPlayers);
	menu.selectedPlayer = buildPlayer();
	menu.saveSelectedPos = -1;
	
	menu.textures = nullptr;
	
	loadMenuTextures(menu);
	
	return menu;
}

void verifyMenu(Menu & menu , State & state)
{
	if(state.currentState == State::MENU){
		verifyBoxRecords(menu);
		verifyButtonsMenu(menu , state);
		verifyTextInputNameBox(menu);
		return;
	}
	
	if(state.currentState == State::SETTINGS)
		verifyButtonsSettings(menu, state);
	
}

void reloadPlayers(Menu & menu)
{
	menu.players = getTopPlayer(menu.isQuickSort , menu.totalPlayers);
}


void reloadMenu(Menu & menu , State & state, int points)
{
	if(points >= 0){
		menu.selectedPlayer.points = points;
		writePlayerToFile(menu.selectedPlayer);
	}
	reloadPlayers(menu);
	menu.saveSelectedPos = -1;
	menu.saveNameToModify = "";
	menu.selectedPlayer = buildPlayer();
	
	state.currentState = State::MENU;	
}


void verifyButtonsMenu(Menu & menu , State & state)
{
	if(isPressTexture(menu.textures , buildPosition(BUTTON_MENU_X_1 , BUTTON_MENU_Y) , "reload")){
		reloadMenu(menu , state , -1);
		return;
	}
	
	if(isPressTexture(menu.textures , buildPosition(BUTTON_MENU_X_2 , BUTTON_MENU_Y) , "start")){
		if(!menu.saveNameToModify.empty() && menu.saveSelectedPos != -1){
			if(updatePlayer(menu.players[menu.saveSelectedPos] , true  ,false , menu.textNameBox)){
				
				menu.selectedPlayer.name = menu.textNameBox;
				
				menu.players[menu.saveSelectedPos].name = menu.textNameBox;
				menu.saveNameToModify = "";
				menu.saveSelectedPos = -1;
				
			}
		}
		menu.selectedPlayer.name = menu.textNameBox.empty() ? "NO NAME" : menu.textNameBox;
		writePlayerToFile(menu.selectedPlayer);
		
		state.currentState = State::START_GAME;
		return;
	}
	
	if(isPressTexture(menu.textures , buildPosition(BUTTON_MENU_X_3 , BUTTON_MENU_Y) , "settings")){
		state.currentState = State::SETTINGS;
		return;
	}
	
	if(isPressTexture(menu.textures , buildPosition(CLEAN_BUTTON_BOX_X , CLEAN_BUTTON_BOX_Y) , "clean")){
		
		if(!menu.saveNameToModify.empty() && menu.saveSelectedPos != -1 && 
		   menu.saveNameToModify == menu.players[menu.saveSelectedPos].name)
			updatePlayer(menu.players[menu.saveSelectedPos], false , true , "");
		
		menu.textNameBox = "";
		menu.saveNameToModify = "";
		menu.selectedPlayer = buildPlayer();
		menu.saveSelectedPos = -1;
		return;
	}
	
}

void verifyButtonsSettings(Menu & menu , State & state)
{
	if(isPressTexture(menu.textures , {BUTTON_TYPE_SORT_X_1 , BUTTON_TYPE_SORT_Y}, "empty")){
		menu.isQuickSort = true;
		reloadPlayers(menu);
		return;
	}
	if(isPressTexture(menu.textures , {BUTTON_TYPE_SORT_X_2 , BUTTON_TYPE_SORT_Y}, "empty")){
		menu.isQuickSort = false;
		reloadPlayers(menu);
		state.currentState = State::MENU;
		return;
	}
	
}


void verifyBoxRecords(Menu & menu)
{
	float pos = RECORD_BOX_Y_INITIAL;
	
	for(int i = 0; i < menu.totalPlayers - 1; i++)
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
	drawTexture(menu.textures , "reload" , {BUTTON_MENU_X_1 ,BUTTON_MENU_Y});
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

void drawSettings(Menu & menu)
{	
	
	drawTexture(menu.textures , "settingsBackground" , {SETTINGS_BACKGROUND_X, SETTINGS_BACKGROUND_Y});
	drawTexture(menu.textures , "empty" , {BUTTON_TYPE_SORT_X_1, BUTTON_TYPE_SORT_Y});
	drawTexture(menu.textures , "empty" , {BUTTON_TYPE_SORT_X_2, BUTTON_TYPE_SORT_Y});
	drawTexture(menu.textures , "settingsText" , {TITLE_B0X_X, TITLE_B0X_Y});
	
	drawText(menu.textures," Sorting Type ", FONT_SIZE_MENU_H1 ,{TITLE_TEXT_X , TITLE_TEXT_Y});

	drawText(menu.textures," QUICKSORT ", FONT_SIZE_MENU_H3 ,{TEXT_TYPE_SORT_X_1 ,TEXT_TYPE_SORT_Y});
	drawText(menu.textures," BUBBLESORT ", FONT_SIZE_MENU_H3 ,{ TEXT_TYPE_SORT_X_2 ,TEXT_TYPE_SORT_Y});
	
}

void drawMenu(Menu & menu, State & state)
{
	drawBackgroundMenu(menu);
	drawTopRecordPlayers(menu);
	
	if(state.currentState == State::SETTINGS) drawSettings(menu);
}
