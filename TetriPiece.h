	#pragma once

	// PARA EL MANEJO DE LAS POSICIONES EN EL TABLERO DEL MISMO QUE SE USARA PARA LA ROTACION DE LA PIEZAS
	struct Position
	{
		int x, y;

		// PARA ANIMACION DE BOTONES
		int width, height;
	};

	Position buildPosition(int x, int y, int height, int width)
	{
		Position position;
		position.x = x;
		position.y = y;
		position.height = height;
		position.width = width;

		return position;
	}

	struct Piece
	{

		// LAS PIEZAS SE CONTRUIRAN DE MODO QUE TENDRAN UN POSICION EN (X,Y) BASE Y SE DECREMENTARA Y AUMENTARA DICHAS POCIONES PARA EL MOV
		Position position;
	};

	Piece buildPiece(int x, int y)
	{
		Piece piece;
		piece.position = buildPosition(x, y, 0, 0);

		return piece;
	}
	
	

	// PILA PARA LA CONTRUCCION Y ORGANIZACION DE LA PIEZA, DE MODO QUE SE LEE DE
	//  DE DERECHA A IZQUIERDA CONVIENE LEERLA COMO UNA PILA
	struct TetriPiece
	{

		const static int SIZE = 4;
		Piece pieces[SIZE];

		// TENDRA LOS VALORES BASE DE S - Z - I - 0 - J - L - T  ADEMAS DE LOS VALORES DE D(DEFAULT) y B(BOM-SPECIAL)
		char type;
		
		TetriPiece
	};

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
	


	// CONSTRUYE TODA LA PIECE Y LA ORIENTACION COMPLETA DE ESTA
	TetriPiece buildTetriPiece(char type)
	{
		switch(type)
		{
		case 'T': return buildT();
		case 'L': return buildL();
		case 'J': return buildJ();
		case 'O': return buildO();
		case 'I': return buildI();
		case 'Z': return buildZ();
		default : return buildS();
		}
	}
	
