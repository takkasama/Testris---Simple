#include "../header/Player.h"

Player buildPlayer()
{
	Player player;
	player.name = "NONE";
	player.record = 0;
	
	return player;
}

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

PlayerNode * getLastPlayerNode(PlayerNode *& node)
{
	if(node == nullptr) return nullptr;
	
	PlayerNode * current = node;
	
	while(current->next != nullptr)
		current = current->next;
	
	return current;
}

int getSizePlayerNode(PlayerNode * node)
{
	if(node == nullptr) return 0;
	
	PlayerNode * current = node;
	
	int size = 0;
	
	while(current != nullptr){
		current = current->next;
		size++;
	}
	
	return size;
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

void orderPlayerByBubbleSort(PlayerNode *& node)
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


PlayerNode* createParition(PlayerNode * begin , PlayerNode *& end , PlayerNode *& prevToBegin)
{
	//elemento principal 
	if(begin == nullptr || end == nullptr) return nullptr;
	
	
	//NODO PARA LA CONECCION PARA LA AYUDA DE LA CONEXION DEL ANTERIO Y EL SIGUIENTE A MOVER
	PlayerNode * current = begin->next;
	PlayerNode * prevToCurrent = begin;
	
	//DECLARACION DEL NUEVO COMIENZO QUE SERIA EL CENTRAL DE LA PARTICION
	PlayerNode * newBegin = begin;
	
	PlayerNode * stopCondition = end->next;
	
	while(current != stopCondition){
		if(begin->player.record > current->player.record){
			//CONEXION DEL ANTERIOR Y EL SIGUIENTE DEL NODO A MOVER
			PlayerNode * save = current->next;
			prevToCurrent->next = save;
			
			//CONEXION CON EL NODO PIVOTE O PRINCIPAL Y EL ANTERIOR A ESTE SI LO TIENE
			current->next = begin;
			
			//INDICAMO QUE SI NEUBO INICIO SERA EL PRIMER ELEMENTO QUE SE DEBA DE MOVER 
			//DE ESTE MODO LOGRAMOS CONSERVAR EL INCIO DE LOS ELEMENTOS QUE DEBEMOS ORDENAR
			if(prevToBegin == nullptr)
				newBegin = current;
			else 
				prevToBegin->next = current;
			
			//ACUTALIZACION EL ELEMNTO PREVIO AL PIVOTE;
			prevToBegin = current;
			
			current = save;
			continue;
		}
		
		prevToCurrent = current;
		current = current->next;
	}
	
	end = prevToCurrent;
	return newBegin;
}


void quickSort(PlayerNode *& begin , PlayerNode *& end)
{
	if(begin == nullptr || end == nullptr ||end == begin) return;
	
	//INDICAMOS QUE EL NODO INICIAL COMO EL CENTRO DE PARTICION
	PlayerNode * parition = begin;
	
	
	//ELEMNTO QUE FUNCIONARA COMO EL ELEMENTO COMO EL PREVION AL PIVOTE QUE EN UN PRINCIPIO
	//ESTE ES ELEMENTO CETNRAL
	PlayerNode * prevToBegin = nullptr;
	
	
	//CREO UN PARTICION ACOMODANDO A LA IZQUIERDA LOR MENORES Y A LA DERECHA LOS MAYORES;
	//LO QUE SE OBTIENE ES EL INCIO DEL ELEMENTO MAS BAJO A LA IZQUIERDA QUE SERA EL COMIENZO PARA LA PARTE IZQUIERDA
	//EL NODO OBTENIDO ES EL PRIMER NODO QUE ES IDENTIFICADO COMO 
	begin = createParition(begin , end, prevToBegin);
	
	
	//IZQUIERDA
	if(prevToBegin != nullptr)
		quickSort(begin , prevToBegin);
	
	//DERECHA
	if(parition != end)
		quickSort(parition->next , end);
}


void orderPlayerByQuickSort(PlayerNode *& node)
{
	if(node  ==  nullptr) return;
	
	PlayerNode * end = getLastPlayerNode(node);	
	
	quickSort(node , end);
	
}


//METODO DE OBTENCION DEL TOP DE JUGADORES QUE RECIBBE UN PUNTERO DE UN ARREGLO DE 
//DE JUGADORES, PARA EL LLENGADO DE ESTOS, DEL MISMO MODO DEL METODO DE ORDENACION QUE SE
//DESEA PARA LOS JUGAORES
Player * getTopPlayer(bool isQuickSort , int & totalPlayers)
{
	PlayerNode * listPlayers = readPlayersFile();
	
	if(listPlayers == nullptr)
		return nullptr;
	
	if(isQuickSort)
		orderPlayerByQuickSort(listPlayers);
	else 
		orderPlayerByBubbleSort(listPlayers);
	
	PlayerNode * current = listPlayers;
	
	totalPlayers = getSizePlayerNode(listPlayers) <= 10 ? getSizePlayerNode(listPlayers) : 10;
	
	Player * players = new Player[totalPlayers];
	
	for(int i = 0 ; i < totalPlayers && current->next != nullptr; i++)
	{
		Player player = current->player;
		players[i] = player;
		
		current = current->next;
	}
	
	return players;
}

