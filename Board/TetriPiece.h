	#pragma once

	struct Piece
	{
		int x;
		int y;
		
	};

	Piece buildPiece(int x, int y)
	{
		Piece piece;
		piece.x = x;
		piece.y = y;
		return piece;
	}
	
	void updatePositionPiece(Piece &piece, int x, int y){piece.x = x; piece.y = y; }
	

	// PILA PARA LA CONTRUCCION Y ORGANIZACION DE LA PIEZA, DE MODO QUE SE LEE DE
	//  DE DERECHA A IZQUIERDA CONVIENE LEERLA COMO UNA PILA
	struct TetriPiece
	{

		const static int SIZE = 4;
		Piece pieces[SIZE];

		// TENDRA LOS VALORES BASE DE S - Z - I - 0 - J - L - T  ADEMAS DE LOS VALORES DE D(DEFAULT) y B(BOM-SPECIAL)
		char type;
		
	};
	
	
	
	void rotatePiece(TetriPiece & tetriPiece){
		
		if(tetriPiece.type == 'O')
			return;
		
		int auxX = tetriPiece.pieces[1].x;
		int auxY = tetriPiece.pieces[1].y;
		
		
		for(int i = 0; i < tetriPiece.SIZE; i++){
			int newX = auxX + (tetriPiece.pieces[i].y - auxY);
			int newY = auxY - (tetriPiece.pieces[i].x - auxX);
			
			updatePositionPiece(tetriPiece.pieces[i], newX, newY);
		}
	}
		
	void movePieceRight(TetriPiece & tetriPiece){
		for(int i = 0; i < tetriPiece.SIZE; i ++)
			tetriPiece.pieces[i].x++;
	}
	void movePieceLeft(TetriPiece & tetriPiece){
		for(int i = 0; i < tetriPiece.SIZE; i++)
			tetriPiece.pieces[i].x--;
	}
	void movePieceDown(TetriPiece & tetriPiece){
		for(int j = 0; j < tetriPiece.SIZE; j++)
			tetriPiece.pieces[j].y++;
	}
	void movePIeceUp(TetriPiece & tetriPiece){
		for(int i =0; i < tetriPiece.SIZE; i++)
			tetriPiece.pieces[i].y--;
	}	
	

	TetriPiece buildZ()
	{
		TetriPiece tetriPiece;
		tetriPiece.pieces[0] = buildPiece(0, 0);
		tetriPiece.pieces[1] = buildPiece(1, 0);
		tetriPiece.pieces[2] = buildPiece(1, 1);
		tetriPiece.pieces[3] = buildPiece(2, 1);

		tetriPiece.type = 'Z';

		return tetriPiece;
	}

	TetriPiece buildI()
	{
		TetriPiece tetriPiece;
		tetriPiece.pieces[0] = buildPiece(0, 0);
		tetriPiece.pieces[1] = buildPiece(1, 0);
		tetriPiece.pieces[2] = buildPiece(2, 0);
		tetriPiece.pieces[3] = buildPiece(3, 0);

		tetriPiece.type = 'I';

		return tetriPiece;
	}
	TetriPiece buildS()
	{
		TetriPiece tetriPiece;
		tetriPiece.pieces[0] = buildPiece(0, 1);
		tetriPiece.pieces[1] = buildPiece(1, 1);
		tetriPiece.pieces[2] = buildPiece(1, 0);
		tetriPiece.pieces[3] = buildPiece(2, 0);

		tetriPiece.type = 'S';

		return tetriPiece;
	}
	TetriPiece buildT()
	{
		TetriPiece tetriPiece;
		tetriPiece.pieces[0] = buildPiece(1, 0);
		tetriPiece.pieces[1] = buildPiece(2, 0);
		tetriPiece.pieces[2] = buildPiece(3, 0);
		tetriPiece.pieces[3] = buildPiece(2, 1);

		tetriPiece.type = 'T';

		return tetriPiece;
	}
	TetriPiece buildL()
	{
		TetriPiece tetriPiece;
		tetriPiece.pieces[0] = buildPiece(0, 0);
		tetriPiece.pieces[1] = buildPiece(0, 1);
		tetriPiece.pieces[2] = buildPiece(0, 2);
		tetriPiece.pieces[3] = buildPiece(1, 2);

		tetriPiece.type = 'L';

		return tetriPiece;
	}
	TetriPiece buildJ()
	{
		TetriPiece tetriPiece;
		tetriPiece.pieces[0] = buildPiece(1, 0);
		tetriPiece.pieces[1] = buildPiece(1, 1);
		tetriPiece.pieces[2] = buildPiece(1, 2);
		tetriPiece.pieces[3] = buildPiece(0, 2);

		tetriPiece.type = 'J';

		return tetriPiece;
	}

	TetriPiece buildO()
	{
		TetriPiece tetriPiece;
		tetriPiece.pieces[0] = buildPiece(0, 0);
		tetriPiece.pieces[1] = buildPiece(1, 0);
		tetriPiece.pieces[2] = buildPiece(0, 1);
		tetriPiece.pieces[3] = buildPiece(1, 1);

		tetriPiece.type = 'O';

		return tetriPiece;
	}
	TetriPiece buildDefault()
	{
		TetriPiece tetriPiece;
		tetriPiece.pieces[0] = buildPiece(0, 0);
		
		tetriPiece.type = 'D';
		
		return tetriPiece;
	}	
	
	
	void resetPosition(TetriPiece & tetriPiece)
	{
		if(tetriPiece.type == 'S'){
			tetriPiece = buildS();
			return;
		}
		if(tetriPiece.type == 'Z'){
			tetriPiece = buildZ();
			return;
		}
		if(tetriPiece.type == 'T'){
			tetriPiece = buildT();
			return;
		}
		if(tetriPiece.type == 'J'){
			tetriPiece = buildJ();
			return;
		}
		if(tetriPiece.type == 'L'){
			tetriPiece = buildL();
			return;
		}
		if(tetriPiece.type == 'O'){
			tetriPiece = buildO();
			return;
		}
		if(tetriPiece.type == 'I'){
			tetriPiece = buildI();
			return;
		}	
	}
