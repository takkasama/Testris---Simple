#pragma once

#include <iostream>
#include <fstream>

using namespace std;

const static string PLAYERS_FILE = "save.txt";

const static string TAG_NAME_O = "<name>";
const static string TAG_NAME_C = "</name>";

const static string TAG_RECORD_O = "<record>";
const static string TAG_RECORD_C = "</record>";

const static string TAG_PLAYER_O = "<player>";
const static string TAG_PLAYER_C = "</player>";

//ESTRUCTURA PARA LA ORGANIZACION DE LAS PERSISTENCIA DE LOS DATOS
// DEL MISMO PARA LA ORGANIZACION DE LOS TOP RECORDS
struct Player 
{
	string name;
	int record;
	int points;
};

Player buildPlayer();

//ESTRUCTURA PARA OBTENCION DE LOS DATOS DEL ARCHIVO Y LA ORDENACION DE ESTOS
//DEL MISMO MODO ESTA SE USARA PARA EL ORDEAMIENTO DE LOS DATOS Y LA OBTECION DEL TOP DE ESTOS
//EN EL GAME SE USARA COMO UNA ESTRUCTURA FIJA, ES DECIR UN ARREGLO DE 10.
struct PlayerNode
{
	Player player; 
		
	PlayerNode * next;
	
};

PlayerNode * buildPlayerNode();
void addPlayerNode(PlayerNode *& node, Player player);
PlayerNode * getLastPlayerNode(PlayerNode *& node);
int getSizePlayerNode(PlayerNode * node);

bool openOutFile(ofstream & outFile, bool isToAdd);
bool openInFile(ifstream & inFile);

string getTagData(string line, string tag1, string tag2);
bool isPlayerRegisterOnFile(string name);
void updateRecordToPlayer(Player  & player);
void addNewPlayerToFile(Player player);
void writePlayerToFile(Player & player);
//LECTURA DEL ARCHIVO DE SAVE, DE LOS PLAYERS Y CARGADO A LA LISTA DE JUGADORES
PlayerNode * readPlayersFile();

bool modifyPlayerName(string name , string newName);

void orderPlayerByBubbleSort(PlayerNode *& node);
PlayerNode* createParition(PlayerNode * begin, PlayerNode *& end, PlayerNode *& prevToBegin);
void quickSort(PlayerNode *& begin, PlayerNode *& end);
void orderPlayerByQuickSort(PlayerNode *& node);

//METODO DE OBTENCION DEL TOP DE JUGADORES QUE RECIBBE UN PUNTERO DE UN ARREGLO DE 
//DE JUGADORES, PARA EL LLENGADO DE ESTOS, DEL MISMO MODO DEL METODO DE ORDENACION QUE SE
//DESEA PARA LOS JUGAORES
Player * getTopPlayer(bool isQuickSort , int & totalPlayers);
	
