#include "app/Game/Game.h"
#include "app/Reader/JsonReader.h"

int main() {

	// get the root path of the project without knowing the current working directory
	std::string rootPath = __FILE__;
	rootPath = rootPath.substr(0, rootPath.find("main.cpp"));

	READER::JsonReader* jsonReader = new READER::JsonReader(rootPath + "data/json/test.json");

	APP::Game* game = new APP::Game(rootPath, jsonReader);
	game->run();

	delete game;

	return 0;
}