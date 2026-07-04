#pragma once
#include<string>
#include<fstream>
using namespace std;

class Player;
class TileMap;
class GameManager;

class SaveManager {
private:
	static const std::string SAVE_FILE;

public:
	static bool saveExists();

	static bool saveGame(const GameManager& gm);
	static bool loadGame(GameManager& gm);
};