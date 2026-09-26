#include "../header/Game.h"

Game builGame()
{
	Game game;
	game.board = buildBoard();
	game.level = buildLevel();
	
	game.graphic = buildGameGraphic();
	game.currentPlayer = buildPlayer();
	
	game.state.currentState = State::MENU;
	
	game.menu = buildMenu();
	
	return game;
}

void resetGame(Game & game)
{
	game.board = buildBoard();
	game.currentPlayer = game.menu.selectedPlayer;
	game.state.currentState = State::PLAY;
}

void updateGame(Game &game, KeyPressed & key ,float time)
{
	
	if(game.state.currentState == State::START_GAME){
		resetGame(game);
		return;
	}
	if(game.state.currentState == State::PLAY){
		game.graphic.updateTimer += time;
		
		verifyKeys(game , key , time);
		verifyButtonsBoard(game);
		
		
		
		if (game.graphic.updateTimer >= game.level.speed)
		{
			game.graphic.updateTimer -= game.level.speed;
			
			//SI NO PUEDO TERMINAR DE ACTULIZAR EL JUEGO ASUME QUE YA SE TERMINO
			if(!updateBoard(game.board)) game.state.currentState = State::MENU;
			
			updateLevel(game.level, getFullRows(game.board));
			
		}
		return;
	}
	if(game.state.currentState == State::PAUSE){
		
		
		//PUASE ACTION
		return;
	}
	if(game.state.currentState == State::REPRODUCE){
		game.graphic.updateTimer += time;
		
		verifyKeys(game , key , time);
		verifyButtonsBoard(game);
		
		cleanCellsToHistorical(game.board);
		if(game.graphic.updateTimer >= 4.0f){
			game.state.currentState = State::PLAY;
		}
		return;
	}
	if(game.state.currentState == State::MENU){
		verifyButtonsMenu(game.menu , game.state);
		verifyBoxRecords(game.menu);
		verifyTextInputNameBox(game.menu);
		return;
	}
	
	
}



void verifyKeys(Game & game, KeyPressed & key ,float time)
{
	game.graphic.keyTimer += time;
	
	if(game.graphic.keyTimer >= KEY_DELAY)
	{
		game.graphic.keyTimer = 0.0f;
		
		if(key.currentKey == KeyPressed::ANY)
			return;
		
		switch(key.currentKey){
		case KeyPressed::KEY_L:
			moveRight(game.board);
			key.currentKey = KeyPressed::ANY;
		break;
		case KeyPressed::KEY_J:
			moveLeft(game.board);
			key.currentKey = KeyPressed::ANY;
		break;
		case KeyPressed::KEY_K:
			rotate(game.board);
			key.currentKey = KeyPressed::ANY;
		break;
		case KeyPressed::KEY_H:
			holdPiece(game.board);
			key.currentKey = KeyPressed::ANY;
		break;
		case KeyPressed::KEY_SPACE:
			moveToBottom(game.board);
			key.currentKey = KeyPressed::ANY;
		break;
		case KeyPressed::KEY_ESCAPE:
			game.state.currentState = State::PAUSE;
			key.currentKey = KeyPressed::ANY;
		break;
		case KeyPressed::KEY_U:
			goToPrev(game.board);
			game.graphic.updateTimer = 0.0f;
			game.state.currentState = State::REPRODUCE;
			key.currentKey = KeyPressed::ANY;
		break;
		case KeyPressed::KEY_O:
			goToNext(game.board);
			game.graphic.updateTimer = 0.0f;
			game.state.currentState = State::REPRODUCE;
			key.currentKey = KeyPressed::ANY;
		break;	
		}
		
		
	}
}

void verifyButtonsBoard(Game & game)
{
	if(isPressTexture(game.graphic.textures , buildPosition(BUTTON_1_X , BUTTON_Y) , "back")){
		goToPrev(game.board);
		game.graphic.updateTimer = 0.0f;
		game.state.currentState = State::REPRODUCE;
		return;
	}
	if(isPressTexture(game.graphic.textures , buildPosition(BUTTON_2_X , BUTTON_Y) , "advance")){
		goToNext(game.board);
		game.graphic.updateTimer = 0.0f;
		game.state.currentState = State::REPRODUCE;
		return;
	}
	if(isPressTexture( game.graphic.textures , buildPosition(BUTTON_3_X , BUTTON_Y) , "pause")){		
		game.state.currentState =State::PAUSE;
		return;
	}
	if(isPressTexture(game.graphic.textures , buildPosition(BUTTON_4_X , BUTTON_Y) , "close")){		
		game.state.currentState = State::MENU;
		return;
	}
	
}


