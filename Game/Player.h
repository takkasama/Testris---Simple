#pragma once
#include <fstream> 
const static string PLAYERS_FILE = "save.txt";

const static string TAG_NAME_O = "<name>";
const static string TAG_NAME_C = "</name>";

const static string TAG_RECORD_O = "<record>";
const static string TAG_RECORD_C = "</record>";

const static string TAG_PLAYER_O = "<player>";
const static string TAG_PLAYER_C = "</player>";

	
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

void registerPoints(Player & player , int totalPoints)
{
	if(totalPoints > player.record)
		player.record = totalPoints;
	
	player.points = 0;	
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
	
	if (openTag != std::string::npos) {
		
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
			outTemp << TAG_PLAYER_O + nameModify + recordModify + TAG_PLAYER_C;		
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
