#include "app/Game/Game.h"
#include "app/Communication/Communicable.h"
#include "app/Helper/LogDisplayer.h"

// try to get the path of the executable file on windows
#include <windows.h>
#include <iostream>


/// <summary>
/// Entrée principale du programme
/// </summary>
/// <returns></returns>
int main() {

	// get the path of the executable file
	char path[MAX_PATH];
	GetModuleFileNameA(NULL, path, MAX_PATH);
	std::string pathStr = path;

	std::string::size_type pos = pathStr.find_last_of("\\/");
	std::string pathDir = pathStr.substr(0, pos);

	// lance le jeu
	APP::Game* game = new APP::Game(pathDir);
	//game->run();
	game->run();

	// delete les objets
	delete game;

	return 0;
}