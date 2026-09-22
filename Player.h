#pragma once

struct Player 
{
	string alias;
	int points;
	int maxRecord;
};

Player buildPlayer()
{
	Player player;
	player.alias = "NONE";
	player.points = 0;
	player.maxRecord = 0;
	
	return player;
}

void registerPoints(Player & player , int totalPoints)
{
	if(totalPoints > player.maxRecord)
		player.maxRecord = totalPoints;
	
}


//LOGICA DE GUARDADO DE ARCHIVOS Y OBTENCINO DE LOS OTROS REGISTROS
