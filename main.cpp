#include <iostream>
#include <string>
#include <ctime>

#include "raygui.h"
#include "raylib.h"

#include "Bag.h"

using namespace std;


const string PATH_PIECES = "Assets/TetriPieces";
const string PATH_BUTTONS = "Assets/Buttons";

	
struct HoldTetri{
	
	TetriPiece tetriPiece;
	
	
	HoldTetri * next;
	
};


struct StackTetri{

	StackTetri *top;
};
	


int main()
{
	srand(static_cast<unsigned int>(time(0)));
	return 0;
}