//DIBUJO DE JUEGO 
void drawPiecesTextures(Game & game)
{
	Row *currentRow = game.board.top;
	int y = 0;
	while (currentRow != nullptr)
	{
		for (int x = 0; x < Row::MAX_COLUMNS; x++)
		{
			
			if (!currentRow->cell[x].isSelected)
				continue;
			
			
			string nameImg = "Tetri" + string(1, currentRow->cell[x].type);			
			Position pos = getTexturePosition(x, y);
			drawTexture(game.graphic.textures, nameImg , pos);
		}
		y++;
		currentRow = currentRow->next;
	}
}

void drawCurrentPiece(Game & game)
{
	TetriPiece piece = game.board.currentPiece;
	
	if (piece.type == 'D')
		return;
	string nameImg = "Tetri" + string(1, piece.type);
	
	for (int i = 0; i < TetriPiece::SIZE; i++)
	{
		int x = piece.pieces[i].x;
		int y = piece.pieces[i].y;
		
		Position pos = getTexturePosition(x, y);
		
		drawTexture(game.graphic.textures , nameImg , pos);
	}
}



void drawBackgroundBoard(Game & game)
{
	
	Position pos = buildPosition(0.0f , 0.0f);
	drawTexture(game.graphic.textures , "boardBackground" , pos);
	
	drawTexture(game.graphic.textures, "back" ,buildPosition(BUTTON_1_X, BUTTON_Y));
	drawTexture(game.graphic.textures, "advance" ,buildPosition(BUTTON_2_X, BUTTON_Y));
	drawTexture(game.graphic.textures, "pause" ,buildPosition(BUTTON_3_X, BUTTON_Y));
	drawTexture(game.graphic.textures, "close" ,buildPosition(BUTTON_4_X, BUTTON_Y));
	
	drawText(game.graphic.textures , game.currentPlayer.name , FONT_SIZE , {TEXT_X , TEXT_Y_1});	
	drawText(game.graphic.textures , to_string(game.level.points) ,FONT_SIZE , {TEXT_X , TEXT_Y_2});

	
	//CONSTRUCCION DE LA PRIMERA FILA INFERIOR (ESTA DE EXTRA)
	TetriPiece defaultPiece = buildDefault();
	defaultPiece.pieces[0].y = 20;
	for(int i = 0; i < Row::MAX_COLUMNS; i++){
		
		Position pos = buildPosition(defaultPiece.pieces[0].x , defaultPiece.pieces[0].y);
		
		pos  = getTexturePosition(pos.x , pos.y);
		drawTexture(game.graphic.textures, "TetriD" , pos);
		
		defaultPiece.pieces[0].x++;
	}
	
}

void drawHoldPiece(Game & game)
{
	
	Position pos  = buildPosition(HOLD_X , HOLD_Y);
	
	TetriPiece piece = game.board.hold->next != nullptr ? 
		game.board.hold->next->tetriPiece : buildDefault();
	
	string nameImg  = "TetriC" + string(1 , piece.type);
	
	drawTexture(game.graphic.textures , nameImg , pos);
	
}

void drawNextPieces(Game & game)
{
	
	for(int i = 0; i < Bag::WAIT_SIZE; i++){
		TetriPiece piece = game.board.queueBag->currentBag->waitPieces[i];
		
		string nameImg  = "TetriC" + string(1 , piece.type);
		
		drawTexture(game.graphic.textures, nameImg, getTexturePositionToNextPieces(i));
	}
}


void drawGame(Game & game)
{
	if(game.state.currentState == State::PLAY || game.state.currentState == State::REPRODUCE)
	{
		drawBackgroundBoard(game);
		drawPiecesTextures(game);
		drawCurrentPiece(game);
		drawNextPieces(game);
		drawHoldPiece(game);
	}
	
	if(game.state.currentState == State::MENU)
		drawMenu(game.menu);
	

}
