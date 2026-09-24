#pragma once
#include <fstream> 
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
	int points;
	int record;
};

Player buildPlayer()
{
	Player player;
	player.name = "NONE";
	player.points = 0;
	player.record = 0;
	
	return player;
}

//ESTRUCTURA PARA OBTENCION DE LOS DATOS DEL ARCHIVO Y LA ORDENACION DE ESTOS
//DEL MISMO MODO ESTA SE USARA PARA EL ORDEAMIENTO DE LOS DATOS Y LA OBTECION DEL TOP DE ESTOS
//EN EL GAME SE USARA COMO UNA ESTRUCTURA FIJA, ES DECIR UN ARREGLO DE 10.
struct PlayerNode
{
	Player player; 
	
	PlayerNode * next;
	
};
PlayerNode * buildPlayerNode()
{
	PlayerNode * playerNode = new PlayerNode;
	
	playerNode->next = nullptr;
	
	playerNode->player = buildPlayer();
		
	return playerNode;
}

void addPlayerNode(PlayerNode *& node , Player player)
{
	PlayerNode * newNode = buildPlayerNode();
	newNode->player = player;
	
	if(node == nullptr)
	{
		node = newNode;
		return;
	}
	
	PlayerNode * current = node;
	
	while(current->next != nullptr) current = current->next;
	
	current->next = newNode;
}


bool openOutFile(ofstream & outFile , bool isToAdd)
{
	if(isToAdd)
		outFile.open(PLAYERS_FILE, ios::app); 
	else 
		outFile.open(PLAYERS_FILE); 
	
	return outFile.is_open();
}


bool openInFile(ifstream & inFile)
{
	inFile.open(PLAYERS_FILE);
	
	return inFile.is_open();
}


string getTagData(string line , string tag1 , string tag2)
{
	size_t openTag = line.find(tag1);
	
	if (openTag != string::npos) {
		
		size_t startTag = openTag + tag1.size();
		size_t closeTag = line.find(tag2, startTag);
		if (closeTag != string::npos && closeTag > startTag) 
			return line.substr(startTag, closeTag - startTag);
		
	}
	return "";
}


bool isPlayeRegisterOnFile(string name)
{
	ifstream inFile;
	
	if(!openInFile(inFile))
		return false;
	string line;
	
	while(getline(inFile , line)){
		string player = getTagData(line , TAG_PLAYER_O , TAG_PLAYER_C);
		if(player != ""){
			string nameTag = getTagData(line , TAG_NAME_O , TAG_NAME_C);
			if(nameTag == name)
				return true;
		}
	}
	inFile.close();
	
	return false;	
}

void updateRecordToPlayer(string name, int record)
{
	ifstream inFile;
	ofstream outTemp("temp.txt");
	
	if(!openInFile(inFile) || !outTemp.is_open())
		return;
	
	
	string line;
	while(getline(inFile , line)){
		string player  = getTagData(line , TAG_PLAYER_O , TAG_PLAYER_C);
		string nameTag  = getTagData(line, TAG_NAME_O , TAG_NAME_C);
		if(player != "" && nameTag == name){
			string nameModify  = TAG_NAME_O + nameTag + TAG_NAME_C;
			string recordModify = TAG_RECORD_O + to_string(record) +  TAG_RECORD_C;
			outTemp << TAG_PLAYER_O + nameModify + recordModify + TAG_PLAYER_C << endl;		
		}
		else	
		   outTemp << line << endl;		
	}
	
	inFile.close();
	outTemp.close();
	
	remove(PLAYERS_FILE.c_str());
	rename("temp.txt" , PLAYERS_FILE.c_str());
}

void addNewPlayerToFile(Player player)
{
	ofstream outFile;
	
	if(!openOutFile(outFile, true)) return;
	
	string name  = TAG_NAME_O + player.name + TAG_NAME_C;
	string record = TAG_RECORD_O + to_string(player.record) +  TAG_RECORD_C;
	string p = TAG_PLAYER_O + name + record + TAG_PLAYER_C;
	
	outFile << p << endl;
	outFile.close();
	
}


void writePlayerToFile(Player & player)
{
	if(isPlayeRegisterOnFile(player.name))
		updateRecordToPlayer(player.name , player.record);
	else
		addNewPlayerToFile(player);
	
}


//LECTURA DEL ARCHIVO DE SAVE, DE LOS PLAYERS Y CARGADO A LA LISTA DE JUGADORES
PlayerNode * readPlayersFile()
{
	PlayerNode * list = nullptr;
	ifstream inFile;
	if(!openInFile(inFile))
		return nullptr;
	
	string line;
	while(getline(inFile , line))
	{
		string player = getTagData(line , TAG_PLAYER_O, TAG_PLAYER_C);
		
		if(player != ""){
		
			string name = getTagData(line , TAG_NAME_O , TAG_NAME_C);
			string record = getTagData(line  , TAG_RECORD_O , TAG_RECORD_C);
			Player player = buildPlayer();
			player.name = name;
			player.record = stoi(record);
			
			addPlayerNode(list , player);
			
		}
		
	}
	inFile.close();
	
	return list;
}

void sortListByBubleSort(PlayerNode *& node)
{
	if(node == nullptr) return;
	
	PlayerNode * current = node;
	PlayerNode * prevToCurrent  = nullptr;
	
	bool isValidSort = true;
	
	while(isValidSort)
	{
		isValidSort = false;
		
		while(current != nullptr && current->next != nullptr){
			if(current->player.record > current->next->player.record){
				
				PlayerNode * save = current->next;
				current->next = save->next;
				save->next = current;					
				
				isValidSort = true;			
				if(prevToCurrent != nullptr) prevToCurrent->next = save;
				else node = save;
				
				prevToCurrent = save;
				
				continue;
			}
			
			prevToCurrent = current;
			current = current->next;
		}	
		
		
		current = node;
		prevToCurrent = nullptr;
	}
	
	
	
}
	


void sortListByQuickSort(PlayerNode *& node)
{
	
	
	
	
	
	
	
	
}


//METODO DE OBTENCION DEL TOP DE JUGADORES QUE RECIBBE UN PUNTERO DE UN ARREGLO DE 
//DE JUGADORES, PARA EL LLENGADO DE ESTOS, DEL MISMO MODO DEL METODO DE ORDENACION QUE SE
//DESEA PARA LOS JUGAORES
void getTopPlayer(Player *& players , int size, bool isQuickSort)
{
	PlayerNode * listPlayers = readPlayersFile();
	
	if(listPlayers == nullptr)
		return;
	
	if(isQuickSort)
		sortListByQuickSort(listPlayers);
	else 
		sortListByBubleSort(listPlayers);
	
	PlayerNode * current = listPlayers;
	
	for(int i = 0 ; i < size && current->next != nullptr; i++)
	{
		Player player = current->player;
		players[i] = player;
		
		current = current->next;
	}
}


